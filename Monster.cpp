#include "Monster.h"

Monster::Monster(){
	
}
Monster::Monster(int setLife,int setWeight,D3DXVECTOR3 setPosition,D3DXVECTOR3 setVelocity,D3DXVECTOR3 setGoal){
	alive = true;
	bGround = false;
	life = setLife;
	weight = setWeight;
	vPosition = setPosition; 
	vVelocity = setVelocity;
	vGoal = setGoal;
}
bool Monster::isAlive(){
	return alive;
}
int Monster::hisLife(){
	return life;
}
int Monster::hisWeight(){
	return weight;
}
D3DXVECTOR3 Monster::hisPosition(){
	return vPosition;
}
D3DXVECTOR3 Monster::hisVelocity(){
	return vVelocity;
}
D3DXVECTOR3 Monster::hisGoal(){
	return vGoal;
}
bool Monster::isGround(){
	return bGround;
}