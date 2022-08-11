#include <QDebug>
#include <QtXml>
#include "database.h"

#include <vector>

int main()
{
	const QString dbfilename("../hsc_database.xml");

	try {
		Database db(dbfilename);
		db.PrintNames("../names.txt");
		db.Print("../db.txt");
	} catch(std::exception& ex) {
		qDebug() << ex.what();
	}

	return 0;
}

// 28 HSC - Databases.pdf
