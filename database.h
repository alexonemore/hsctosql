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

#include <QtSql>
#include <QVector>
#include <QString>
#include <QHash>
#include <unordered_map>
#include <set>

using Composition = std::unordered_map<QString, double>;

#if 0
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
#endif

struct HSCDBTempRange
{
	QString Unit; // Joules always
	QString TemperatureUnit; // Kelvin always
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
	QString suHSCMP; // Melting Point always equal HSCMP
	QString suHSCBP; // Boiling Point always equal HSCBP
	QString OriginDatabase; // Own
	QString SaveDate; // 2022-06-02T11:05:19.1268694+03:00
	QString CAN; // CAS
	QString formula; // Formula
	QString formulaS; // Strucrutal Formula
	QString NameCh; // Chemical Name
	QString NameCo; // Common Name
	QString HSCMP; // Melting Point
	QString HSCBP; // Boiling Point
	QString Unit; // Joules always
	QString TemperatureUnit; // Kelvin always
	QVector<HSCDBTempRange> TempRange;
	Composition composition; // parsed from Formula
	QString suffix;
#if 0
	SubstanceType type;
#endif
};

class Database final
{
	QVector<HSCDBSpecies> data;
public:
	Database(const QString& filename);
	void Print(const QString& filename) const;
	void PrintNames(const QString& filename) const;
	std::set<QString> GetElements() const;
	std::set<QString> GetFormulasContainsElement(const QString& el) const;
	auto begin() const { return data.begin(); }
	auto end() const { return data.end(); }
private:
	void ParseFormulaToComposition();
};

class DataReferences final
{
	struct DataReferencesItem {
		int id;
		QString short_name;
		QString long_name;
	};
	QVector<DataReferencesItem> data;
public:
	DataReferences(const QString& filename);
	void Print(const QString& filename) const;
	QVector<QString> FindLongNames(const QString& short_name) const;
	auto begin() const { return data.begin(); }
	auto end() const { return data.end(); }
};

class Elements final
{
	QVector<QString> properties;
	QVector<QString> property_units;
	QVector<QVector<QString>> values;
	std::unordered_map<QString, double> atomic_weight;
public:
	Elements(const QString& filename);
	void Print(const QString& filename) const;
	void PrintProperties() const;
	void PrintPropertyUnits() const;
	std::set<QString> GetElements() const;
	double GetWeight(const Composition& composition) const;
};

class Colors final
{
	struct Color {
		int id, number;
		QString name;
	};
	QVector<Color> data;
public:
	Colors(const QString& filename);
	const QString& GetColorName(const int number) const;
	auto begin() const { return data.begin(); }
	auto end() const { return data.end(); }
};

class Units final
{
	struct Unit {
		int id;
		QString name, unit_name;
	};
	QVector<Unit> data;
public:
	Units(const QString& filename);
	auto begin() const { return data.begin(); }
	auto end() const { return data.end(); }
};

void ParseFormula(const QString& formula, QString& suffix,
					  Composition& composition);
void ParseFormulaWithoutNestedBrackets(Composition& composition,
						const std::string& text, const double amount1);
void tests();

void SaveToSql(const Database& db, const DataReferences& dbref,
			   const Elements& dbel, const Colors& dbcolor,
			   const Units& dbunit, const QString& filename);

QSqlQuery MakeTable(const QSqlDatabase& sql, const QString& str0, const QString& str1);
void MakeTableSpecies(const QSqlDatabase& sql, const Database& db, const Elements& dbel);
void MakeTableTempRange(const QSqlDatabase& sql, const Database& db);
void MakeTableColor(const QSqlDatabase& sql, const Colors& dbcolor);
void MakeTableCompositionsOfSpecies(const QSqlDatabase& sql, const Database& db, const Elements& dbel);
void MakeTableElements(const QSqlDatabase& sql, const Elements& dbel);
void MakeTableIonicRadiiInCrystalsOxidationState(const QSqlDatabase& sql, const Elements& dbel);
void MakeTableIsotopes(const QSqlDatabase& sql, const Elements& dbel);
void MakeTableState(const QSqlDatabase& sql);
void MakeTableRefs(const QSqlDatabase& sql, const DataReferences& dbref);
void MakeTableTempRangeToReferences(const QSqlDatabase& sql, const Database& db, const DataReferences& dbref);
QString FilenameIncrement(const QString& filename, int precision = 3);

#endif // DATABASE_H
