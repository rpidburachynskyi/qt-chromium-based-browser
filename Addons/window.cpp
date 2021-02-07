#include "window.h"

#include <QVBoxLayout>
#include <QNetworkProxy>
#include <QTimer>
#include <QMouseEvent>
#include <QSplitter>
#include <QTabWidget>
#include <QApplication>
#include <QWebEngineSettings>

int Window::LastPressedMouseButton = -1;

Window::Window(Tab *tab, QWidget *parent) : QWidget(parent)
{

	m_tabsPanel = new TabsPanel(this);
	m_viewport = new Viewport(this);
	m_scriptsPanel = new ScriptsPanel(this);
	m_webPageInfo = new WebPageInfo(this);

	QHBoxLayout *lb = new QHBoxLayout;
	QVBoxLayout *vb = new QVBoxLayout;
	QSplitter *sp = new QSplitter(this);
	sp->addWidget(m_viewport);
	sp->addWidget(m_webPageInfo);

	lb->addWidget(m_tabsPanel);

	vb->setMargin(0);
	vb->setSpacing(0);
	vb->addLayout(lb);
	vb->addWidget(sp);
	vb->addWidget(m_scriptsPanel);

	setLayout(vb);
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);

	connect(m_tabsPanel, &TabsPanel::changedTab, this, &Window::changeTab);
	connect(m_tabsPanel, &TabsPanel::triggeredCollapse, this, &Window::showMinimized);
	connect(m_tabsPanel, &TabsPanel::triggeredFullScreen, this, &Window::changeShowMode);
	connect(m_tabsPanel, &TabsPanel::triggeredClose, this, &Window::close);
	connect(m_tabsPanel, &TabsPanel::triggeredMove, [this](const QPoint &pos) {if(!isMaximized()) move(pos);});
	connect(m_tabsPanel, &TabsPanel::tabClosed, this, &Window::addClosedTabHistory);

	connect(m_viewport, &Viewport::sourceCodeTriggered, [this](){m_webPageInfo->showWithContext(WebPageInfo::SourceCode);});

	showNormal();

	m_tabsPanel->addTab(tab == nullptr ? new Tab() : tab);

	QApplication::instance()->installEventFilter(this);
}

Window::~Window()
{
	delete m_tabsPanel;
	delete m_viewport;
}

void Window::addClosedTabHistory(Tab *tab)
{
	m_closedTabsHistory.addTab(tab);
}

bool Window::eventFilter(QObject *watched, QEvent *event)
{
	QMouseEvent *mev = static_cast<QMouseEvent *>(event);
	if(mev != nullptr && mev->type() == QEvent::MouseButtonPress)
	{
		LastPressedMouseButton = mev->button();
	}
	return QObject::eventFilter(watched, event);
}

void Window::keyPressEvent(QKeyEvent *event)
{
	if(qApp->keyboardModifiers().testFlag(Qt::ControlModifier))
	{
		 if(qApp->keyboardModifiers().testFlag(Qt::ShiftModifier))
		 {
			 if(event->key() == Qt::Key_T)
			 {
				 if(!m_closedTabsHistory.hasTabUrl())
					 return;
				 m_tabsPanel->addTab(m_closedTabsHistory.getTabUrl());
			 }
		 }

		 if(event->key() == Qt::Key_R)
		 {
			 m_viewport->reload();
		 }else if(event->key() == Qt::Key_O)
		 {

		 }
	}

}

void Window::closeEvent(QCloseEvent *event)
{
	QTimer::singleShot(25, [this](){
		this->deleteLater();});
	//delete this;
}

void Window::changeTab(Tab *tab)
{
	m_viewport->setPage(tab->page());
	m_webPageInfo->changeWatcherTab(tab);
}

void Window::changeShowMode()
{
	if(isMaximized())
		showNormal();
	else
		showMaximized();
}
