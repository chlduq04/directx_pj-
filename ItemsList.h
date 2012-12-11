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
	void delNode(Items* node);
	Items* searchNode();

	inline Items* returnNode(){return nowNode;};
	inline int getCount(){return count;};
	inline Items* getStart(){return istart;};
	inline Items* getEnd(){return iend;};

};
#endif