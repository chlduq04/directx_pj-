#ifndef _ITEMSLIST_H_
#define _ITEMSLIST_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Items.h"

class ItemsList{
private:
	int count;
	Items* nowNode;
	Items* istart;
	Items* iend;
	Items* listPrev;
	Items* listNext;
public:
	ItemsList();
	~ItemsList();
	void setNode(Items* argu);
	void delNode(int item_number);

	Items* searchNode();
	Items* returnNode();
	int getCount();
	Items* getStart();
	Items* getEnd();
};
#endif