#include "tabslayout.h"

#include <QPainter>
#include <QTimer>
#include <QApplication>
#include <QPropertyAnimation>

TabsLayout::TabsLayout(QWidget *parent) : QWidget(parent)
{
	m_spacing = 3;
}

void TabsLayout::addTab(Tab *tab)
{
	m_tabs.append(tab);
	tab->resize(0,height());
	connect(tab, &Tab::movedToNewWindow, [tab, this]()
	{
		m_tabs.removeOne(tab);
		this->placeTabs();
	});
	connect(tab, &Tab::beginMoved, [this]()
	{
		this->placeTabs();
	});
	connect(tab, &Tab::endMoved, [this]()
	{
		this->placeTabs();
	});
	connect(tab, &Tab::moved, [tab, this]()
	{
//		Tab *t = tab;//static_cast<Tab *>(sender());
//		int center = t->x() + t->clickMovePoint().x();//(t->width() / 2);
//		for(int i = 0; i < m_tabs.size(); i++)
//		{
//			Tab *tt = m_tabs.at(i);
//			if(tt == t)
//				continue;
//			int ttright = tt->futurePos.rx() + (tt->width());
//			int ttleft = tt->futurePos.rx();
//			if(ttright > center && m_tabs.indexOf(tt) < m_tabs.indexOf(t))
//			{
//				this->swapTab(tt, t);
//			}else if(ttleft < center && m_tabs.indexOf(tt) > m_tabs.indexOf(t))
//			{
//				this->swapTab(tt, t);
//			}
//		} // IT WORK

		bool moveRight = false, moveLeft = false;

		int index = m_tabs.indexOf(tab);
		int moveingTabX = m_tabs.at(index)->pos().x() + m_tabs.at(index)->clickMovePoint().x();

		if(m_tabs.size() <= 1)
		{

		}
		else if(index == 0)
		{
				moveRight = true;
		}else if(index == m_tabs.size() - 1)
		{
				moveLeft = true;
		}else if(m_tabs.size() >= 3)
		{
			moveLeft = moveRight = true;
		}

		if(moveRight)
		{
			int rightTabX = m_tabs.at(index + 1)->futurePos.rx();
			if(rightTabX < moveingTabX)
			{
				this->swapTab(m_tabs.at(index), m_tabs.at(index+1));
				moveLeft = false;
			}
		}

		if(moveLeft)
		{
			int leftTabX = m_tabs.at(index - 1)->futurePos.rx() + m_tabs.at(index - 1)->width();
			if(leftTabX > moveingTabX)
			{
				this->swapTab(m_tabs.at(index), m_tabs.at(index-1));
			}
		}
	});

	connect(tab, &Tab::tabClosed, [tab, this]()
	{
		m_tabs.removeOne(tab);
		this->placeTabs();
	});
	tab->setParent(this);
	placeTabs();
}

void TabsLayout::removeTab(Tab *tab)
{
	m_tabs.removeOne(tab);
}

void TabsLayout::swapTab(Tab *tab1, Tab *tab2)
{
	m_tabs.swapItemsAt(m_tabs.indexOf(tab1), m_tabs.indexOf(tab2));
	placeTabs();
}

void TabsLayout::placeTabs()
{
	int count = m_tabs.size();
	if(count == 0)
		return;
	int w = width() - 40;
	int one = w / count - m_spacing;
	int i = -1;

	one = one < 200 ? one : 200;

	QSize size(one, height());

	for(int i = m_tabs.size() - 1; i >= 0; i--)
	{
		Tab *tab = m_tabs.at(i);
		//i++;
		if(tab->isMoving())
			continue;
		tab->setVisible(true);
		QPoint pos(i * (one + m_spacing), 0);
		if(tab->futurePos != pos || tab->pos() != tab->futurePos)
		{
			QPropertyAnimation* anim = new QPropertyAnimation(tab, "pos", this);
			anim->setEasingCurve(QEasingCurve::InExpo);
			anim->setStartValue(tab->pos());
			anim->setEndValue(tab->futurePos = pos);
			anim->setDuration(500);
			anim->start();
			connect(anim, &QPropertyAnimation::finished, anim, &QPropertyAnimation::deleteLater);
		}

		if(tab->size() != size)
		{
			tab->propertyAnimation()->stop();
			tab->propertyAnimation()->setPropertyName("size");
			tab->propertyAnimation()->setEasingCurve(QEasingCurve::OutQuad);
			tab->propertyAnimation()->setStartValue(tab->size());
			tab->propertyAnimation()->setEndValue(size);
			tab->propertyAnimation()->setDuration(500);
			tab->propertyAnimation()->start();
		}
	}
}

void TabsLayout::resizeEvent(QResizeEvent *event)
{
	placeTabs();
}

void TabsLayout::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::black));
	painter.drawRect(rect());
}
