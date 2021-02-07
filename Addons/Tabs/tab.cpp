#include "tab.h"
#include "Addons/window.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QFile>
#include <QTimer>
#include <QGradient>
#include <QWebEngineHistory>
#include <QWebEngineSettings>
#include <QPropertyAnimation>
#include <QMapIterator>
#include <QPropertyAnimation>

Tab::Tab(QWidget *parent) : QStandartWidget (parent)
{
	m_isMoving = false;
	m_isSelected = false;

	m_propertyAnimation = new QPropertyAnimation(this);
	m_propertyAnimation->setTargetObject(this);

	m_webPage = new WebPage(this); // FIXIT
	m_webPage->setHtml(m_getNewPageHTML());

	m_loadIcon = new TabLoadIcon(this);
	m_loadIcon->setGeometry(5,5, 20, 20);

	connect(m_webPage, &WebPage::titleChanged, this, static_cast<void (Tab::*)(void)>(&Tab::repaint));
	connect(m_webPage, &WebPage::loadFinished, [this](){this->setToolTip(m_webPage->title());});
	connect(m_webPage, &WebPage::messageAdded, [this](const QString &message)
	{
		emit messageAdded(message);
		m_consoleMessages.append(message);
	});
	connect(m_webPage, &WebPage::featurePermissionRequested, [this](const QUrl &securityOrigin, QWebEnginePage::Feature feature)
	{
		for(auto key : m_featuresPermissions.keys())
		{
			if(*key == feature)
			{
				switch (* m_featuresPermissions.value(key))
				{
					case WebPage::PermissionGrantedByUser:
						m_webPage->setFeaturePermission(securityOrigin, feature, WebPage::PermissionGrantedByUser);
						break;
					case WebPage::PermissionDeniedByUser:
						m_webPage->setFeaturePermission(securityOrigin, feature, WebPage::PermissionDeniedByUser);
						break;
					default:
						emit this->triggeredFeaturePermissionRequest(securityOrigin, feature);
						break;

				}
			}
		}

	});
	connect(m_webPage, &WebPage::featurePermissionRequestCanceled, [this](const QUrl &securityOrigin, QWebEnginePage::Feature feature)
	{
		qDebug() << securityOrigin;
		qDebug() << feature;
	});

	m_featuresPermissions[new WebPage::Feature(WebPage::Feature::MouseLock)] = new WebPage::PermissionPolicy(WebPage::PermissionPolicy::PermissionUnknown);
	m_featuresPermissions[new WebPage::Feature(WebPage::Feature::Geolocation)] = new WebPage::PermissionPolicy(WebPage::PermissionPolicy::PermissionUnknown);
	m_featuresPermissions[new WebPage::Feature(WebPage::Feature::Notifications)] = new WebPage::PermissionPolicy(WebPage::PermissionPolicy::PermissionUnknown);
	m_featuresPermissions[new WebPage::Feature(WebPage::Feature::MediaAudioCapture)] = new WebPage::PermissionPolicy(WebPage::PermissionPolicy::PermissionUnknown);
	m_featuresPermissions[new WebPage::Feature(WebPage::Feature::MediaVideoCapture)] = new WebPage::PermissionPolicy(WebPage::PermissionPolicy::PermissionUnknown);
	m_featuresPermissions[new WebPage::Feature(WebPage::Feature::DesktopVideoCapture)] = new WebPage::PermissionPolicy(WebPage::PermissionPolicy::PermissionUnknown);
	m_featuresPermissions[new WebPage::Feature(WebPage::Feature::MediaAudioVideoCapture)] = new WebPage::PermissionPolicy(WebPage::PermissionPolicy::PermissionUnknown);
	m_featuresPermissions[new WebPage::Feature(WebPage::Feature::DesktopAudioVideoCapture)] = new WebPage::PermissionPolicy(WebPage::PermissionPolicy::PermissionUnknown);

	setMouseTracking(true);
}

Tab::~Tab()
{
	if(m_webPage)
		delete m_webPage;

	delete m_propertyAnimation;

	QMapIterator<QWebEnginePage::Feature *, QWebEnginePage::PermissionPolicy *> it (m_featuresPermissions);
	while (it.hasNext()) {
		it.next();
		delete it.value();
		delete it.key();
	}
}

