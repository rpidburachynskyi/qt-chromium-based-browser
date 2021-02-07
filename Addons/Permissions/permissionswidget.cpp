#include "permissionswidget.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>

PermissionsWidget::PermissionsWidget(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *l = new QVBoxLayout(this);
	for(int i = 0; i < 8; i++)
	{
		auto item = new PermissionsWidgetItem(this);
		m_items.append(item);
		l->addWidget(item);
	}

	l->setSpacing(0);

	setWindowFlags (Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);

	QApplication::instance()->installEventFilter(this);

}

void PermissionsWidget::setItemsSettings(QMap<QWebEnginePage::Feature *, QWebEnginePage::PermissionPolicy *> *items)
{
	int i = 0;
	for(auto key : items->keys())
	{
		PermissionsWidgetItem *item = m_items[i++];
		item->setSettingsItem(key, items->value(key));
	}
}

void PermissionsWidget::showWidget()
{
	show();
	QPropertyAnimation *anim = new QPropertyAnimation(this, "size", this);
	anim->setStartValue(QSize(0,0));
	anim->setEndValue(QSize(380, 300));
	anim->start();
	connect(anim, &QPropertyAnimation::finished, anim, &QPropertyAnimation::deleteLater);
}

void PermissionsWidget::hideWidget()
{
	QPropertyAnimation *anim = new QPropertyAnimation(this, "size", this);
	anim->setStartValue(QSize(380, 300));
	anim->setEndValue(QSize(0,0));
	anim->start();
	connect(anim, &QPropertyAnimation::finished, this, &QWidget::hide);
	connect(anim, &QPropertyAnimation::finished, anim, &QPropertyAnimation::deleteLater);
}

bool PermissionsWidget::eventFilter(QObject *watched, QEvent *event)
{
	// FIXIT
	return QObject::eventFilter(watched, event);
	if(!isVisible())
		return QObject::eventFilter(watched, event);
	if(event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *mev = static_cast<QMouseEvent *>(event);
		if(mev->button() == Qt::LeftButton && qobject_cast<QComboBox *>(watched) == nullptr)
		{
			hide();
		}
	}
	return QObject::eventFilter(watched, event);
}

void PermissionsWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::yellow));
	painter.drawRect(rect());
}
