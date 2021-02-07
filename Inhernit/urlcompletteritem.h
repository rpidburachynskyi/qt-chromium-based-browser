#ifndef URLCOMPLETTERITEM_H
#define URLCOMPLETTERITEM_H

#include <QWidget>

class UrlCompletterItem : public QWidget
{
	Q_OBJECT
public:
	explicit UrlCompletterItem(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;
signals:

public slots:

};

#endif // URLCOMPLETTERITEM_H
