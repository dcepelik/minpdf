#include "BoxModel/HGlue.hpp"
#include "BoxModel/VGlue.hpp"
#include "BoxModel/VList.hpp"
#include "VWrappingContainer.hpp"

using namespace DocumentModel::Elements;


VWrappingContainer::VWrappingContainer(shared_ptr<Element> parent, string name,
	int width) : WrappingContainer(parent, name, width) {};


int
VWrappingContainer::getBoxSize(shared_ptr<Box> box)
{
	return box->getHeight();
}


shared_ptr<Glue>
VWrappingContainer::createNewInfGlue()
{
	return shared_ptr<Glue>(new VGlue(1, 0, 0, 0));
}


shared_ptr<List>
VWrappingContainer::createNewList(vector<shared_ptr<Box>>::iterator begin,
	vector<shared_ptr<Box>>::iterator end)
{
	VList *list = new VList(maxSize);

	for (auto it = begin; it != end; it++)
		list->addChild(*it);

	return shared_ptr<List>(list);
}


shared_ptr<Glue>
VWrappingContainer::createNewInterlineGlue()
{
	return shared_ptr<Glue>(new HGlue(0, 0, 0, 0));
}
