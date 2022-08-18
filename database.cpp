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
#include <QFile>
#include <QtXml>
#include <regex>
#include <iostream>
#include <exception>

Database::Database(const QString& filename)
{
	tests();
	QFile file(filename);
	if(file.open(QIODevice::ReadOnly)) {
		QXmlStreamReader sr(&file);
		auto get_next_character = [&sr](){
			auto type = sr.readNext();
			if(type == QXmlStreamReader::TokenType::Characters) {
				return sr.text().toString().trimmed();
			}
			else if(type == QXmlStreamReader::TokenType::EndElement) {
				return QString{};
			} else {
				QString str("ERROR get_next_character: ");
				str += sr.tokenString() + " " + sr.name() + " " + sr.text();
				throw std::exception(str.toStdString().c_str());
			}
		};
		bool in_temp_range{false};
		do{
			auto type = sr.readNext();
			auto name = sr.name();

			if(type == QXmlStreamReader::TokenType::EndElement &&
					name == QStringLiteral("TempRange")) {
				in_temp_range = false;
			}

			if(type != QXmlStreamReader::TokenType::StartElement) {
				continue;
			}

			if(!in_temp_range && name == QStringLiteral("HSCDBSpecies")) { data.push_back(HSCDBSpecies{}); }
			else if(!in_temp_range && name == QStringLiteral("suHSCMP")) { data.last().suHSCMP = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("suHSCBP")) { data.last().suHSCBP = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("OriginDatabase")) { data.last().OriginDatabase = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("SaveDate")) { data.last().SaveDate = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("CAN")) { data.last().CAN = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("formula")) { data.last().formula = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("FormulaS")) { data.last().formulaS = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("NameCh")) { data.last().NameCh = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("NameCo")) { data.last().NameCo = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("HSCMP")) { data.last().HSCMP = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("HSCBP")) { data.last().HSCBP = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("Unit")) { data.last().Unit = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("TemperatureUnit")) { data.last().TemperatureUnit = get_next_character(); }

			else if(!in_temp_range && name == QStringLiteral("TempRange")) { in_temp_range = true; }

			else if(in_temp_range && name == QStringLiteral("HSCDBTempRange")) { data.last().TempRange.push_back(HSCDBTempRange{}); }

			else if(in_temp_range && name == QStringLiteral("Unit")) { data.last().TempRange.last().Unit = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("TemperatureUnit")) { data.last().TempRange.last().TemperatureUnit = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCTempIndex")) { data.last().TempRange.last().HSCTempIndex = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("Reference")) { data.last().TempRange.last().Reference = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCT1")) { data.last().TempRange.last().HSCT1 = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCT2")) { data.last().TempRange.last().HSCT2 = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCH")) { data.last().TempRange.last().HSCH = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCS")) { data.last().TempRange.last().HSCS = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCA")) { data.last().TempRange.last().HSCA = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCB")) { data.last().TempRange.last().HSCB = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCC")) { data.last().TempRange.last().HSCC = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCD")) { data.last().TempRange.last().HSCD = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCE")) { data.last().TempRange.last().HSCE = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCF")) { data.last().TempRange.last().HSCF = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCDe")) { data.last().TempRange.last().HSCDe = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCCo")) { data.last().TempRange.last().HSCCo = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCSolu")) { data.last().TempRange.last().HSCSolu = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCPhase")) { data.last().TempRange.last().HSCPhase = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCCl")) { data.last().TempRange.last().HSCCl = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCT1")) { data.last().TempRange.last().suHSCT1 = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCT2")) { data.last().TempRange.last().suHSCT2 = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCH")) { data.last().TempRange.last().suHSCH = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCS")) { data.last().TempRange.last().suHSCS = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCA")) { data.last().TempRange.last().suHSCA = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCB")) { data.last().TempRange.last().suHSCB = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCC")) { data.last().TempRange.last().suHSCC = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCD")) { data.last().TempRange.last().suHSCD = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCE")) { data.last().TempRange.last().suHSCE = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCF")) { data.last().TempRange.last().suHSCF = get_next_character(); }

		} while(!sr.atEnd());
		if(sr.hasError()) {
			QString str("ERROR QXmlStreamReader: ");
			str += sr.errorString();
			throw std::exception(str.toStdString().c_str());
		}
		file.close();
	}
	int i{1};
	for(auto&& d : data) {
		d.id = i++;
	}

	ParseFormulaToComposition();
}

