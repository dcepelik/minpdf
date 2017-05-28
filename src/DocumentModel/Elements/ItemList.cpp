#include "ItemList.hpp"
#include "Paragraph.hpp"
#include "TextNode.hpp"
#include "BoxModel/InlinePostscript.hpp"

using namespace DocumentModel::Elements;


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

			TextNode *bulletText = new TextNode(shared_ptr<Element>(this), to_string(i) + ")");
			double bulletNatWidth = bulletText->getNaturalWidth();

			vector<shared_ptr<Box>> pBoxes;
			vector<shared_ptr<Box>> bulletBoxes;

			p->render(pBoxes);
			bulletText->render(bulletBoxes);

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
