#include "console.h"
#include <QPainter>
#include <QDebug>
#include <qscrollbar.h>
#include <QApplication>

Console::Console(QWidget *parent) : QWidget (parent)
{
	QVBoxLayout *l = new QVBoxLayout;
	m_consoleScroll = new QScrollArea(this);
	m_messagesLayout = new QVBoxLayout;
	m_messagesLayout->setAlignment(Qt::AlignTop);
	m_viewport = new QWidget(this);
	m_viewport->setLayout(m_messagesLayout);
	m_consoleScroll->setWidget(m_viewport);
	m_currentWatchedTab = nullptr;

	m_consoleEditor = new ConsoleEditor(this);

	connect(m_consoleEditor, &ConsoleEditor::executeCommand, [this](const QString &command)
	{
		m_currentWatchedTab->page()->runJavaScript(command);
	});

	m_messagesLayout->setMargin(0);
	m_messagesLayout->setMargin(1);

	l->addWidget(m_consoleScroll, 7);
	l->addWidget(m_consoleEditor, 2);
	setLayout(l);
}

void Console::setTab(Tab *tab)
{
	if(m_currentWatchedTab != nullptr)
		disconnect(m_currentWatchedTab, &Tab::messageAdded, this, &Console::addMessage);
	m_currentWatchedTab = tab;
	setMessages(tab->messages());
	connect(m_currentWatchedTab, &Tab::messageAdded, this, &Console::addMessage);
}

void Console::setMessages(const QList<QString> &messages)
{
	if(messages.size() < m_consoleMessages.size())
	{
		int count = m_consoleMessages.size() - messages.size();
		for(int i = 0; i < count; i++)
		{
			delete m_consoleMessages.takeLast();
		}
	}else if (messages.size() > m_consoleMessages.size())
	{
		int count = messages.size() - m_consoleMessages.size();
		for(int i = 0; i < count; i++)
		{
			ConsoleMessage *message = new ConsoleMessage(this);
			message->show();
			m_messagesLayout->addWidget(message);
			m_consoleMessages.append(message);
		}
	}

	for(int i = 0; i < messages.size(); i++)
	{
		m_consoleMessages[i]->setMessage(messages[i]);
		m_consoleMessages[i]->repaint();
	}
	m_viewport->resize(width(), messages.size() * 20);
}

void Console::addMessage(const QString &msg)
{
	ConsoleMessage *message = new ConsoleMessage(this);
	message->setMessage(msg);
	message->show();
	m_messagesLayout->addWidget(message);
	m_consoleMessages.append(message);
	m_viewport->resize(width(), m_consoleMessages.size() * 21);
}

void Console::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::black));
	painter.drawRect(rect());
}