void Database::Print(const QString& filename) const
{
	if(!filename.isEmpty()) {
		QFile file(filename);
		if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			QTextStream stream(&file);
			for(auto&& i : data) {
				stream << "id" << " " << i.id << "\n";
				stream << "suHSCMP" << " " << i.suHSCMP << "\n";
				stream << "suHSCBP" << " " << i.suHSCBP << "\n";
				stream << "OriginDatabase" << " " << i.OriginDatabase << "\n";
				stream << "SaveDate" << " " << i.SaveDate << "\n";
				stream << "CAN" << " " << i.CAN << "\n";
				stream << "formula" << " " << i.formula << "\n";
				stream << "formulaS" << " " << i.formulaS << "\n";
				stream << "NameCh" << " " << i.NameCh << "\n";
				stream << "NameCo" << " " << i.NameCo << "\n";
				stream << "HSCMP" << " " << i.HSCMP << "\n";
				stream << "HSCBP" << " " << i.HSCBP << "\n";
				stream << "Unit" << " " << i.Unit << "\n";
				stream << "TemperatureUnit" << " " << i.TemperatureUnit << "\n";
				stream << "Suffix " << i.suffix << "\n";
				for(auto&& t : i.TempRange) {
					stream << "\tUnit" << " " << t.Unit << "\n";
					stream << "\tTemperatureUnit" << " " << t.TemperatureUnit << "\n";
					stream << "\tHSCTempIndex" << " " << t.HSCTempIndex << "\n";
					stream << "\tReference" << " " << t.Reference << "\n";
					stream << "\tHSCT1" << " " << t.HSCT1 << "\n";
					stream << "\tHSCT2" << " " << t.HSCT2 << "\n";
					stream << "\tHSCH" << " " << t.HSCH << "\n";
					stream << "\tHSCS" << " " << t.HSCS << "\n";
					stream << "\tHSCA" << " " << t.HSCA << "\n";
					stream << "\tHSCB" << " " << t.HSCB << "\n";
					stream << "\tHSCC" << " " << t.HSCC << "\n";
					stream << "\tHSCD" << " " << t.HSCD << "\n";
					stream << "\tHSCE" << " " << t.HSCE << "\n";
					stream << "\tHSCF" << " " << t.HSCF << "\n";
					stream << "\tHSCDe" << " " << t.HSCDe << "\n";
					stream << "\tHSCCo" << " " << t.HSCCo << "\n";
					stream << "\tHSCSolu" << " " << t.HSCSolu << "\n";
					stream << "\tHSCPhase" << " " << t.HSCPhase << "\n";
					stream << "\tHSCCl" << " " << t.HSCCl << "\n";
					stream << "\tsuHSCT1" << " " << t.suHSCT1 << "\n";
					stream << "\tsuHSCT2" << " " << t.suHSCT2 << "\n";
					stream << "\tsuHSCH" << " " << t.suHSCH << "\n";
					stream << "\tsuHSCS" << " " << t.suHSCS << "\n";
					stream << "\tsuHSCA" << " " << t.suHSCA << "\n";
					stream << "\tsuHSCB" << " " << t.suHSCB << "\n";
					stream << "\tsuHSCC" << " " << t.suHSCC << "\n";
					stream << "\tsuHSCD" << " " << t.suHSCD << "\n";
					stream << "\tsuHSCE" << " " << t.suHSCE << "\n";
					stream << "\tsuHSCF" << " " << t.suHSCF << "\n";
				}
				for(auto&& [element, amount] : i.composition) {
					stream << "\t\t" << element << " " << amount << "\n";
				}
			}
		}
		file.close();
	}
}

void Database::PrintNames(const QString& filename) const
{
	if(!filename.isEmpty()) {
		QFile file(filename);
		if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			QTextStream stream(&file);
			for(auto&& i : data) {
				stream << i.formula + QStringLiteral("\t[");
				for(auto&& [element, amount] : i.composition) {
					stream << element << QStringLiteral(":") << amount << QStringLiteral(" ");
				}
				stream << QStringLiteral("] {")
					   << i.suffix << QStringLiteral("}\n");
			}
		}
		file.close();
	}
}

std::set<QString> Database::GetElements() const
{
	std::set<QString> set;
	for(const auto& i : data) {
		for(const auto& j : i.composition) {
			set.insert(j.first);
		}
	}
	return set;
}

std::set<QString> Database::GetFormulasContainsElement(const QString& el) const
{
	std::set<QString> set;
	for(const auto& i : data) {
		if(i.composition.count(el)) set.insert(i.formula);
	}
	return set;
}

void Database::ParseFormulaToComposition()
{
	for(auto&& i : data) {
		ParseFormula(i.formula, i.suffix, i.composition);
	}
}

bool contain_nested_brackets(const std::string& text)
{
	int bracket{0};
	int max{0};
	for(auto&& c : text) {
		if(c == '(') ++bracket;
		else if(c == ')') --bracket;
		max = std::max(max, bracket);
	}
	if(max > 2) {
		std::string t("Depth of nested brackets more than 2 in: ");
		t.append(text);
		throw std::exception(t.c_str());
	}
	if(max == 2) return true;
	else return false;
};

