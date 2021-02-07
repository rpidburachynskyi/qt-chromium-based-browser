#ifndef QSTANDARTWIDGET_H
#define QSTANDARTWIDGET_H

#include <QWidget>

class QStandartWidget : public QWidget
{
	Q_OBJECT
public:
	explicit QStandartWidget(QWidget *parent = nullptr);

	QWidget *rootWidget();

signals:

public slots:
};

#endif // QSTANDARTWIDGET_H
