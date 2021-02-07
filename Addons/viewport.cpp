#include "viewport.h"
#include <QApplication>
#include <QWheelEvent>

Viewport::Viewport(QWidget *parent) : QWebEngineView (parent)
{
	setMinimumSize(30,50);
	setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

	m_sourceCodeAction.setText("Source code");
	connect(&m_sourceCodeAction, &QAction::triggered, [this]()
	{
		emit this->sourceCodeTriggered(WebPageInfo::SourceCode);
	});

	m_menu.addAction(&m_sourceCodeAction);

	connect(this, &Viewport::customContextMenuRequested, [this]()
	{
		m_menu.move(QCursor::pos());
		m_menu.show();
	});
}

void Viewport::reload()
{
	page()->triggerAction(WebPage::Reload);
}


void Viewport::wheelEvent(QWheelEvent *event)
{
	if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
	{
		setZoomFactor(zoomFactor() + (event->delta() > 0 ? 0.1 : -0.1));
	}
}
