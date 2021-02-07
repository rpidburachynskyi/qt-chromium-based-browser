#ifndef TABLOADBAR_H
#define TABLOADBAR_H

#include <QWidget>
#include <QLabel>

class Tab;

class TabLoadIcon : public QWidget
{
	Q_OBJECT
public:

	enum ProgressType
	{
		Started,
		Finished
	};
	explicit TabLoadIcon(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;
signals:

public slots:
	void updateProgress(const ProgressType &type);

private:
	QLabel *m_animationProgress;
	Tab *m_tab;
};

#endif // TABLOADBAR_H
