#include "script.h"

#include <QPainter>

Script::Script(QWidget *parent) : QWidget(parent)
{
	setFixedSize(30, 30);
}

void Script::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::blue));
	painter.drawRect(rect());
}
