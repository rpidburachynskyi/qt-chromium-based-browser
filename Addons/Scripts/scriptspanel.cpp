#include "scriptspanel.h"
#include <QPainter>

ScriptsPanel::ScriptsPanel(QWidget *parent) : QWidget(parent)
{
	m_scriptsLayout = new QHBoxLayout;

	m_scriptsLayout->setSpacing(2);
	m_scriptsLayout->setMargin(1);
	m_scriptsLayout->setAlignment(Qt::AlignLeft);

	setLayout(m_scriptsLayout);
	setFixedHeight(30);

	addScript();
	addScript();
}

void ScriptsPanel::addScript()
{
	Script *script = new Script(this);
	m_scripts.append(script);
	m_scriptsLayout->addWidget(script);
}

void ScriptsPanel::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(Qt::cyan));
	painter.drawRect(rect());
}
