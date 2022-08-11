#include <QDebug>
#include <QtXml>
#include "database.h"

#include <vector>

int main()
{
	const QString dbfilename("../hsc_database.xml");
	const QString data_references_filename("../hsc_data_references.txt");
	const QString elements_filename("../hsc_elements.txt");

	try {
		Elements dbel(elements_filename);
		dbel.Print("../out_elements.txt");

		DataReferences dbref(data_references_filename);
		dbref.Print("../out_dbrefs.txt");

		Database db(dbfilename);
		//db.PrintNames("../out_names.txt");
		db.Print("../out_db.txt");


	} catch(std::exception& ex) {
		qDebug() << ex.what();
	}

	return 0;
}

// 28 HSC - Databases.pdf
