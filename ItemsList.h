#ifndef _ITEMSLIST_H_
#define _ITEMSLIST_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Items.h"

class ItemsList{
private:
	int nCount;
	Items* pNowNode;

	Items* pStart;
	Items* pEnd;
	
	Items* pListPrev;
	Items* pListNext;
public:
	ItemsList();
	~ItemsList();
	void SetNode(Items* argu);
	void DelNode(Items* node);
	Items* SearchNode();

	inline Items* ReturnNode(){return pNowNode;};
	inline int GetCount(){return nCount;};
	inline Items* GetStart(){return pStart;};
	inline Items* GetEnd(){return pEnd;};

};
#endif