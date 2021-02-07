#ifndef URLLINEEDIT_H
#define URLLINEEDIT_H

#include "urlcompletteritem.h"

#include <QLineEdit>
#include <QCompleter>
#include <QStringListModel>

class UrlLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	UrlLineEdit(QWidget *parent = nullptr);

	void keyPressEvent(QKeyEvent *event) override;

	static void AddWordToCompletted(const QString &word);
	static void AddWordsToCompletted(const QStringList &list);
	static QStringList *completterList();

signals:
	void triggeredEnter(const QUrl &url);
private:
	QCompleter *m_completter;

	static QStringList m_completterList;
	static QStringListModel m_completterModel;

	QList<UrlCompletterItem *> m_completterItems;
};

#endif // URLLINEEDIT_H
