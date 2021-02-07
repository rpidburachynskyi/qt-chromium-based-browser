#include "consoleeditor.h"

#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QApplication>
#include <QVBoxLayout>

ConsoleEditor::ConsoleEditor(QWidget *parent) : QWidget(parent)
{
	m_textEdit = new ConsoleTextEdit(this);
	QVBoxLayout *l = new QVBoxLayout;
	l->addWidget(m_textEdit);
	setLayout(l);
	setFocusPolicy(Qt::FocusPolicy::StrongFocus);

	connect(m_textEdit, &ConsoleTextEdit::returnPressed, [this]()
	{
		emit this->executeCommand(m_textEdit->toPlainText());
	});
}

void ConsoleEditor::paintEvent(QPaintEvent *event)
{
	QPainter painter (this);
	painter.setBrush(QBrush(Qt::black));
	painter.setPen(QPen(Qt::white));
	painter.drawRect(rect());
	painter.drawText(2, 14, m_command);
}
