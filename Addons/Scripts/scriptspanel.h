#ifndef SCRIPTSPANEL_H
#define SCRIPTSPANEL_H

#include "Addons/Scripts/script.h"

#include <QWidget>
#include <QHBoxLayout>
class ScriptsPanel : public QWidget
{
	Q_OBJECT
public:
	explicit ScriptsPanel(QWidget *parent = nullptr);

signals:

public slots:
	void addScript();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	QList<Script *> m_scripts;
	QHBoxLayout *m_scriptsLayout;
};

#endif // SCRIPTSPANEL_H
