#include <memory>

#include "StyleTable.hpp"

using namespace std;
using namespace Styles;


StyleTable::StyleTable()
{
}


void
StyleTable::addStyle(string name, shared_ptr<Style> style)
{
	styles.emplace(name, style);
}


shared_ptr<Style>
StyleTable::getStyle(string name)
{
	return styles[name];
}