void ParseFormula(const QString& formula, QString& suffix,
					  Composition& composition)
{
	// I think parenthesis at the end of a formula is always suffix
	auto formula_copy = formula;
	if(formula_copy.endsWith(")")) {
		auto index = formula_copy.lastIndexOf("(");
		suffix = formula_copy.mid(index+1).chopped(1); // get suffix
		formula_copy.truncate(index); // delete suffix from formula
	}

	// then we should get rid of asterisks * in text
	// H3PO4*0.5H2O	=> [ H3PO4 :1    H2O   :0.5 ]
	// *3Gd2O3*WO3	=> [ WO3   :1    Gd2O3 :3   ]
	auto str = formula_copy.toStdString();
	std::vector<std::pair<std::string, double>> asterisk_separated_vec;
	const static std::regex asterisk_separator("([\\*]*)([0-9\\.]*)([A-Za-z0-9\\.\\(\\)\\'\\+\\-]+)");
	auto pos1 = std::sregex_iterator(str.begin(), str.end(), asterisk_separator);
	auto end1 = std::sregex_iterator();
	for(; pos1 != end1; ++pos1) {
		//auto&& m1 = pos1->str(1); // asterisk *
		auto&& m2 = pos1->str(2);   // number
		auto&& m3 = pos1->str(3);   // part of formula
		auto amount1 = m2.empty() ? 1.0 : std::stod(m2);
		asterisk_separated_vec.emplace_back(m3, amount1);
	}

	// but we still have parentheses
	// Co*6(NH3)*N3(+2a) =>	[Co:1 N3:1 (NH3):6 ]
	// (Co(NH3)5Cl)Cl2	 => [(Co(NH3)5Cl)Cl2:1 ]

	const static std::regex nested_brackets("([A-Za-z0-9\\.]*)(\\(([A-Za-z0-9\\.]*?\\([A-Za-z0-9\\.]*?\\)[A-Za-z0-9\\.]*?)\\)([0-9\\.]*))([A-Za-z0-9\\.]*)");

	for(auto&& [text, amount1] : asterisk_separated_vec) {
		if(contain_nested_brackets(text)) {
			// (Co(NH3)6)Br3, (Co(NH3)5Cl)Cl2, K2Sr(B4O5(OH)4)2
			std::smatch m;
			if(!std::regex_match(text, m, nested_brackets)) throw std::exception("Error in regex match in nested brackets");
			//auto&& m0 = m[0];		// K2Sr(B4O5(OH)4)2Mo4
			auto&& m1 = m[1].str(); // K2Sr
			//auto&& m2 = m[2];		// (B4O5(OH)4)2
			auto&& m3 = m[3].str(); // B4O5(OH)4
			auto&& m4 = m[4].str(); // 2
			auto&& m5 = m[5].str(); // Mo4
			auto amount_koef = m4.empty() ? 1.0 : std::stod(m4);
			if(!m1.empty()) {
				ParseFormulaWithoutNestedBrackets(composition, m1, amount1);
			}
			if(!m3.empty()) {
				ParseFormulaWithoutNestedBrackets(composition, m3, amount1*amount_koef);
			}
			if(!m5.empty()) {
				ParseFormulaWithoutNestedBrackets(composition, m5, amount1);
			}
		} else {
			if(QString(text.c_str()).contains('\'')) {
				throw std::exception("contains \'");
			}
			ParseFormulaWithoutNestedBrackets(composition, text, amount1);
		}
	}
}

void ParseFormulaWithoutNestedBrackets(Composition& composition,
								const std::string& text, const double amount1)
{
	const static std::regex brackets("([\\(]*[A-Za-z0-9\\.]+[\\)]*)([0-9\\.]*)");
	const static std::regex elements("([A-Z]{1}[a-z]?)([0-9\\.]*)");
	auto pos2 = std::sregex_iterator(text.begin(), text.end(), brackets);
	auto end2 = std::sregex_iterator();
	for(; pos2 != end2; ++pos2) { // K3Sm2(UO2)3.4(MoO4)2
		auto&& m1 = pos2->str(1); // K3Sm2		(UO2)		(MoO4)
		auto&& m2 = pos2->str(2); // null		3.4			2
		auto amount2 = m2.empty() ? 1.0 : std::stod(m2);
		auto amount2_multiply_amount1 = amount2 * amount1;
		auto pos3 = std::sregex_iterator(m1.begin(), m1.end(), elements);
		auto end3 = std::sregex_iterator();
		for(; pos3 != end3; ++pos3) { // (MoO4)
			auto&& e1 = pos3->str(1); // Mo		O
			auto&& e2 = pos3->str(2); // null	4
			auto amount3 = e2.empty() ? 1.0 : std::stod(e2);
			composition[QString(e1.c_str())] += amount3 * amount2_multiply_amount1;
		}
	}
}

