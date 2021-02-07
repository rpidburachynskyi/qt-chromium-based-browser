#include "urllineedit.h"

#include <QKeyEvent>
#include <QApplication>
#include <QDebug>

QStringList UrlLineEdit::m_completterList = QStringList() << "Rostik" << "Tawer";
QStringListModel UrlLineEdit::m_completterModel;

UrlLineEdit::UrlLineEdit(QWidget *parent) : QLineEdit (parent)
{
	m_completter = new QCompleter(this);

	m_completter->setMaxVisibleItems(6);
	m_completter->setModel(&m_completterModel);
	m_completter->setCompletionMode(QCompleter::CompletionMode::PopupCompletion);

	m_completterModel.setStringList(m_completterList);

	setCompleter(m_completter);

	connect(this, &UrlLineEdit::textChanged, [this](const QString &text)
	{
		return;
		for(int i = 0; i < m_completterItems.size(); i++)
			delete m_completterItems.at(i);
		m_completterItems.clear();
		for(int i = 0; i < m_completterList.count() && m_completterItems.size() < 6; i++)
		{
			if(m_completterList.at(i).contains(text))
			{
				UrlCompletterItem *item = new UrlCompletterItem(this);
				item->setFixedSize(width(), 40);
				item->move(mapToGlobal(pos()).x(), mapToGlobal(pos()).y() + 40 * (m_completterItems.size() ));
				item->show();
				m_completterItems.append(item);
			}
		}
	});

	setFixedHeight(30);
	setMinimumWidth(250);
}

void UrlLineEdit::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
	{
		AddWordToCompletted(text());
		emit triggeredEnter(QUrl(text()));
	}
	QLineEdit::keyPressEvent(event);
}

void UrlLineEdit::AddWordToCompletted(const QString &word)
{
	if(!m_completterList.contains(word))
		m_completterList.append(word);
	m_completterModel.setStringList(m_completterList);
}

void UrlLineEdit::AddWordsToCompletted(const QStringList &list)
{
	m_completterList += list;
	m_completterList.removeDuplicates();
	m_completterModel.setStringList(m_completterList);
}

QStringList *UrlLineEdit::completterList()
{
	return &m_completterList;
}
