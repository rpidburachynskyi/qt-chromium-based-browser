#ifndef CONSOLETEXTEDIT_H
#define CONSOLETEXTEDIT_H

#include <QTextEdit>

class ConsoleTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	ConsoleTextEdit(QWidget *parent = nullptr);

signals:
	void returnPressed();
protected:
	void keyPressEvent(QKeyEvent *event) override;
};

#endif // CONSOLETEXTEDIT_H
