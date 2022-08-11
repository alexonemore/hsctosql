#include <QDebug>
#include <QtXml>
#include "database.h"

#include <vector>

int main() try
{
	const QString dbfilename("../hsc_database.xml");
	const QString data_references_filename("../hsc_data_references.txt");
	const QString elements_filename("../hsc_elements.txt");

	Elements dbel(elements_filename);
	DataReferences dbref(data_references_filename);
	Database db(dbfilename);

	for(const auto& i : db) {

	}

#if 0
	dbel.Print("../out_elements.txt");
	dbref.Print("../out_dbrefs.txt");
	db.Print("../out_db.txt");
#endif

	return 0;
} catch(std::exception& e) {
	qDebug() << e.what();
}

// 28 HSC - Databases.pdf
