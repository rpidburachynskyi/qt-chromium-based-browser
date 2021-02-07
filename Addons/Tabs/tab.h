#ifndef TAB_H
#define TAB_H

#include "Inhernit/qstandartwidget.h"
#include "tabloadicon.h"
#include "Addons/webpage.h"

#include <QWidget>
#include <QWebEnginePage>
#include <QPropertyAnimation>

class Tab : public QStandartWidget
{
	Q_OBJECT
public:
	explicit Tab(QWidget *parent = nullptr);
	~Tab() override;

	bool isSelected();
	void setSelected(const bool &selected);

	bool isMoving();
	QPoint clickMovePoint() const;

	bool isStartPage();

	WebPage *page();
	QList<QString> messages();

	QMap<QWebEnginePage::Feature *, QWebEnginePage::PermissionPolicy *> *featuresPermissions();
	void setFeaturePermission(const QUrl &secureOrigin, QWebEnginePage::Feature feature, QWebEnginePage::PermissionPolicy policy);

	QPoint futurePos;
	QPropertyAnimation* propertyAnimation() const;

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
	void closeTab();
	void moveToNewWindow();

	void loadPageFromUrl(const QUrl &url);

	void proccessPageAction(const WebPage::WebAction &action);
signals:
	void movedToNewWindow();

	void tabClosed(Tab *tab);
	void clicked(Tab *tab);
	void triggeredContextMenu();

	void triggeredFeaturePermissionRequest(const QUrl &securityOrigin, QWebEnginePage::Feature feature);

	void messageAdded(const QString &msg);

	void updatedPermissions();

	void beginMoved();
	void moved();
	void endMoved();

private:
	bool m_isSelected;
	bool m_isMoving;

	TabLoadIcon *m_loadIcon;

	WebPage *m_webPage;

	QMap<QWebEnginePage::Feature *, QWebEnginePage::PermissionPolicy *> m_featuresPermissions;

	QList<QString> m_consoleMessages;

	QPoint m_clickMovePoint;
	QPropertyAnimation *m_propertyAnimation;

	QString m_getNewPageHTML();

};

#endif // TAB_H
