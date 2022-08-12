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

#ifndef DATABASE_H
#define DATABASE_H

#include <QVector>
#include <QString>
#include <QHash>
#include <unordered_map>
#include <set>

using Composition = std::unordered_map<QString, double>;

enum class SubstanceType
{
	normal,		// no suffix
	gas,		// g)
	liquid,		// l)
	solid,		// s)

	// molecules, radicals and ions: H+ = H(+a), OH- = OH(-a), Fe+3 = Fe(+3a)
	// suffix a)
	aqueous,

	// pressure: (60bar), (60barg)
	pressure,

	// ionized species: H(+a), OH(-a), Fe(+3a)
	ion_species,

	// ionized gaseous species: Ar(+g), H2(+g)
	ion_gas

};

struct HSCDBTempRange
{
	QString Unit; // Joules
	QString TemperatureUnit; // Kelvin
	QString HSCTempIndex;
	QString Reference;
	QString HSCT1; // Tmin K
	QString HSCT2; // Tmax K
	QString HSCH; // H kJ/mol
	QString HSCS; // S J/mol*K
	QString HSCA; // A
	QString HSCB; // B
	QString HSCC; // C
	QString HSCD; // D
	QString HSCE; // E
	QString HSCF; // F
	QString HSCDe; // Density kg/l
	QString HSCCo; // Color
	QString HSCSolu; // Solubility in H2O g/l
	QString HSCPhase; // Phase
	QString HSCCl; // Reliability Class
	QString suHSCT1; // Rest in Calories
	QString suHSCT2;
	QString suHSCH;
	QString suHSCS;
	QString suHSCA;
	QString suHSCB;
	QString suHSCC;
	QString suHSCD;
	QString suHSCE;
	QString suHSCF;
};

struct HSCDBSpecies
{
	int id;
	QString suHSCMP; // Melting Point
	QString suHSCBP; // Boiling Point
	QString OriginDatabase; // Own
	QString SaveDate; // 2022-06-02T11:05:19.1268694+03:00
	QString CAN; // CAS
	QString formula; // Formula
	QString formulaS; // Strucrutal Formula
	QString NameCh; // Chemical Name
	QString NameCo; // Common Name
	QString HSCMP; // Melting Point
	QString HSCBP; // Boiling Point
	QString Unit; // Joules
	QString TemperatureUnit; // Kelvin
	QVector<HSCDBTempRange> TempRange;
	Composition composition; // parsed from Formula
	QString suffix;
	//SubstanceType type;
};

class Database final
{
	using DatabaseImpl = QVector<HSCDBSpecies>;
	DatabaseImpl db;
public:
	Database(const QString& filename);
	void Print(const QString& filename) const;
	void PrintNames(const QString& filename) const;
	std::set<QString> GetElements() const;
	std::set<QString> GetFormulasContainsElement(const QString& el) const;
	auto begin() const { return db.begin(); }
	auto end() const { return db.end(); }
private:
	void ParseFormulaToComposition();

};

class DataReferences final
{
	struct DataReferencesItem
	{
		int id;
		QString short_name;
		QString long_name;
	};
	using DataReferencesImpl = QVector<DataReferencesItem>;
	DataReferencesImpl db;
public:
	DataReferences(const QString& filename);
	void Print(const QString& filename) const;
	QVector<QString> FindLongNames(const QString& short_name) const;
};

class Elements final
{
	QVector<QString> properties;
	QVector<QString> property_units;
	QVector<QVector<QString>> values;
public:
	Elements(const QString& filename);
	void Print(const QString& filename) const;
	std::set<QString> GetElements() const;
};


void ParseFormula(const QString& formula, QString& suffix,
					  Composition& composition);
void ParseFormulaWithoutNestedBrackets(Composition& composition,
						const std::string& text, const double amount1);
void tests();

#endif // DATABASE_H
