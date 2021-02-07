#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <Addons/webpageinfo.h>
#include "Addons/webpage.h"

#include <QWebEngineView>
#include <QMenu>

class Viewport : public QWebEngineView
{
	Q_OBJECT
public:
	Viewport(QWidget *parent = nullptr);

signals:
	void sourceCodeTriggered(WebPageInfo::ContextType type);

public slots:
	void reload();

protected:
	void wheelEvent(QWheelEvent *event) override;

private:
	QMenu m_menu;

	QAction m_sourceCodeAction;
};

#endif // VIEWPORT_H
