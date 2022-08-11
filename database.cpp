#include "database.h"
#include <QFile>
#include <QDebug>
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
				return sr.text().toString();
			}
			else if(type == QXmlStreamReader::TokenType::EndElement) {
				return QString{};
			} else {
				qDebug() << sr.tokenString() << sr.name() << sr.text();
				throw std::exception("Error get_next_character");
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

			if(!in_temp_range && name == QStringLiteral("HSCDBSpecies")) { db.push_back(HSCDBSpecies{}); }
			else if(!in_temp_range && name == QStringLiteral("suHSCMP")) { db.last().suHSCMP = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("suHSCBP")) { db.last().suHSCBP = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("OriginDatabase")) { db.last().OriginDatabase = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("SaveDate")) { db.last().SaveDate = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("CAN")) { db.last().CAN = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("formula")) { db.last().formula = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("formulaS")) { db.last().formulaS = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("NameCh")) { db.last().NameCh = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("NameCo")) { db.last().NameCo = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("HSCMP")) { db.last().HSCMP = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("HSCBP")) { db.last().HSCBP = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("Unit")) { db.last().Unit = get_next_character(); }
			else if(!in_temp_range && name == QStringLiteral("TemperatureUnit")) { db.last().TemperatureUnit = get_next_character(); }

			else if(!in_temp_range && name == QStringLiteral("TempRange")) { in_temp_range = true; }

			else if(in_temp_range && name == QStringLiteral("HSCDBTempRange")) { db.last().TempRange.push_back(HSCDBTempRange{}); }

			else if(in_temp_range && name == QStringLiteral("Unit")) { db.last().TempRange.last().Unit = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("TemperatureUnit")) { db.last().TempRange.last().TemperatureUnit = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCTempIndex")) { db.last().TempRange.last().HSCTempIndex = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("Reference")) { db.last().TempRange.last().Reference = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCT1")) { db.last().TempRange.last().HSCT1 = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCT2")) { db.last().TempRange.last().HSCT2 = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCH")) { db.last().TempRange.last().HSCH = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCS")) { db.last().TempRange.last().HSCS = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCA")) { db.last().TempRange.last().HSCA = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCB")) { db.last().TempRange.last().HSCB = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCC")) { db.last().TempRange.last().HSCC = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCD")) { db.last().TempRange.last().HSCD = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCE")) { db.last().TempRange.last().HSCE = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCF")) { db.last().TempRange.last().HSCF = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCDe")) { db.last().TempRange.last().HSCDe = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCCo")) { db.last().TempRange.last().HSCCo = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCSolu")) { db.last().TempRange.last().HSCSolu = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCPhase")) { db.last().TempRange.last().HSCPhase = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("HSCCl")) { db.last().TempRange.last().HSCCl = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCT1")) { db.last().TempRange.last().suHSCT1 = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCT2")) { db.last().TempRange.last().suHSCT2 = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCH")) { db.last().TempRange.last().suHSCH = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCS")) { db.last().TempRange.last().suHSCS = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCA")) { db.last().TempRange.last().suHSCA = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCB")) { db.last().TempRange.last().suHSCB = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCC")) { db.last().TempRange.last().suHSCC = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCD")) { db.last().TempRange.last().suHSCD = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCE")) { db.last().TempRange.last().suHSCE = get_next_character(); }
			else if(in_temp_range && name == QStringLiteral("suHSCF")) { db.last().TempRange.last().suHSCF = get_next_character(); }

		} while(!sr.atEnd());
		if(sr.hasError()) {
			qDebug() << "Error:" << sr.errorString();
			throw std::exception("Error: QXmlStreamReader has error");
		}
		file.close();
	}
	int i{1};
	for(auto&& d : db) {
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
			for(auto&& i : db) {
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
			for(auto&& i : db) {
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
	for(const auto& i : db) {
		for(const auto& j : i.composition) {
			set.insert(j.first);
		}
	}
	return set;
}

void Database::ParseFormulaToComposition()
{
	for(auto&& i : db) {
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
			if(QString(text.c_str()).contains('\'')) throw std::exception("contains \'");
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
		qDebug() << "tests_contain_nested_brackets failed";
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
			qDebug() << i.formula << "fail in suffix" << i.suffix << suffix_test;
		} else if(i.composition != cmp_test) {
			qDebug() << i.formula << "fail in composition";
		} else {
#ifndef NDEBUG
			qDebug() << i.formula << "test passed";
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
			db.push_back(DataReferencesItem{i++, str.at(0), str.at(1)});
		}
		if(stream.status() != QTextStream::Ok) {
			QString err("Read ERROR: ");
			err.append(filename);
			qDebug() << err;
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
			for(const auto& [number_, short_name_, long_name_] : db) {
				stream << number_ << "\t" << short_name_ << "\t" << long_name_ << "\n";
			}
		}
		file.close();
	}
}

QVector<QString> DataReferences::FindLongNames(const QString& short_name) const
{
	QVector<QString> long_names_list;
	for(const auto& [_, short_name_, long_name_] : db) {
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
			if(str.at(0) == "Property") {
				properties.reserve(size-1);
				for(int i = 1; i != size; ++i) {
					properties.push_back(str.at(i));
				}
				continue;
			}
			if(str.at(0) == "Units") {
				property_units.reserve(size-1);
				for(int i = 1; i != size; ++i) {
					property_units.push_back(str.at(i));
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
				last.push_back(str.at(i));
			}
		}
		if(stream.status() != QTextStream::Ok) {
			QString err("Read ERROR: ");
			err.append(filename);
			qDebug() << err;
			throw std::exception(err.toStdString().c_str());
		}
	}
	file.close();
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

std::set<QString> Elements::GetElements() const
{
	// Symbol = 1
	if(properties.at(1) != "Symbol") throw std::exception("Symbol is not in col 1");
	std::set<QString> set;
	for(const auto& i : values) {
		set.insert(i.at(1));
	}
	return set;
}