void tests()
{
	if(contain_nested_brackets("F(Td(te)") &&
			!contain_nested_brackets("F(Td)t(e)") &&
			!contain_nested_brackets("F(Tdte)") &&
			contain_nested_brackets("F(Td(fst)e)") &&
			contain_nested_brackets("(Co(NH3)5Cl)Cl2") &&
			contain_nested_brackets("(Co(NH3)6)Br3") &&
			contain_nested_brackets("K2Sr(B4O5(OH)4)2"))
	{
	} else {
		throw std::exception("ERROR tests_contain_nested_brackets failed");
	}
	struct Test{
		QString formula;
		QString suffix;
		Composition composition;
	};
	QList<Test> formulas;
	formulas << Test{"*2K2TaF7*Ta2O5(+a)", "+a", {{"K", 4}, {"Ta", 4}, {"O", 5}, {"F", 14}}};
	formulas << Test{"K2Zn3(P2O7)2*3H2O(s)", "s", {{"K",2},{"Zn",3},{"P",4},{"O",17},{"H",6}}};
	formulas << Test{"Ca2Fe0.75Mg0.25B2Si2*O10(-al)", "-al", {{"Ca",2},{"Fe",0.75},{"Mg",0.25},{"B",2},{"Si",2},{"O",10}}};

	formulas << Test{"Co(NH3)5*Cl*Cl2", "", {{"Co",1}, {"N",5}, {"H",15}, {"Cl",3}}};
	formulas << Test{"Co(NH3)5Cl*Cl2", "", {{"Co",1}, {"N",5}, {"H",15}, {"Cl",3}}};
	formulas << Test{"Co*5(NH3)*Cl3(ia)", "ia", {{"Co",1}, {"N",5}, {"H",15}, {"Cl",3}}};

	formulas << Test{"(Co(NH3)6)Br3", "", {{"Co",1},{"N",6},{"H",18},{"Br",3}}};
	formulas << Test{"(Co(NH3)5Cl)Cl2", "", {{"Co",1},{"N",5},{"H",15},{"Cl",3}}};
	formulas << Test{"K2Sr(B4O5(OH)4)2Mo4*10H2O", "", {{"K",2},{"Sr",1},{"B",8},{"O",28},{"H",28},{"Mo",4}}};

	QString suffix_test;
	Composition cmp_test;
	for(auto&& i : formulas) {
		suffix_test.clear();
		cmp_test.clear();
		ParseFormula(i.formula, suffix_test, cmp_test);
		if(i.suffix != suffix_test) {
			QString str("ERROR fail in suffix: ");
			str += i.formula + " " + i.suffix + " " + suffix_test;
			throw std::exception(str.toStdString().c_str());
		} else if(i.composition != cmp_test) {
			QString str("ERROR fail in composition: ");
			str += i.formula;
			throw std::exception(str.toStdString().c_str());
		} else {
#ifndef NDEBUG
			std::cout << i.formula.toStdString() << " parse formula test passed\n";
#endif
		}
	}
}

DataReferences::DataReferences(const QString& filename)
{
	QFile file(filename);
	if(file.open(QIODevice::ReadOnly)) {
		QTextStream stream(&file);
		int i{1};
		while(!stream.atEnd()) {
			auto str = stream.readLine().split("\t");
			data.push_back(DataReferencesItem{i++, str.at(0).trimmed(), str.at(1).trimmed()});
		}
		if(stream.status() != QTextStream::Ok) {
			QString err("ERROR read file: ");
			err += filename;
			throw std::exception(err.toStdString().c_str());
		}
	}
	file.close();
}

void DataReferences::Print(const QString& filename) const
{
	if(!filename.isEmpty()) {
		QFile file(filename);
		if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			QTextStream stream(&file);
			for(const auto& [number_, short_name_, long_name_] : data) {
				stream << number_ << "\t" << short_name_ << "\t" << long_name_ << "\n";
			}
		}
		file.close();
	}
}

QVector<QString> DataReferences::FindLongNames(const QString& short_name) const
{
	QVector<QString> long_names_list;
	for(const auto& [_, short_name_, long_name_] : data) {
		if(short_name == short_name_) {
			long_names_list.push_back(long_name_);
		}
	}
	return long_names_list;
}

Elements::Elements(const QString& filename)
{
	QFile file(filename);
	if(file.open(QIODevice::ReadOnly)) {
		QTextStream stream(&file);
		while(!stream.atEnd()) {
			auto str = stream.readLine().split("\t");
			auto size = str.size();
			// the loops below starts with 1 to get rid of first column that
			// duplicates Symbol column
			if(str.at(0) == "Property") {
				properties.reserve(size-1);
				for(int i = 1; i != size; ++i) {
					properties.push_back(str.at(i).trimmed());
				}
				continue;
			}
			if(str.at(0) == "Units") {
				property_units.reserve(size-1);
				for(int i = 1; i != size; ++i) {
					property_units.push_back(str.at(i).trimmed());
				}
				continue;
			}
			if(str.at(0) == "Diagram") {
				continue;
			}
			values.push_back(QVector<QString>{});
			auto&& last = values.last();
			last.reserve(size-1);
			for(int i = 1; i != size; ++i) {
				last.push_back(str.at(i).trimmed());
			}
		}
		if(stream.status() != QTextStream::Ok) {
			QString err("ERROR read file: ");
			err += filename;
			throw std::exception(err.toStdString().c_str());
		}
	}
	file.close();

	// make atomic_weight
	if(properties.at(1) != "Symbol") {
		throw std::exception("Symbol is not in col 1");
	}
	if(properties.at(3) != "Atomic Weight") {
		throw std::exception("Atomic Weight is not in col 3");
	}
	bool ok{false};
	for(auto&& i : values) {
		atomic_weight[i.at(1)] = i.at(3).toDouble(&ok);
		if(!ok) throw std::exception(i.at(2).toStdString().c_str());
	}
}

void Elements::Print(const QString& filename) const
{
	if(!filename.isEmpty()) {
		QFile file(filename);
		if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
			QTextStream stream(&file);
			for(const auto& i : properties) {
				stream << i << "\t";
			}
			stream << "\n";
			for(const auto& i : property_units) {
				stream << i << "\t";
			}
			stream << "\n";
			for(const auto& i : values) {
				for(const auto& j : i) {
					stream << j << "\t";
				}
				stream << "\n";
			}
		}
		file.close();
	}
}

