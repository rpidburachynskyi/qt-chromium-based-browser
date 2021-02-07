#include "webpage.h"
#include "window.h"

#include <QDebug>
#include <QApplication>
#include <QWebEngineFullScreenRequest>

WebPage::WebPage(QObject *parent) : QWebEnginePage (parent)
{
	connect(this, &WebPage::loadProgress, [this](int pr)
	{
		Progres = pr;
	});


	connect(this, &WebPage::fullScreenRequested, [this](QWebEngineFullScreenRequest r)
	{
		r.accept();
	});
}

void WebPage::load(const QUrl &url)
{
	return QWebEnginePage::load(m_processUrl(url));
}

void WebPage::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID)
{
	emit messageAdded(QString::number(lineNumber) + ") " + message);
}

bool WebPage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
	if(Window::LastPressedMouseButton == Qt::MiddleButton)
	{
		emit this->newTabUrlAdded(url);
		return false;
	}
	return true;
}

QUrl WebPage::m_processUrl(const QUrl &prev)
{
	QUrl next = prev;
	QString url = next.url();
	if(url.contains("https://") || url.contains("http://"))
		return next;
	const char* FIND_GOOGLE_URL = "https://www.google.com/search?q=";
	url.push_front(FIND_GOOGLE_URL);
	next.setUrl(url);
	return next;
}

void WebPage::triggerAction(QWebEnginePage::WebAction action, bool checked)
{
	QWebEnginePage::triggerAction(action, checked);
}
