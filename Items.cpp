#include "Items.h"

Items::Items(){
	pPrev = NULL;
	pNext = NULL;
	nItemNum = NULL;
	fTime = 0;
	nHp = 0;
	nMp = 0;
	nDefence = 0;
	nSpeed = 0;
	vPosition = D3DXVECTOR3(0,0,0);
}

Items::Items(int type,int level,D3DXVECTOR3 position,int static_item_number,float time){
	nItemNum = static_item_number;
	pPrev = NULL;
	pNext = NULL;
	fTime = time;
	nHp = 0;
	nMp = 0;
	nDefence = 0;
	nSpeed = 0;
	vPosition = position;

	switch(type){
	case 0:
		nHp = level*50;
		break;
	case 1:
		nMp = level*25;
		break;
	case 2:
		nDefence = level*20;
		break;
	default:
		break;
	}
}
