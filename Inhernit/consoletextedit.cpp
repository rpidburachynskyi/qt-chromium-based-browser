#include "consoletextedit.h"

#include <QKeyEvent>
#include <QApplication>

ConsoleTextEdit::ConsoleTextEdit(QWidget *parent) : QTextEdit (parent)
{

}


void ConsoleTextEdit::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Return && QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
	{
		emit returnPressed();
		setText("");
		return;
	}
	return QTextEdit::keyPressEvent(event);
}
