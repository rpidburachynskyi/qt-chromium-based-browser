#ifndef TABSLAYOUT_H
#define TABSLAYOUT_H

#include "tab.h"

#include <QWidget>

class TabsLayout : public QWidget
{
	Q_OBJECT
public:
	explicit TabsLayout(QWidget *parent = nullptr);

	void addTab(Tab *tab);
	void removeTab(Tab *tab);
	void swapTab(Tab *tab1, Tab *tab2);

protected:
	void resizeEvent(QResizeEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

signals:

public slots:
	void placeTabs();

private:
	QList<Tab *> m_tabs;

	int m_spacing;

};

#endif // TABSLAYOUT_H
