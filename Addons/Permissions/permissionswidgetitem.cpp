#include "permissionswidgetitem.h"

#include <QHBoxLayout>
#include <QApplication>
#include <QPainter>

PermissionsWidgetItem::PermissionsWidgetItem(QWidget *parent) : QWidget(parent)
{
	m_title = new QLabel(this);
	m_voiceBox = new QComboBox(this);

	m_voiceBox->addItems(QStringList() << "Question" << "Granted" << "Denied");

	QHBoxLayout *l = new QHBoxLayout(this);

	l->addWidget(m_title);
	l->addWidget(m_voiceBox);
}

void PermissionsWidgetItem::setSettingsItem(QWebEnginePage::Feature *feature, QWebEnginePage::PermissionPolicy *policy)
{
	switch (*feature)
	{
		case WebPage::Feature::MouseLock:
			m_title->setText("Mouse lock");
			break;
		case WebPage::Feature::Geolocation:
			m_title->setText("Geolocation");
			break;
		case WebPage::Feature::Notifications:
			m_title->setText("Notifications");
			break;
		case WebPage::Feature::MediaAudioCapture:
			m_title->setText("Audio capture");
			break;
		case WebPage::Feature::MediaVideoCapture:
			m_title->setText("Video capture");
			break;
		case WebPage::Feature::DesktopVideoCapture:
			m_title->setText("Desktop Video capture");
			break;
		case WebPage::Feature::MediaAudioVideoCapture:
			m_title->setText("Media Audio Video capture");
			break;
		case WebPage::Feature::DesktopAudioVideoCapture:
			m_title->setText("Desktop Audio Video capture");
			break;
		default:
			throw "OUT OF FEATURES";
	}

	m_voiceBox->disconnect();
	m_voiceBox->setCurrentIndex(*policy);

	connect(m_voiceBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [policy](int index)
	{
		*policy = static_cast<WebPage::PermissionPolicy>(index);
	});
}