void Elements::PrintProperties() const
{
	for(const auto& i : properties) {
		std::cout << i.toStdString() << std::endl;
		//qDebug() << i;
	}
}

void Elements::PrintPropertyUnits() const
{
	for(const auto& i : property_units) {
		std::cout << i.toStdString() << std::endl;
		//qDebug() << i;
	}
}

std::set<QString> Elements::GetElements() const
{
	std::set<QString> set;
	for(const auto& i : values) {
		set.insert(i.at(1));
	}
	return set;
}

double Elements::GetWeight(const Composition& composition) const
{
	double weight{0.0};
	for(const auto& [name, amount] : composition) {
		weight += atomic_weight.at(name) * amount;
	}
	return weight;
}

Colors::Colors(const QString& filename)
{
	QFile file(filename);
	if(file.open(QIODevice::ReadOnly)) {
		QTextStream stream(&file);
		int id{1};
		while(!stream.atEnd()) {
			auto str = stream.readLine().split(".");
			auto number = str.at(0).toInt();
			auto name = str.at(1).trimmed();
			data.push_back(Color{id++, number, name});
		}
		if(stream.status() != QTextStream::Ok) {
			QString err("ERROR read file: ");
			err += filename;
			throw std::exception(err.toStdString().c_str());
		}
	}
}

const QString& Colors::GetColorName(const int number) const
{
	auto f = std::find_if(data.cbegin(), data.cend(), [number](const Color& c){
		return number == c.number;
	});
	return f->name;
}

Units::Units(const QString& filename)
{
	QFile file(filename);
	if(file.open(QIODevice::ReadOnly)) {
		QTextStream stream(&file);
		int id{1};
		while(!stream.atEnd()) {
			auto str = stream.readLine().split("\t");
			auto name = str.at(0).trimmed();
			auto unit_name = str.at(1).trimmed();
			data.push_back(Unit{id++, name, unit_name});
		}
		if(stream.status() != QTextStream::Ok) {
			QString err("ERROR read file: ");
			err += filename;
			throw std::exception(err.toStdString().c_str());
		}
	}
}

// ****************************************************************************
// *****************************     To SQL       *****************************
// ****************************************************************************

void SaveToSql(const Database& db, const DataReferences& dbref,
			   const Elements& dbel, const Colors& dbcolor, const Units& dbunit,
			   const QString& filename)
{
	QString new_filename(FilenameIncrement(filename));
	while(QFile::exists(new_filename)) {
		new_filename = FilenameIncrement(new_filename);
	}

	QSqlDatabase sql = QSqlDatabase::addDatabase("QSQLITE");
	sql.setDatabaseName(new_filename);
	if(!sql.open()) {
		QString str("Cannot open Database file: ");
		str += new_filename + "\n" + sql.lastError().text();
		throw std::exception(str.toStdString().c_str());
	}
	MakeTableSpecies(sql, db, dbel);
	MakeTableTempRange(sql, db);
	MakeTableColor(sql, dbcolor);
	MakeTableCompositionsOfSpecies(sql, db, dbel);
	MakeTableElements(sql, dbel);
	MakeTableIonicRadiiInCrystalsOxidationState(sql, dbel);
	MakeTableIsotopes(sql, dbel);
	MakeTableState(sql);
	MakeTableRefs(sql, dbref);
	MakeTableTempRangeToReferences(sql, db, dbref);
	sql.close();
}

QString FilenameIncrement(const QString& filename, int precision)
{
	auto split1 = filename.split("/");
	QStringList path;
	std::copy_n(split1.begin(), split1.size()-1, std::back_inserter(path));
	QString fname = split1.last();

	auto split2 = fname.split(".");
	QStringList name;
	QString extension;
	if(split2.size() < 2) {
		name = split2;
		extension = "db";
	} else {
		std::copy_n(split2.begin(), split2.size()-1, std::back_inserter(name));
		extension = split2.last();
	}

	auto split3 = name.join(".").split("_");
	QStringList rname;
	int number;
	bool ok{false};
	if(split3.size() < 2) {
		number = 1;
		rname = split3;
	} else {
		number = split3.last().toInt(&ok);
		if(ok) {
			++number;
			std::copy_n(split3.begin(), split3.size()-1, std::back_inserter(rname));
		} else {
			number = 1;
			rname = split3;
		}
	}

	QString new_filename(path.join("/"));
	new_filename += "/";
	new_filename += rname.join("_");
	new_filename += "_" + QString::number(number).rightJustified(precision, '0');
	new_filename += "." + extension;
	return new_filename;
}

