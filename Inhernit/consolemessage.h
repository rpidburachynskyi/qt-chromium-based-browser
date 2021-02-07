#ifndef CONSOLEMESSAGE_H
#define CONSOLEMESSAGE_H

#include <QWidget>

class ConsoleMessage : public QWidget
{
	Q_OBJECT
public:
	explicit ConsoleMessage(QWidget *parent = nullptr);

	void setMessage(const QString &message);
signals:

public slots:

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	QString m_message;
};

#endif // CONSOLEMESSAGE_H
