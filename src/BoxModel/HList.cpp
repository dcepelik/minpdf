#include "HList.hpp"

using namespace BoxModel;


BoxType
HList::getType()
{
	return BoxType::HListBox;
}


void
HList::writePSOutput(ostream &out)
{
	(void)out;
}


void
HList::dump()
{
	cout << "[";
	
	for (auto item: items) {
		item->dump();
	}

	cout << "]";
}