void MakeTableSpecies(const QSqlDatabase& sql, const Database& db,
					  const Elements& dbel)
{
	static QString str0("DROP TABLE IF EXISTS Species;");
	static QString str1("CREATE TABLE IF NOT EXISTS Species ( "
						"species_id         INTEGER PRIMARY KEY NOT NULL, "
						"CAN                TEXT NOT NULL, "
						"Formula            TEXT NOT NULL, "
						"FormulaS           TEXT NOT NULL, "
						"NameCh             TEXT NOT NULL, "
						"NameCo             TEXT NOT NULL, "
						"Suffix             TEXT NOT NULL, "
						"TempRanges         INTEGER NOT NULL, "
						"NumberOfElements   INTEGER NOT NULL, "
						"MP                 REAL NOT NULL, "
						"BP                 REAL NOT NULL, "
						"Weight             REAL NOT NULL, "
						"T_min              REAL NOT NULL, "
						"T_max              REAL NOT NULL "
						");");
	static QString str2("INSERT INTO Species (species_id, CAN, Formula, "
						"FormulaS, NameCh, NameCo, Suffix, TempRanges, "
						"NumberOfElements, MP, BP, Weight, T_min, T_max) "
						"VALUES (%1, '%2', '%3', '%4', '%5', '%6', '%7', "
						"%8, %9, %10, %11, %12, %13, %14);");
	QSqlQuery query(MakeTable(sql, str0, str1));

	auto minmax = [](const QVector<HSCDBTempRange>& tr) {
		int imin{0}, imax{0}, icur{0};
		bool ok{false};
		double min = tr.at(0).HSCT1.toDouble(&ok);
		if(!ok) throw std::exception(tr.at(0).HSCT1.toStdString().c_str());
		double max = tr.at(0).HSCT2.toDouble(&ok);
		if(!ok) throw std::exception(tr.at(0).HSCT2.toStdString().c_str());
		for(const auto& i : tr) {
			auto xmin = i.HSCT1.toDouble(&ok);
			if(!ok) throw std::exception(i.HSCT1.toStdString().c_str());
			auto xmax = i.HSCT2.toDouble(&ok);
			if(!ok) throw std::exception(i.HSCT2.toStdString().c_str());
			if(xmin < min) {
				min = xmin;
				imin = icur;
			}
			if(xmax > max) {
				max = xmax;
				imax = icur;
			}
			icur++;
		}
		return std::make_pair(tr.at(imin).HSCT1, tr.at(imax).HSCT2);
	};

	for(const auto& species : db) {
		auto [min, max] = minmax(species.TempRange);
		auto formula = species.formula;
		formula.replace("'", "''");
		auto formulas = species.formulaS;
		formulas.replace("'", "''");
		auto namech = species.NameCh;
		namech.replace("'", "''");
		auto nameco = species.NameCo;
		nameco.replace("'", "''");
		auto suffix = species.suffix;
		suffix.replace("'", "''");
		auto&& str = str2.arg(QString::number(species.id),
				species.CAN, formula, formulas, namech, nameco, suffix).
				arg(QString::number(species.TempRange.size()),
					QString::number(species.composition.size()),
					QString::number(std::abs(species.HSCMP.toDouble()), 'g', 10),
					QString::number(std::abs(species.HSCBP.toDouble()), 'g', 10),
					QString::number(dbel.GetWeight(species.composition), 'g', 10),
					min, max);
		if(!query.exec(str)) {
			str += "\n" + query.lastError().text();
			throw std::exception(str.toStdString().c_str());
		}
	}
}

void MakeTableTempRange(const QSqlDatabase& sql, const Database& db)
{
	static QString str0("DROP TABLE IF EXISTS TempRange;");
	static QString str1("CREATE TABLE IF NOT EXISTS TempRange ( "
						"tr_id              INTEGER PRIMARY KEY NOT NULL, "
						"species_id         INTEGER NOT NULL, "
						"TempIndex          INTEGER NOT NULL, "
						"T1                 REAL NOT NULL, "
						"T2                 REAL NOT NULL, "
						"H                  REAL NOT NULL, "
						"S                  REAL NOT NULL, "
						"A                  REAL NOT NULL, "
						"B                  REAL NOT NULL, "
						"C                  REAL NOT NULL, "
						"D                  REAL NOT NULL, "
						"E                  REAL NOT NULL, "
						"F                  REAL NOT NULL, "
						"Density            REAL NOT NULL, "
						"Color              INTEGER NOT NULL, "
						"Solubility         REAL NOT NULL, "
						"Phase              TEXT NOT NULL, "
						"ReliabilityClass   INTEGER NOT NULL "
						");");
	static QString str2("INSERT INTO TempRange (tr_id, species_id, TempIndex, "
						"T1, T2, H, S, A, B, C, D, E, F, Density, Color, "
						"Solubility, Phase, ReliabilityClass) "
						"VALUES (%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, "
						"%12, %13, %14, %15, %16, '%17', %18);");
	QSqlQuery query(MakeTable(sql, str0, str1));

	int tr_id{1};
	for(const auto& species : db) {
		for(const auto& temp_range : species.TempRange) {
			auto&& str = str2.arg(QString::number(tr_id++),
								  QString::number(species.id),
								  temp_range.HSCTempIndex,
								  temp_range.HSCT1,
								  temp_range.HSCT2,
								  temp_range.HSCH,
								  temp_range.HSCS,
								  temp_range.HSCA,
								  temp_range.HSCB).
					arg(temp_range.HSCC,
						temp_range.HSCD,
						temp_range.HSCE,
						temp_range.HSCF,
						temp_range.HSCDe,
						temp_range.HSCCo,
						temp_range.HSCSolu,
						temp_range.HSCPhase,
						temp_range.HSCCl);
			if(!query.exec(str)) {
				str += "\n" + query.lastError().text();
				throw std::exception(str.toStdString().c_str());
			}
		}
	}
}

