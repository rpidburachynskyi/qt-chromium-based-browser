#include "webpageinfo.h"

#include <QApplication>
#include <QMouseEvent>
#include <QPropertyAnimation>

WebPageInfo::WebPageInfo(QWidget *parent) : QWidget(parent)
{
	setVisible(false);
	m_console = new class Console(this);
	m_sourceCode = new QTextEdit(this);
	m_watchedTab = nullptr;

	m_sourceCode->setReadOnly(true);

	m_tabs = new QTabWidget(this);
	m_tabs->addTab(m_console, "Console");
	m_tabs->addTab(m_sourceCode, "Source code");

	QVBoxLayout *l = new QVBoxLayout;
	l->addWidget(m_tabs);
	setLayout(l);

	m_closeAction.setText("Close");
	connect(&m_closeAction, &QAction::triggered, this, &WebPageInfo::close);

	m_menu.addAction(&m_closeAction);
}

void WebPageInfo::changeWatcherTab(Tab *tab)
{
	m_watchedTab = tab;

	m_console->setTab(tab);

	connect(m_watchedTab->page(), &WebPage::loadFinished, [this](){updateWithContext(SourceCode);});

	updateWithContext(All);
}

void WebPageInfo::showWithContext(WebPageInfo::ContextType type)
{
	if(!isVisible())
		setVisible(true);
	else
		return setVisible(false);
	switch (type)
	{
		case Console:
			m_tabs->setCurrentWidget(m_console);
			break;
		case SourceCode:
			m_tabs->setCurrentWidget(m_sourceCode);
			break;
		default:
			throw "All can't be used in this context";
	}

	QPropertyAnimation *anim = new QPropertyAnimation(this, "width", this);
	anim->setDuration(100);
	anim->setStartValue(0);
	anim->setEndValue(300);
	anim->start();
}

void WebPageInfo::updateWithContext(WebPageInfo::ContextType type)
{
	if(type == All || type == SourceCode)
	{
		m_watchedTab->page()->toHtml([this](QString html) {
			m_sourceCode->setPlainText(m_processHTML(html));
		});
	}
}

void WebPageInfo::showContextMenu()
{
	m_menu.move(QCursor::pos());
	m_menu.show();
}

void WebPageInfo::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::RightButton)
	{
		showContextMenu();
	}
}

void nCharLineDeleteT(QString &s, int n)
{
	while(n > 0 && s[n] != '\t' && s[n] != '\n')
		n--;
	if(s[n] == '\n')
		return;
	s.remove(n, 1);
}

QString WebPageInfo::m_processHTML(QString html)
{
	//FIXIT
	return html;
}
