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
int Items::getNumber(){
	return itNum;
}
int Items::getHp(){
	return hp;
}
int Items::getMp(){
	return mp;
}
int Items::getDef(){
	return defence;
}
int Items::getSpd(){
	return speed;
}
void Items::setPositionX(float argu){
	ptPosition.x = argu;
}
void Items::setPositionY(float argu){
	ptPosition.y = argu;
}
void Items::setPositionZ(float argu){
	ptPosition.z = argu;
}
void Items::setVelocityX(float argu){
	ptVelocity.x = argu;
}
void Items::setVelocityY(float argu){
	ptVelocity.y = argu;
}
void Items::setVelocityZ(float argu){
	ptVelocity.z = argu;
}
void Items::setGoalX(float argu){
	ptGoal.x = argu;
}
void Items::setGoalY(float argu){
	ptGoal.y = argu;
}
void Items::setGoalZ(float argu){
	ptGoal.z = argu;
}

void Items::setPosition(D3DXVECTOR3 argu){
	ptPosition = argu;
}
void Items::setVelocity(D3DXVECTOR3 argu){
	ptVelocity = argu;
}
void Items::setGoal(D3DXVECTOR3 argu){
	ptGoal = argu;
}


D3DXVECTOR3 Items::getPosition(){
	return ptPosition;
}
D3DXVECTOR3 Items::getVelocity(){
	return ptVelocity;
}
D3DXVECTOR3 Items::getGoal(){
	return ptGoal;
}

void Items::setPrev(Items* argu){
	iprev = argu;
}
void Items::setNext(Items* argu){
	inext = argu;
}
Items* Items::getPrev(){
	return iprev;
}
Items* Items::getNext(){
	return inext;
}
float Items::getTime(){
	return mTime;
}
