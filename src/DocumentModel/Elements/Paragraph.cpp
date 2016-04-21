#include <cassert>
#include <cmath>
#include <stack>

#include "Paragraph.hpp"

using namespace BoxModel;
using namespace DocumentModel;
using namespace DocumentModel::Elements;


Paragraph::Paragraph(shared_ptr<Element> parent, int width)
	: HWrappingContainer(parent, "p", width)
{
}
