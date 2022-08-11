#include "database.h"
#include <iostream>
#include <set>

// 28 HSC - Databases.pdf

void CompareSets(const std::set<QString>& set1, const std::set<QString>& set2);

int main() try
{
	Elements dbel("../hsc_elements.txt");
	DataReferences dbref("../hsc_data_references.txt");
	Database db("../hsc_database.xml");

#if 0
	auto set = db.GetElements();
	auto set_el = dbel.GetElements();
	std::cout << "Number of elements in Database: " << set.size() << std::endl;
	std::cout << "Number of elements in Elements: " << set_el.size() <<std::endl;
	std::cout << "\tDatabase\tElements\n";
	CompareSets(set, set_el);
#endif
#if 1
	auto set = db.GetFormulasContainsElement("D");
	for(const auto& i : set) {
		std::cout << i.toStdString() << std::endl;
	}
#endif
#if 1
	dbel.Print("../out_elements.txt");
	dbref.Print("../out_dbrefs.txt");
	db.Print("../out_db.txt");
#endif

	return 0;
} catch(std::exception& e) {
	std::cerr << e.what() << std::endl;
}

void CompareSets(const std::set<QString>& set1, const std::set<QString>& set2)
{
	std::set<QString> merger;
	for(const auto& i : set1) { merger.insert(i); }
	for(const auto& i : set2) { merger.insert(i); }
	for(const auto& i : merger) {
		std::cout << i.toStdString() << "\t" << (set1.count(i) ? "+" : "-")
				  << "\t" << (set2.count(i) ? "+" : "-") << std::endl;
	}
}


