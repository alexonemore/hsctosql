#include "utilities.h"
#include <QString>
#include <QMetaProperty>
#include <unordered_map>
#include <vector>

namespace static_tests {
using vt = typename std::iterator_traits<decltype(std::declval<
			std::unordered_map<int, double>>().cbegin())>::value_type;
static_assert(is_pair_v<vt>, "is_pair");
static_assert(EqualsAnyOf(1, 4, 1.0, 5.7), "");
static_assert(EqualsAnyOf(1, 4, 's', 1.0f), "");
static_assert(EqualsAllOf(1, 1, 1, 1.0, 1.0f), "");
static_assert(!EqualsAllOf(1, 1, 1, 9, 1), "");
static_assert(!EqualsAllOf(1, 1, 1, 1, '1'), "");
}

QString Timer::duration()
{
	auto mt = minutes();
	auto st = seconds();
	auto h = hours();
	auto m = mt - h * 60;
	auto s = st - mt * 60;
	auto ms = milliseconds() - st * 1000;
	QString dur;
	if(h > 0) { dur += QString::number(h) + " h"; }
	if(m > 0) { dur += " " + QString::number(m) + " m"; }
	if(s > 0) { dur += " " + QString::number(s) + " s "; }
	dur += QString::number(ms) + " ms";
	return dur;
}

void PrintAllProperties(const QObject* const obj)
{
#ifndef NDEBUG
	const QMetaObject* metaobject = obj->metaObject();
	int count = metaobject->propertyCount();
	for(int i{0}; i < count; ++i) {
		QMetaProperty metaproperty = metaobject->property(i);
		const char* name = metaproperty.name();
		QVariant value = obj->property(name);
		qDebug() << name << ": " << value.toString();
	}
#else
	Q_UNUSED(obj)
#endif
}