void MakeTableColor(const QSqlDatabase& sql, const Colors& dbcolor)
{
	static QString str0("DROP TABLE IF EXISTS Color;");
	static QString str1("CREATE TABLE IF NOT EXISTS Color ( "
						"color_id           INTEGER PRIMARY KEY NOT NULL, "
						"Number             INTEGER NOT NULL, "
						"Name               TEXT NOT NULL "
						");");
	static QString str2("INSERT INTO Color (color_id, Number, Name) "
						"VALUES (%1, %2, '%3');");
	QSqlQuery query(MakeTable(sql, str0, str1));
	for(const auto& i : dbcolor) {
		auto&& str = str2.arg(QString::number(i.id),
							  QString::number(i.number),
							  i.name);
		if(!query.exec(str)) {
			str += "\n" + query.lastError().text();
			throw std::exception(str.toStdString().c_str());
		}
	}
}

void MakeTableCompositionsOfSpecies(const QSqlDatabase& sql, const Database& db,
									const Elements& dbel)
{
	static QString str0("DROP TABLE IF EXISTS CompositionsOfSpecies;");
	static QString str1("CREATE TABLE IF NOT EXISTS CompositionsOfSpecies ( "
						"cmp_id           INTEGER PRIMARY KEY NOT NULL, "
						"species_id       INTEGER NOT NULL, "
						"element_id       INTEGER NOT NULL, "
						"Amount           REAL NOT NULL"
						");");
	static QString str2("INSERT INTO CompositionsOfSpecies (cmp_id, "
						"species_id, element_id, Amount) "
						"VALUES (%1, %2, %3, %4);");
	QSqlQuery query(MakeTable(sql, str0, str1));




}

void MakeTableElements(const QSqlDatabase& sql, const Elements& dbel)
{
	static QString str0("DROP TABLE IF EXISTS Elements;");
	static QString str1("CREATE TABLE IF NOT EXISTS Elements ( "
	"element_id                                 INTEGER PRIMARY KEY NOT NULL, "
	"AtomicNumber                               INTEGER NOT NULL, "
	"Symbol                                     TEXT NOT NULL, "
	"Name                                       TEXT NOT NULL, "
	"AtomicWeight                               REAL NOT NULL, "
	"OxidationStatesMostStable                  TEXT NOT NULL, "
	"OxidationStates                            TEXT NOT NULL, "
	"Density                                    REAL NOT NULL, "
	"ElectronConfiguration                      TEXT NOT NULL, "
	"MeltingPoint                               REAL NOT NULL, "
	"MeltingPointPressure                       REAL NOT NULL, "
	"BoilingPoint                               REAL NOT NULL, "
	"Electronegativity                          REAL NOT NULL, "
	"HeatOfVaporization                         REAL NOT NULL, "
	"HeatOfFusion                               REAL NOT NULL, "
	"ElectricalConductivity                     REAL NOT NULL, "
	"ThermalConductivity                        REAL NOT NULL, "
	"SpecificHeatCapacity                       REAL NOT NULL, "
	"FirstIonizationPotential                   REAL NOT NULL, "
	"AtomicVolume                               REAL NOT NULL, "
	"AtomicRadius                               REAL NOT NULL, "
	"CovalentRadius                             REAL NOT NULL, "
	"CrystalStructure                           TEXT NOT NULL, "
	"AcidBaseProperties                         TEXT NOT NULL, "
	"YearWhenDiscovered                         INTEGER NOT NULL, "
	"Color                                      TEXT NOT NULL, "
	"ColorRGBNumber                             INTEGER NOT NULL, "
	"SolubilityInColdWater                      TEXT NOT NULL, "
	"SolubilityInHotWater                       TEXT NOT NULL, "
	"MagneticSusceptibility                     TEXT NOT NULL, "
	"AtomicElectronAffinity                     TEXT NOT NULL, "
	"LatticeParameterA                          TEXT NOT NULL, "
	"LatticeParameterB                          TEXT NOT NULL, "
	"LatticeParameterC                          TEXT NOT NULL, "
	"ContentInTheEarthsCrust                    REAL NOT NULL, "
	"ContentInTheSea                            REAL NOT NULL, "
	"ContentInTheAir                            REAL NOT NULL, "
	"Polarizability                             REAL NOT NULL, "
	"EnthalpyOfFormationAt29815KGas             TEXT NOT NULL, "
	"EnthalpyOfFormationAt29815KSolid           TEXT NOT NULL, "
	"GibbsEnergyOfFormation29815KGas            TEXT NOT NULL, "
	"GibbsEnergyOfFormation29815KSolid          TEXT NOT NULL, "
	"StandardEntropy29815KGas                   TEXT NOT NULL, "
	"StandardEntropy29815KSolid                 TEXT NOT NULL, "
	"HeatCapacity29815KGas                      TEXT NOT NULL, "
	"HeatCapacity29815KSolid                    TEXT NOT NULL, "
	"LinearExpansion29815K                      REAL NOT NULL, "
	"HalfLifeOfTheMostStabileNuclide            TEXT NOT NULL, "
	"RecyclabilityUNEP                          REAL NOT NULL "
	");");
	static QString str2("INSERT INTO CompositionsOfSpecies (element_id, "
						"AtomicNumber, Symbol, Name, AtomicWeight, "
						"OxidationStatesMostStable, OxidationStates, Density, "
						"ElectronConfiguration, MeltingPoint, "
						"MeltingPointPressure, BoilingPoint, "
						"Electronegativity, HeatOfVaporization, HeatOfFusion, "
						"ElectricalConductivity, ThermalConductivity, "
						"SpecificHeatCapacity, FirstIonizationPotential, "
						"AtomicVolume, AtomicRadius, CovalentRadius, "
						"CrystalStructure, AcidBaseProperties, "
						"YearWhenDiscovered, Color, ColorRGBNumber, "
						"SolubilityInColdWater, SolubilityInHotWater, "
						"MagneticSusceptibility, AtomicElectronAffinity, "
						"LatticeParameterA, LatticeParameterB, "
						"LatticeParameterC, ContentInTheEarthsCrust, "
						"ContentInTheSea, ContentInTheAir, Polarizability, "
						"EnthalpyOfFormationAt29815KGas, "
						"EnthalpyOfFormationAt29815KSolid, "
						"GibbsEnergyOfFormation29815KGas, "
						"GibbsEnergyOfFormation29815KSolid, "
						"StandardEntropy29815KGas, StandardEntropy29815KSolid, "
						"HeatCapacity29815KGas, HeatCapacity29815KSolid, "
						"LinearExpansion29815K, "
						"HalfLifeOfTheMostStabileNuclide, "
						"RecyclabilityUNEP) "
						"VALUES (%1, %2, '%3', '%4', %5, '%6', '%7', %8, '%9', "
						"%10, %11, %12, %13, %14, %15, %16, %17, %18, %19, "
						"%20, %21, %22, '%23', '%24', %25, '%26', %27, '%28', "
						"'%29', '%30', '%31', '%32', '%33', '%34', %35, %36, "
						"%37, %38, '%39', '%40', '%41', '%42', '%43', '%44', "
						"'%45', '%46', %47, '%48', %49);");


}

