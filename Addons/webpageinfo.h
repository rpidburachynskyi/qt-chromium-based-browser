#ifndef WEBPAGEINFO_H
#define WEBPAGEINFO_H

#include "Addons/RightPanel/Console/console.h"

#include <QWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QMenu>

class WebPageInfo : public QWidget
{
	Q_OBJECT
public:

	enum ContextType
	{
		All,
		Console,
		SourceCode
	};
	explicit WebPageInfo(QWidget *parent = nullptr);

signals:

public slots:
	void changeWatcherTab(Tab *tab);

	void showWithContext(ContextType type);
	void updateWithContext(ContextType type = ContextType::All);

private slots:

	void showContextMenu();
private:
	QTabWidget *m_tabs;

	Tab *m_watchedTab;

	class Console *m_console;
	QTextEdit *m_sourceCode;

	QMenu m_menu;
	QAction m_closeAction;

	// QWidget interface
protected:
	void mousePressEvent(QMouseEvent *event) override;

private:

	QString m_processHTML(QString html);
};

#endif // WEBPAGEINFO_H
