#ifndef CONSOLEEDITOR_H
#define CONSOLEEDITOR_H

#include "Inhernit/consoletextedit.h"

#include <QWidget>
#include <QTextEdit>

class ConsoleEditor : public QWidget
{
	Q_OBJECT
public:
	explicit ConsoleEditor(QWidget *parent = nullptr);

signals:
	void executeCommand(const QString &command);

public slots:


protected:
	void paintEvent(QPaintEvent *event) override;

private:
	QString m_command;
	ConsoleTextEdit *m_textEdit;
};

#endif // CONSOLEEDITOR_H