void MakeTableIonicRadiiInCrystalsOxidationState(const QSqlDatabase& sql,
												 const Elements& dbel)
{

}

void MakeTableIsotopes(const QSqlDatabase& sql, const Elements& dbel)
{

}

void MakeTableState(const QSqlDatabase& sql)
{
	static QString str0("DROP TABLE IF EXISTS State;");
	static QString str1("CREATE TABLE IF NOT EXISTS State ("
						"state_id INTEGER PRIMARY KEY NOT NULL, "
						"Symbol TEXT NOT NULL, "
						"Name TEXT NOT NULL);");
	static QString str2("INSERT INTO State (state_id, Symbol, Name) "
						"VALUES (%1, '%2', '%3');");

	static QVector<QString> symbols{"g", "l", "s", "a", "?"};
	static QVector<QString> names{"Gas", "Liquid", "Solid", "Aqueous", "Unknown"};

	QSqlQuery query(MakeTable(sql, str0, str1));

	for(int i = 0; i != symbols.size(); ++i) {
		auto&& str = str2.arg(QString::number(i+1), symbols.at(i), names.at(i));
		if(!query.exec(str)) {
			str += "\n" + query.lastError().text();
			throw std::exception(str.toStdString().c_str());
		}
	}
}

void MakeTableRefs(const QSqlDatabase& sql, const DataReferences& dbref)
{
	static QString str0("DROP TABLE IF EXISTS Refs;");
	static QString str1("CREATE TABLE IF NOT EXISTS Refs ( "
						"ref_id INTEGER PRIMARY KEY NOT NULL, "
						"Name TEXT NOT NULL, "
						"Article TEXT NOT NULL);");
	static QString str2("INSERT INTO Refs (ref_id, Name, Article) "
						"VALUES (%1, '%2', '%3');");

	QSqlQuery query(MakeTable(sql, str0, str1));

	for(const auto& i : dbref) {
		auto name = i.short_name;
		name.replace("'", "''");
		auto article = i.long_name;
		article.replace("'", "''");
		auto&& str = str2.arg(QString::number(i.id), name, article);
		if(!query.exec(str)) {
			str += "\n" + query.lastError().text();
			throw std::exception(str.toStdString().c_str());
		}
	}
}

void MakeTableTempRangeToReferences(const QSqlDatabase& sql, const Database& db,
									const DataReferences& dbref)
{

}

QSqlQuery MakeTable(const QSqlDatabase& sql, const QString& str0,
					const QString& str1)
{
	QSqlQuery query(sql);
	if(!query.exec(str0)) {
		QString err("Unable to drop table\n");
		err += str0 + "\n";
		err += query.lastError().text();
		throw std::exception(err.toStdString().c_str());
	}
	if(!query.exec(str1)) {
		QString err("Unable to create table\n");
		err += str1 + "\n";
		err += query.lastError().text();
		throw std::exception(err.toStdString().c_str());
	}
	return query;
}