bool Tab::isSelected()
{
	return m_isSelected;
}

void Tab::setSelected(const bool &selected)
{
	m_isSelected = selected;

}

bool Tab::isMoving()
{
	return m_isMoving;
}

bool Tab::isStartPage()
{
	return !m_webPage->history()->canGoBack();
}

WebPage *Tab::page()
{
	return m_webPage;
}

QList<QString> Tab::messages()
{
	return m_consoleMessages;
}

void Tab::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QColor color;
	if(m_isSelected)
		color = Qt::yellow;
	else
		color = Qt::red;

	QRadialGradient gr(mapFromGlobal(QCursor::pos()), 100);
	gr.setColorAt(0, Qt::white);
	gr.setColorAt(1, color);
	painter.setBrush(QBrush(gr));

	painter.setPen(QPen(Qt::black));
	painter.drawRect(rect());
	painter.setFont(QFont("Arial", 10));
	if(m_webPage == nullptr)
		return;
	if(m_loadIcon->isVisible())
		painter.drawText(m_loadIcon->width() + 10, height() * 2/4, m_webPage->title());
	else
		painter.drawText(10, height() * 2/4, m_webPage->title());

	QWidget::paintEvent(event);
}

void Tab::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_clickMovePoint = event->pos();
	}else if(event->button() == Qt::RightButton)
	{
		emit triggeredContextMenu();
	}
}

void Tab::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		if(!m_isMoving)
		{
			clicked(this);
		}else
		{
			m_isMoving = false;
			emit endMoved();
		}
	}
	repaint();
}

void Tab::mouseMoveEvent(QMouseEvent *event)
{
	if(event->buttons().testFlag(Qt::LeftButton))
	{
		if(m_isMoving)
		{
			emit moved();
		}else
		{
			raise();
			m_isMoving = true;
			emit beginMoved();
		}
		int x = (QCursor::pos() - rootWidget()->pos()  - m_clickMovePoint).x();
		x = x > parentWidget()->width() - width() - 40 ? parentWidget()->width() - width() - 40 : x;
		move(QPoint(x, pos().ry()));
	}
	rootWidget()->repaint();
}

void Tab::closeTab()
{
	emit tabClosed(this);
	delete m_webPage;
	m_webPage = nullptr;
	QPropertyAnimation* anim = new QPropertyAnimation(this, "maximumWidth");
	anim->setStartValue(width());
	anim->setEndValue(0);
	anim->setDuration(300);
	anim->setEasingCurve(QEasingCurve::OutCubic);
	anim->start();
	connect(anim, &QPropertyAnimation::finished, anim, &QPropertyAnimation::deleteLater);
	connect(anim, &QPropertyAnimation::finished, this, &Tab::deleteLater);
}

void Tab::moveToNewWindow()
{
	emit movedToNewWindow();
	move(0,0);
	new Window(this);
}

void Tab::loadPageFromUrl(const QUrl &url)
{
	m_webPage->load(url);
}

void Tab::proccessPageAction(const QWebEnginePage::WebAction &action)
{
	switch (action)
	{
		case WebPage::Back:
		case WebPage::Forward:
		case WebPage::Reload:
			m_webPage->triggerAction(action);
			break;
		default:
			throw "Other webactions not used here";
	}
}

QPropertyAnimation *Tab::propertyAnimation() const
{
	return m_propertyAnimation;
}

QPoint Tab::clickMovePoint() const
{
	return m_clickMovePoint;
}

QMap<QWebEnginePage::Feature *, QWebEnginePage::PermissionPolicy *> *Tab::featuresPermissions()
{
	return &m_featuresPermissions;
}

void Tab::setFeaturePermission(const QUrl &secureOrigin, QWebEnginePage::Feature feature, QWebEnginePage::PermissionPolicy policy)
{
	for(auto key : m_featuresPermissions.keys())
	{
		if(*key == feature)
		{
			auto f = m_featuresPermissions.value(key);
			*f = policy;
			page()->setFeaturePermission(secureOrigin, feature, policy);
			emit updatedPermissions();
			break;
		}
	}
}

QString Tab::m_getNewPageHTML()
{
	QFile file("newpage.html"); // FIXIT
	file.open(QFile::ReadWrite);
	return file.readAll();
}
