#include "tabloadicon.h"
#include "tab.h"

#include <QPainter>
#include <QIcon>
#include <QMovie>

TabLoadIcon::TabLoadIcon(QWidget *parent) : QWidget(parent)
{
	m_tab = static_cast<Tab *>(parent);

	m_animationProgress = new QLabel(this);
	setVisible(false);


	connect(m_tab->page(), &WebPage::loadStarted, [this]()
	{
		m_animationProgress->setGeometry(0, 0, width(), height());
		updateProgress(Started);
		setVisible(!m_tab->isStartPage());
	});
	connect(m_tab->page(), &WebPage::loadFinished, [this]()
	{
		m_animationProgress->setGeometry(0, 0, width(), height());
		updateProgress(Finished);
		setVisible(false);
	});
	connect(m_tab->page(), &WebPage::iconChanged, [this](const QIcon &icon)
	{
		if(icon.isNull())
			return setVisible(false);
		else if(!isVisible())
			setVisible(true);
		m_animationProgress->setGeometry(0, 0, width(), height());
		m_animationProgress->setPixmap(icon.pixmap(m_animationProgress->size()));
	});
}


void TabLoadIcon::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::black));
	//painter.drawRect(rect());
}

void TabLoadIcon::updateProgress(const TabLoadIcon::ProgressType &type)
{
	switch (type)
	{
		case Started:
		{
			QMovie *movie = new QMovie(":/gifs/load_animation.gif");
			movie->start();
			movie->setScaledSize(m_animationProgress->size());
			m_animationProgress->setMovie(movie);

			break;
		}
		case Finished:
			m_animationProgress->setMovie(nullptr);
			m_animationProgress->repaint();
			break;
	}
}
