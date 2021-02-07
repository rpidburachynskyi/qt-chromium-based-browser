#include "qstandartwidget.h"

QStandartWidget::QStandartWidget(QWidget *parent) : QWidget(parent)
{

}

QWidget *QStandartWidget::rootWidget()
{
	QWidget *parent = parentWidget();
	while (parent->parentWidget() != nullptr)
		parent = parent->parentWidget();
	return parent;
}
