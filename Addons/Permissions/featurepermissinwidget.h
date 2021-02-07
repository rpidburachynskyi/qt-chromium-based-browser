#ifndef FEATUREPERMISSINWIDGET_H
#define FEATUREPERMISSINWIDGET_H

#include "Addons/Tabs/tab.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QWebEnginePage>

class FeaturePermissinWidget : public QWidget
{
	Q_OBJECT
public:
	explicit FeaturePermissinWidget(QWidget *parent = nullptr);

signals:
	void solutionButtonClicked(const QUrl &secureOrigin, QWebEnginePage::Feature feature, int answer);

public slots:
	void setSettings(Tab *tab, const QUrl secureOrigin, QWebEnginePage::Feature feature);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	Tab *m_tab;

	QUrl m_secureOrigin;
	QWebEnginePage::Feature m_feature;

	QLabel *m_titleLabel;

	QPushButton *m_yesButton;
	QPushButton *m_noButton;
};

#endif // FEATUREPERMISSINWIDGET_H
