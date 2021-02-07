#include "Addons/window.h"
#include <Inhernit/urllineedit.h>

#include <QApplication>
#include <QNetworkProxy>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Window *w = new Window();

	//QNetworkProxy::setApplicationProxy(QNetworkProxy(QNetworkProxy::HttpProxy, "93.190.137.11", 1080));

	QFile file("Complete_words.txt");
	if(!file.open(QFile::ReadWrite))
	{
		qDebug() << "ERROR OPEN FILE";
		return 0;
	}
	QTextStream stream(&file);
	UrlLineEdit::AddWordsToCompletted(stream.readAll().split(" "));
	file.close();

	int exec = a.exec();
	file.open(QFile::WriteOnly);
	UrlLineEdit::completterList()->removeDuplicates();
	file.write(UrlLineEdit::completterList()->join(' ').toUtf8());
	file.close();
	return exec;
}
