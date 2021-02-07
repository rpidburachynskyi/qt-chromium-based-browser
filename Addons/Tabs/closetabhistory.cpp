#include "closetabhistory.h"

CloseTabHistory::CloseTabHistory()
{

}

void CloseTabHistory::addTab(Tab *tab)
{
	m_urls.push_back(tab->page()->url());
}

bool CloseTabHistory::hasTabUrl()
{
	return !m_urls.isEmpty();
}

QUrl CloseTabHistory::getTabUrl()
{
	QUrl url = m_urls.last();
	m_urls.pop_back();
	return url;
}
