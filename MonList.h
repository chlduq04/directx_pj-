#ifndef _MONLIST_H_
#define _MONLIST_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Monster.h"

class MonList{

private:
	int count;
	Monster* nowNode;
	Monster* istart;
	Monster* iend;
	Monster* listPrev;
	Monster* listNext;
public:
	MonList();
	~MonList();
	void setNode(Monster* argu);
	void delNode(int item_number);
	Monster* searchNode();
	Monster* returnNode();
	int getCount();
	Monster* getStart();
	Monster* getEnd();
};
#endif