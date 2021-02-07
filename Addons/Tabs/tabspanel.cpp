#include "Addons/Tabs/tabspanel.h"
#include "Addons/window.h"

#include <QPainter>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QWebEngineHistory>

TabsPanel::TabsPanel(QWidget *parent)
{
	m_actionsPanel = new ActionPanel(this);

	m_actionsPanel->setFixedHeight(30);

	m_permissionsPushButton = new QPushButton(this);
	m_urlLineEdit = new UrlLineEdit(this);

	m_tabsLayout = new TabsLayout;

	m_permissionsPushButton->setFixedSize(30,30);

	QHBoxLayout *hintButtonsLayout = new QHBoxLayout;
	QHBoxLayout *tabsHLayoutANDhintButtonsLayout = new QHBoxLayout;

	tabsHLayoutANDhintButtonsLayout->setMargin(0);
	tabsHLayoutANDhintButtonsLayout->setSpacing(0);

	QVBoxLayout *tabsHLayoutANDhintButtonsLayoutANDLineEdit = new QVBoxLayout;

	tabsHLayoutANDhintButtonsLayoutANDLineEdit->setMargin(0);
	tabsHLayoutANDhintButtonsLayoutANDLineEdit->setSpacing(0);

	QHBoxLayout *permissionANDurledit = new QHBoxLayout;

	QPushButton* hideBtn = new QPushButton("_", this);
	hideBtn->setFixedSize(30,30);
	connect(hideBtn, &QPushButton::clicked, this, [this](){emit triggeredCollapse();});
	QPushButton* fullScreenBtn = new QPushButton("O", this);
	fullScreenBtn->setFixedSize(30,30);
	connect(fullScreenBtn, &QPushButton::clicked, this, [this](){emit triggeredFullScreen();});
	QPushButton* closeBtn = new QPushButton("X", this);
	closeBtn->setFixedSize(30,30);
	connect(closeBtn, &QPushButton::clicked, this, [this](){
		emit triggeredClose();});

	connect(m_permissionsPushButton, &QPushButton::clicked, this, &TabsPanel::showPermissionWidget);


	permissionANDurledit->addWidget(m_actionsPanel);
	permissionANDurledit->addWidget(m_permissionsPushButton);
	permissionANDurledit->addWidget(m_urlLineEdit);

	hintButtonsLayout->addWidget(hideBtn);
	hintButtonsLayout->addWidget(fullScreenBtn);
	hintButtonsLayout->addWidget(closeBtn);
	hintButtonsLayout->setAlignment(Qt::AlignRight);

	tabsHLayoutANDhintButtonsLayout->addWidget(m_tabsLayout, 110);
	tabsHLayoutANDhintButtonsLayout->addLayout(hintButtonsLayout, 2);

	tabsHLayoutANDhintButtonsLayoutANDLineEdit->addLayout(tabsHLayoutANDhintButtonsLayout);
	tabsHLayoutANDhintButtonsLayoutANDLineEdit->addLayout(permissionANDurledit);

	tabsHLayoutANDhintButtonsLayoutANDLineEdit->setSizeConstraint(QVBoxLayout::SizeConstraint::SetMinAndMaxSize);

	setLayout(tabsHLayoutANDhintButtonsLayoutANDLineEdit);

	connect(m_urlLineEdit, &UrlLineEdit::triggeredEnter, [this](const QUrl &url) {m_currentOpenedTab->loadPageFromUrl(url);});

	/// Fill actions //////////////////////////////////////////////////////////////////
	// Main context menu
	m_newTabAction.setText("New tab");


	m_contextMenu.addAction(&m_newTabAction);


	connect(&m_newTabAction, &QAction::triggered, this, static_cast<void (TabsPanel::*)(void)>(&TabsPanel::addTab));

	// Tab context menu
	m_newWindowTabActionTab.setText("New window");
	m_closeTabActionTab.setText("Close tab");

	m_contextMenuTab.addAction(&m_newWindowTabActionTab);
	m_contextMenuTab.addAction(&m_closeTabActionTab);

	connect(&m_newWindowTabActionTab, &QAction::triggered, this, &TabsPanel::moveNewWindowTab);
	connect(&m_closeTabActionTab, &QAction::triggered, [this](){m_currentContextMenuTab->closeTab();});
	/////////////////////////////////////////////////////////////////////////////////////
}

TabsPanel::~TabsPanel()
{
	for(auto tab : m_tabs)
		delete tab;
	delete m_urlLineEdit;
	delete m_tabsLayout;
}

