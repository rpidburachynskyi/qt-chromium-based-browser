#ifndef WINDOW_H
#define WINDOW_H

#include "Addons/viewport.h"
#include "webpageinfo.h"
#include "Addons/Tabs/tabspanel.h"
#include "Addons/Scripts/scriptspanel.h"
#include "Addons/Tabs/closetabhistory.h"

#include <QWidget>

class Window : public QWidget
{
	Q_OBJECT
public:
	explicit Window(Tab *tab = nullptr, QWidget *parent = nullptr);
	~Window() override;

	static int LastPressedMouseButton;

public slots:
	void addClosedTabHistory(Tab *tab);

protected:
	bool eventFilter(QObject *watched, QEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void closeEvent(QCloseEvent *event) override;

signals:

public slots:
	void changeTab(Tab *tab);

private slots:
	void changeShowMode();

private:
	TabsPanel *m_tabsPanel;
	Viewport *m_viewport;
	ScriptsPanel *m_scriptsPanel;
	WebPageInfo *m_webPageInfo;
	CloseTabHistory m_closedTabsHistory;
};

#endif // WINDOW_H
