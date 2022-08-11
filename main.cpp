#include <QDebug>
#include "database.h"

#include <set>

int main() try
{
	Elements dbel("../hsc_elements.txt");
	DataReferences dbref("../hsc_data_references.txt");
	Database db("../hsc_database.xml");

	std::set<QString> set;
#if 0
	for(const auto& i : db) {
		set.insert(i.suffix);
	}
	qDebug() << "Number of suffixes:" << set.size();
	for(auto&& i : set) { qDebug() << i; }
#elif 1
	set.clear();
	for(const auto& i : db) {
		for(const auto& j : i.composition) {
			set.insert(j.first);
		}
	}
	qDebug() << "Number of elements:" << set.size();
	for(auto&& i : set) { qDebug() << i; }
#endif

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