void TabsPanel::addTab(Tab *tab)
{
	connect(tab, &Tab::clicked, this, &TabsPanel::changeViewTab);
	connect(tab, &Tab::triggeredContextMenu, this, &TabsPanel::showContextMenuTab);
	connect(tab, &Tab::updatedPermissions, this, &TabsPanel::updatePermissionsWidget);
	connect(tab, &Tab::tabClosed, this, &TabsPanel::onTabClosed);
	connect(tab, &Tab::triggeredFeaturePermissionRequest, this, &TabsPanel::showFeaturePermissinWidget);
	connect(tab->page(), &WebPage::titleChanged, this, &TabsPanel::updateTabInterface);
	connect(tab->page(), &WebPage::newTabUrlAdded, this, static_cast<void (TabsPanel::*)(const QUrl& url)>(&TabsPanel::addTab));
	m_tabs.append(tab);

	m_tabsLayout->addTab(tab);

	changeViewTab(tab);
}

void TabsPanel::addTab()
{
	Tab *tab = new Tab(this);
	addTab(tab);
}

void TabsPanel::addTab(const QUrl &url)
{
	Window::LastPressedMouseButton = -1;
	Tab *tab = new Tab(this);
	addTab(tab);
	tab->page()->load(url);
}

void TabsPanel::moveNewWindowTab()
{
	if(m_currentContextMenuTab == nullptr)
		throw "Null of tab";
	m_currentContextMenuTab->moveToNewWindow();
	m_tabs.removeOne(m_currentContextMenuTab);
	changeViewTab(m_tabs.first());
}

void TabsPanel::changeViewTab(Tab *tab)
{
	disconnect(m_actionsPanel, &ActionPanel::triggeredPageAction, m_currentOpenedTab, &Tab::proccessPageAction);

	for(auto tab : m_tabs) // FIXIT
	{
		tab->setSelected(false);
		tab->repaint();
	}
	m_currentOpenedTab = tab;
	m_currentOpenedTab->setSelected(true);
	m_currentOpenedTab->repaint();
	emit changedTab(m_currentOpenedTab);
	updateTabInterface();

	connect(m_actionsPanel, &ActionPanel::triggeredPageAction, m_currentOpenedTab, &Tab::proccessPageAction);
}

void TabsPanel::onTabClosed(Tab *tab)
{
	m_tabs.removeOne(tab);
	changeViewTab(m_tabs.first());
	emit tabClosed(tab);
}

void TabsPanel::showContextMenuTab()
{
	m_currentContextMenuTab = static_cast<Tab *>(sender());

	m_newWindowTabActionTab.setVisible(m_tabs.size() != 1);
	m_closeTabActionTab.setEnabled(m_tabs.size() != 1);

	m_contextMenuTab.move(QCursor::pos());
	m_contextMenuTab.show();
}

void TabsPanel::updateTabInterface()
{
	m_urlLineEdit->setText(m_currentOpenedTab->isStartPage() ? "" : m_currentOpenedTab->page()->url().url());
	m_actionsPanel->backButton()->setEnabled(m_currentOpenedTab->page()->history()->canGoBack());
	m_actionsPanel->forwardButton()->setEnabled(m_currentOpenedTab->page()->history()->canGoForward());
}

void TabsPanel::showPermissionWidget()
{
	if(!m_permissionWidget.isVisible())
	{
		m_permissionWidget.setParent(parentWidget());
		m_permissionWidget.setItemsSettings(m_currentOpenedTab->featuresPermissions());
		m_permissionWidget.move(m_permissionsPushButton->pos() + QPoint(m_permissionsPushButton->width(), m_permissionsPushButton->height()));
		m_permissionWidget.showWidget();
	}else
	{
		m_permissionWidget.hideWidget();
	}
}

void TabsPanel::updatePermissionsWidget()
{
	if(static_cast<Tab *>(sender()) != m_currentOpenedTab)
		return;
	m_permissionWidget.setItemsSettings(m_currentOpenedTab->featuresPermissions());
}

void TabsPanel::showFeaturePermissinWidget(const QUrl &securityOrigin, QWebEnginePage::Feature feature)
{
	Tab *tab = static_cast<Tab *>(sender());
	m_featurePermissinWidget.setSettings(tab, securityOrigin, feature);
	m_featurePermissinWidget.move(0,0);
	m_featurePermissinWidget.show();
}

void TabsPanel::showContextMenu()
{
	m_contextMenu.move(QCursor::pos());
	m_contextMenu.show();
}

void TabsPanel::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_clickMovePoint = event->pos();
		m_clickMovePoint.ry() += 7;
	}
}

void TabsPanel::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons() == Qt::LeftButton)
	{
		emit triggeredMove(QCursor::pos() - m_clickMovePoint);
	}
}

void TabsPanel::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{

	}else if(event->button() == Qt::RightButton)
	{
		showContextMenu();
	}
}

void TabsPanel::mouseDoubleClickEvent(QMouseEvent *event)
{
	Tab *tab = new Tab();
	tab->move(event->pos().rx(), 0);
	addTab(tab);
}

void TabsPanel::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
	painter.drawRect(rect());
}
