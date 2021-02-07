#include "consolemessage.h"

#include <QPainter>
#include <QDebug>

ConsoleMessage::ConsoleMessage(QWidget *parent) : QWidget(parent)
{
	setFixedHeight(20);
}

void ConsoleMessage::setMessage(const QString &message)
{
	m_message = message;
}

void ConsoleMessage::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::white));
	painter.drawRect(rect());
	painter.setPen(QPen(Qt::black));
	painter.drawText(0, height() * 3/4, m_message);
}
