#ifndef CLOSETABHISTORY_H
#define CLOSETABHISTORY_H

#include "tab.h"

class CloseTabHistory
{
public:
	CloseTabHistory();

	void addTab(Tab *tab);
	bool hasTabUrl();
	QUrl getTabUrl();

private:
	QVector<QUrl> m_urls;
};

#endif // CLOSETABHISTORY_H
