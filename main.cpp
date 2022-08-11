#include <QDebug>
#include <QtXml>
#include "database.h"

#include <vector>

int main()
{
	const QString dbfilename("../hsc_database.xml");
	const QString data_references_filename("../data_references.txt");

	try {
		DataReferences dbref(data_references_filename);
		dbref.Print("../refs.txt");

		Database db(dbfilename);
		db.PrintNames("../names.txt");
		db.Print("../db.txt");
	} catch(std::exception& ex) {
		qDebug() << ex.what();
	}

	return 0;
}

// 28 HSC - Databases.pdf
