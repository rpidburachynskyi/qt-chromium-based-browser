#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebEnginePage>

class WebPage : public QWebEnginePage
{
	Q_OBJECT
public:
	WebPage(QObject *parent = nullptr);

	void load(const QUrl &url);

	void triggerAction(WebAction action, bool checked = false) override;
	int Progres;
signals:
	void messageAdded(const QString &message);
	void newTabUrlAdded(const QUrl &url);

protected:
	void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID) override;

	bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame) override;

private:

	QUrl m_processUrl(const QUrl &prev);
};

#endif // WEBPAGE_H
