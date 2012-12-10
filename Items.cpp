#include "Items.h"
Items::Items(){
	iprev = NULL;
	inext = NULL;
	itNum = NULL;
	iprev = NULL;
	inext = NULL;
	mTime = 0;
	hp = 0;
	mp = 0;
	defence = 0;
	speed = 0;
	ptPosition = D3DXVECTOR3(0,0,0);

}

Items::Items(char* type,int level,D3DXVECTOR3 position,int static_item_number,float time){
	itNum = static_item_number;
	iprev = NULL;
	inext = NULL;
	mTime = time;
	hp = 0;
	mp = 0;
	defence = 0;
	speed = 0;
	ptPosition = position;

	if(!strcmp(type,"hp")){
		hp = level*50;
	}
	if(!strcmp(type,"mp")){
		mp = level*25;
	}
	if(!strcmp(type,"def")){
		defence = level*20;
	}
	if(!strcmp(type,"spd")){
		speed = level*0.5;
	}

}
