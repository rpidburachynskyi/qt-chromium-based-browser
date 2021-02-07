#include "featurepermissinwidget.h"

#include <QPainter>
#include <QVBoxLayout>

FeaturePermissinWidget::FeaturePermissinWidget(QWidget *parent) : QWidget(parent)
{
	setFixedSize(300, 170);

	m_titleLabel = new QLabel(this);
	m_yesButton = new QPushButton(this);
	m_noButton = new QPushButton(this);

	QHBoxLayout *hl = new QHBoxLayout;
	QVBoxLayout *vl = new QVBoxLayout(this);

	hl->addWidget(m_yesButton);
	hl->addWidget(m_noButton);

	vl->addWidget(m_titleLabel);
	vl->addLayout(hl);

	vl->setAlignment(Qt::AlignBottom);

	connect(m_yesButton, &QPushButton::clicked, [this]()
	{
		m_tab->setFeaturePermission(m_secureOrigin, m_feature, WebPage::PermissionGrantedByUser);
		close();
	});
	connect(m_noButton, &QPushButton::clicked, [this]()
	{
		m_tab->setFeaturePermission(m_secureOrigin, m_feature, WebPage::PermissionDeniedByUser);
		close();
	});

	setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
	setFixedSize(280, 100);
	m_titleLabel->setFont(QFont("Arial", 24));
	m_yesButton->setText("Granted");
	m_noButton->setText("Denied");
}

void FeaturePermissinWidget::setSettings(Tab *tab, const QUrl secureOrigin, QWebEnginePage::Feature feature)
{
	m_tab = tab;
	m_secureOrigin = secureOrigin;
	m_feature = feature;
	switch (feature)
	{
		case WebPage::Feature::MouseLock:
			m_titleLabel->setText("Mouse lock");
			break;
		case WebPage::Feature::Geolocation:
			m_titleLabel->setText("Geolocation");
			break;
		case WebPage::Feature::Notifications:
			m_titleLabel->setText("Notifications");
			break;
		case WebPage::Feature::MediaAudioCapture:
			m_titleLabel->setText("Audio capture");
			break;
		case WebPage::Feature::MediaVideoCapture:
			m_titleLabel->setText("Video capture");
			break;
		case WebPage::Feature::DesktopVideoCapture:
			m_titleLabel->setText("Desktop Video capture");
			break;
		case WebPage::Feature::MediaAudioVideoCapture:
			m_titleLabel->setText("Media Audio Video capture");
			break;
		case WebPage::Feature::DesktopAudioVideoCapture:
			m_titleLabel->setText("Desktop Audio Video capture");
			break;
		default:
			throw "OUT OF FEATURES";
	}
}

void FeaturePermissinWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setPen(QPen(Qt::black, 2));
	painter.setBrush(QBrush(Qt::gray));
	painter.drawRect(rect());
}
