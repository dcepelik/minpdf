#include "BoxModel/HGlue.hpp"
#include "BoxModel/VGlue.hpp"
#include "BoxModel/HList.hpp"
#include "HWrappingContainer.hpp"

using namespace DocumentModel::Elements;


HWrappingContainer::HWrappingContainer(shared_ptr<Element> parent, string name,
	int width) : WrappingContainer(parent, name, width)
{
};


int
HWrappingContainer::getBoxSize(shared_ptr<Box> box)
{
	return box->getWidth();
}


shared_ptr<Glue>
HWrappingContainer::createNewInfGlue()
{
	return shared_ptr<Glue>(new HGlue(1, 0, 0, 0));
}


shared_ptr<List>
HWrappingContainer::createNewList(vector<shared_ptr<Box>>::iterator begin,
	vector<shared_ptr<Box>>::iterator end)
{
	HList *list = new HList(maxSize);

	for (auto it = begin; it != end; it++)
		list->addChild(*it);

	return shared_ptr<List>(list);
}


shared_ptr<Glue>
HWrappingContainer::createNewInterlineGlue()
{
	return shared_ptr<Glue>(new VGlue(0, 5, 0, 0));
}
