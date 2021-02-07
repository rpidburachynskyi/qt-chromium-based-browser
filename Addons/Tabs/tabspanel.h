#ifndef TABSPANEL_H
#define TABSPANEL_H

#include "tab.h"
#include "tabslayout.h"
#include "actionpanel.h"
#include "Addons/Permissions/permissionswidget.h"
#include "Inhernit/urllineedit.h"
#include "Addons/Permissions/featurepermissinwidget.h"

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>

class TabsPanel : public QWidget
{
	Q_OBJECT
public:
	TabsPanel(QWidget *parent = nullptr);
	~TabsPanel() override;

	void addTab();
	void addTab(const QUrl &url);
	void addTab(Tab *tab);
signals:
	void tabClosed(Tab *tab);
	void changedTab(Tab *tab);

	void triggeredMove(QPoint p);

	void triggeredCollapse();
	void triggeredFullScreen();
	void triggeredClose();
private slots:
	void onTabClosed(Tab *tab);

	void moveNewWindowTab();

	void changeViewTab(Tab *tab);

	void showContextMenuTab();

	void updateTabInterface();

	void showPermissionWidget();
	void updatePermissionsWidget();

	void showFeaturePermissinWidget(const QUrl &securityOrigin, QWebEnginePage::Feature feature);
private slots:
	void showContextMenu();

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

private:
	Tab *m_currentOpenedTab;

	QList<Tab *> m_tabs;

	ActionPanel *m_actionsPanel;
	QPushButton *m_permissionsPushButton;
	UrlLineEdit *m_urlLineEdit;

	TabsLayout *m_tabsLayout;

	QMenu m_contextMenu;
	QAction m_newTabAction;

	Tab *m_currentContextMenuTab;
	QMenu m_contextMenuTab;
	QAction m_newWindowTabActionTab;
	QAction m_closeTabActionTab;


	QPoint m_clickMovePoint;

	FeaturePermissinWidget m_featurePermissinWidget;
	PermissionsWidget m_permissionWidget;
};

#endif // TABSPANEL_H
