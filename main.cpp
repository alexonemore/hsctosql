/* This file is part of HSCToSQL (Database converter).
 * Copyright (c) 2022 Alexandr Shchukin
 * Corresponding email: shchukin@ism.ac.ru
 *
 * HSCToSQL (Database converter) is free software:
 * you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * HSCToSQL (Database converter) is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSCToSQL (Database converter).
 * If not, see <http://www.gnu.org/licenses/>.*/

#include "database.h"
#include <iostream>
#include <set>

// 28 HSC - Databases.pdf

void CompareSets(const std::set<QString>& set1, const std::set<QString>& set2);
void CompareElements(const Database& db, const Elements& dbel);
void PrintFormulasContainsElement(const Database& db, const QString& element);
void PrintOutFiles(const Database& db, const Elements& dbel,
				   const DataReferences& dbref, const QString& prefix_path);
void CheckSuEqualNonSu(const Database& db);
void CheckUnits(const Database& db);

int main() try
{
	Elements dbel("../hsc_elements.txt");
	DataReferences dbref("../hsc_data_references.txt");
	Database db("../hsc_database.xml");

	CheckSuEqualNonSu(db);
	CheckUnits(db);

	dbel.PrintProperties();
	dbel.PrintPropertyUnits();

#ifdef NDEBUG
	CompareElements(db, dbel);
	PrintFormulasContainsElement(db, "T");
	PrintOutFiles(db, dbel, dbref, "../");
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

void CompareElements(const Database& db, const Elements& dbel)
{
	auto set = db.GetElements();
	auto set_el = dbel.GetElements();
	std::cout << "Number of elements in Database: " << set.size() << std::endl;
	std::cout << "Number of elements in Elements: " << set_el.size() <<std::endl;
	std::cout << "\tDatabase\tElements\n";
	CompareSets(set, set_el);
}

void PrintFormulasContainsElement(const Database& db, const QString& element)
{
	auto set = db.GetFormulasContainsElement(element);
	for(const auto& i : set) {
		std::cout << i.toStdString() << std::endl;
	}
}

void PrintOutFiles(const Database& db, const Elements& dbel,
				   const DataReferences& dbref, const QString& prefix_path)
{
	dbel.Print(prefix_path + "out_elements.txt");
	dbref.Print(prefix_path + "out_dbrefs.txt");
	db.Print(prefix_path + "out_db.txt");
}

void CheckSuEqualNonSu(const Database& db)
{
	for(const auto& i : db) {
		if(i.suHSCMP != i.HSCMP) {
			std::cout << "MP: " << i.formula.toStdString() << std::endl;
			throw std::exception("suHSCMP");
		}
		if(i.suHSCBP != i.HSCBP) {
			std::cout << "BP: " << i.formula.toStdString() << std::endl;
			throw std::exception("suHSCBP");
		}
		for(const auto& temprange : i.TempRange) {
			if(temprange.suHSCT1 != temprange.HSCT1) {
				std::cout << "suHSCT1: " << i.formula.toStdString() << std::endl;
				throw std::exception("suHSCT1");
			}
			if(temprange.suHSCT2 != temprange.HSCT2) {
				std::cout << "suHSCT2: " << i.formula.toStdString() << std::endl;
				throw std::exception("suHSCT2");
			}
		}
	}
}

void CheckUnits(const Database& db)
{
	QString joules("Joules");
	QString kelvin("Kelvin");

	for(const auto& i : db) {
		if(i.Unit != joules) {
			std::cout << "Species Units: " << i.Unit.toStdString()
					  << " in " << i.formula.toStdString() << std::endl;
			throw std::exception("SpeciesUnits");
		}
		if(i.TemperatureUnit != kelvin) {
			std::cout << "Species TemperatureUnit: " << i.Unit.toStdString()
					  << " in " << i.formula.toStdString() << std::endl;
			throw std::exception("SpeciesTemperatureUnit");
		}
		for(const auto& temprange : i.TempRange) {
			if(temprange.Unit != joules) {
				std::cout << "TempRange Units: " << temprange.Unit.toStdString()
						  << " in " << i.formula.toStdString() << std::endl;
				throw std::exception("TempRangeUnits");
			}
			if(temprange.TemperatureUnit != kelvin) {
				std::cout << "TempRange TemperatureUnit: "
						  << temprange.TemperatureUnit.toStdString()
						  << " in " << i.formula.toStdString() << std::endl;
				throw std::exception("TempRangeTemperatureUnit");
			}
		}
	}
}


