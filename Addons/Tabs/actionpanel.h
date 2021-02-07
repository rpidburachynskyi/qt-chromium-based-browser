#ifndef ACTIONPANEL_H
#define ACTIONPANEL_H

#include "Addons/webpage.h"

#include <QWidget>
#include <QPushButton>

class ActionPanel : public QWidget
{
	Q_OBJECT
public:
	explicit ActionPanel(QWidget *parent = nullptr);
	~ActionPanel() override;

	QPushButton *backButton() const;

	QPushButton *forwardButton() const;

	QPushButton *reloadButton() const;

protected:
	void paintEvent(QPaintEvent *event) override;

signals:
	void triggeredPageAction(const WebPage::WebAction &action);

public slots:

private:
	QPushButton *m_backButton;
	QPushButton *m_forwardButton;
	QPushButton *m_reloadButton;

};

#endif // ACTIONPANEL_H
