#include "urlcompletteritem.h"

#include <QPainter>

UrlCompletterItem::UrlCompletterItem(QWidget *parent) : QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Widget);
}


void UrlCompletterItem::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::yellow));
	painter.setPen(QPen(Qt::black));
	painter.drawRect(rect());
	painter.drawText(0, height(), "RostikTawer");
}
