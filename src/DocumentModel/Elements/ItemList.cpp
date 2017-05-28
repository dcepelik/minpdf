#include "ItemList.hpp"
#include "Paragraph.hpp"
#include "TextNode.hpp"
#include "BoxModel/InlinePostscript.hpp"

using namespace DocumentModel::Elements;


/*
 * Taken from
 * https://stackoverflow.com/questions/19266018/converting-integer-to-roman-numeral
 */
static string to_roman(unsigned int value)
{
    struct romandata_t { unsigned int value; char const* numeral; };
    const struct romandata_t romandata[] =
    {
        {1000, "M"}, {900, "CM"},
        {500, "D"}, {400, "CD"},
        {100, "C"}, { 90, "XC"},
        { 50, "L"}, { 40, "XL"},
        { 10, "X"}, { 9, "IX"},
        { 5, "V"}, { 4, "IV"},
        { 1, "I"},
        { 0, NULL} // end marker
    };

    std::string result;
    for (const romandata_t* current = romandata; current->value > 0; ++current)
    {
        while (value >= current->value)
        {
            result += current->numeral;
            value -= current->value;
        }
    }
    return result;
}


void ItemList::render(vector<shared_ptr<Box>> &boxes)
{
	Paragraph *p;
	HList *hlist;
	double itemIndent = 50;
	double spaceAfterBullet = 10;
	int i = 1;

	for (auto child: children) {
		if ((p = dynamic_cast<Paragraph *>(child.get()))) {
			p->setMaxSize(getDocument()->getContentWidth() - itemIndent);

			string bulletText;
			
			if (style == ItemListStyleNumbered) {
				bulletText = to_string(i) + ".";
			}
			else if (style == ItemListStyleUnordered) {
				bulletText = "-";
			}
			else {
				bulletText = to_roman(i) + ")";
			}

			TextNode *bulletTextNode = new TextNode(shared_ptr<Element>(this), bulletText);
			double bulletNatWidth = bulletTextNode->getNaturalWidth();

			vector<shared_ptr<Box>> pBoxes;
			vector<shared_ptr<Box>> bulletBoxes;

			p->render(pBoxes);
			bulletTextNode->render(bulletBoxes);

			if (pBoxes.size() == 0)
				continue;

			hlist = dynamic_cast<HList *>(pBoxes[0].get());
			assert(hlist != NULL);

			HGlue *preBulletGlue = new HGlue(0, itemIndent - bulletNatWidth - spaceAfterBullet, 0, 0);
			HGlue *postBulletGlue = new HGlue(0, spaceAfterBullet, 0, 0);

			hlist->prependChild(shared_ptr<Box>(postBulletGlue));
			hlist->prependChildren(bulletBoxes);
			hlist->prependChild(shared_ptr<Box>(preBulletGlue));

			for (auto pBox = pBoxes.begin() + 1; pBox != pBoxes.end(); pBox++) {
				HGlue *indentGlue = new HGlue(0, itemIndent, 0, 0);
				if ((hlist = dynamic_cast<HList *>(pBox->get()))) {
					hlist->prependChild(shared_ptr<Box>(indentGlue));
				}
			}

			boxes.insert(boxes.end(), pBoxes.begin(), pBoxes.end());
			i++;
		}
	}
}
