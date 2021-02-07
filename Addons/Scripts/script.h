#ifndef SCRIPT_H
#define SCRIPT_H

#include <QWidget>

class Script : public QWidget
{
	Q_OBJECT
public:
	explicit Script(QWidget *parent = nullptr);

signals:

public slots:

	// QWidget interface
protected:
	void paintEvent(QPaintEvent *event) override;
};

#endif // SCRIPT_H
