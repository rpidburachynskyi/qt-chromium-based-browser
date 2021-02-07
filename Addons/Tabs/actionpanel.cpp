#include "actionpanel.h"

#include <QHBoxLayout>
#include <QPainter>

ActionPanel::ActionPanel(QWidget *parent) : QWidget(parent)
{
	m_backButton = new QPushButton("B", this);
	m_forwardButton = new QPushButton("F", this);
	m_reloadButton = new QPushButton("R", this);

	connect(m_backButton, &QPushButton::clicked, [this](){emit triggeredPageAction(WebPage::Back);});
	connect(m_forwardButton, &QPushButton::clicked, [this](){emit triggeredPageAction(WebPage::Forward);});
	connect(m_reloadButton, &QPushButton::clicked, [this](){emit triggeredPageAction(WebPage::Reload);});

	QHBoxLayout *l = new QHBoxLayout(this);

	l->setMargin(3);
	l->setSpacing(0);

	l->addWidget(m_backButton);
	l->addWidget(m_forwardButton);
	l->addWidget(m_reloadButton);


	const int SQ_SIZE = 27;
	m_backButton->setFixedSize(SQ_SIZE, SQ_SIZE);
	m_forwardButton->setFixedSize(SQ_SIZE, SQ_SIZE);
	m_reloadButton->setFixedSize(SQ_SIZE, SQ_SIZE);
}

ActionPanel::~ActionPanel()
{
	delete m_backButton;
	delete m_forwardButton;
	delete m_reloadButton;
}

void ActionPanel::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::yellow));
	painter.drawRect(rect());
}

QPushButton *ActionPanel::reloadButton() const
{
	return m_reloadButton;
}

QPushButton *ActionPanel::forwardButton() const
{
	return m_forwardButton;
}

QPushButton *ActionPanel::backButton() const
{
	return m_backButton;
}
