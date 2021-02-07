#ifndef PERMISSIONSWIDGETITEM_H
#define PERMISSIONSWIDGETITEM_H

#include "Addons/webpage.h"

#include <QWidget>
#include <QLabel>
#include <QComboBox>

class PermissionsWidgetItem : public QWidget
{
	Q_OBJECT
public:
	explicit PermissionsWidgetItem(QWidget *parent = nullptr);

	void setSettingsItem(QWebEnginePage::Feature *feature, QWebEnginePage::PermissionPolicy *policy);
signals:

public slots:

private:
	QLabel *m_title;
	QComboBox *m_voiceBox;
};

#endif // PERMISSIONSWIDGETITEM_H
