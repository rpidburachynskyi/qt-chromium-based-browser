#ifndef CONSOLE_H
#define CONSOLE_H

#include "Inhernit/consolemessage.h"
#include "Addons/Tabs/tab.h"
#include "Addons/RightPanel/Console/consoleeditor.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>

class Console : public QWidget
{
	Q_OBJECT
public:
	explicit Console(QWidget *parent = nullptr);

signals:

public slots:
	void setTab(Tab *tab);
	void setMessages(const QList<QString> &messages);
	void addMessage(const QString &message);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	QScrollArea *m_consoleScroll;
	QWidget *m_viewport;

	ConsoleEditor *m_consoleEditor;

	Tab * m_currentWatchedTab;
	QList <ConsoleMessage *> m_consoleMessages;
	QVBoxLayout *m_messagesLayout;
};

#endif // CONSOLE_H
