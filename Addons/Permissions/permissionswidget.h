#ifndef PERMISSIONSWIDGET_H
#define PERMISSIONSWIDGET_H

#include "Addons/Permissions/permissionswidgetitem.h"

#include <QWidget>
#include <QWebEnginePage>

class PermissionsWidget : public QWidget
{
	Q_OBJECT
public:
	explicit PermissionsWidget(QWidget *parent = nullptr);

	void setItemsSettings(QMap<QWebEnginePage::Feature *, QWebEnginePage::PermissionPolicy *> *items);
signals:

public slots:
	void showWidget();
	void hideWidget();
private:
	QList<PermissionsWidgetItem *> m_items;

	// QObject interface
public:
	bool eventFilter(QObject *watched, QEvent *event) override;

	// QWidget interface
protected:
	void paintEvent(QPaintEvent *event) override;
};

#endif // PERMISSIONSWIDGET_H
