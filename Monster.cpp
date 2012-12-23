#include "Monster.h"

Monster::~Monster(){}
Monster::Monster(D3DXVECTOR3 position,D3DXVECTOR3 velocity,D3DXVECTOR3 goal){
	pase = 0;
	maxLife = MON_HEALTH;
	mLife = MON_HEALTH;
	mWeight = MON_WEIGHT;
	mAttack = -5;
	mDefence = 10;
	originType = 0;
	mType = 0;
	sType = 0;
	mMotion = 0;
	mAlive = true;
	vPosition = position; 
	vVelocity = velocity;
	vGoal = goal;
	bGround = false;
	bMove = false;
	bJump = false;
	bGoal = false;
	doAction = false;
	defendTime = 8.0f;
}



void Monster::monDefence(int def){
	mDefence = def;
}
void Monster::monAttack(){
	mAttack = 20;
}
void Monster::monMissile(){}
void Monster::monJump(){}
void Monster::monHealing(){
	if(mLife<maxLife){
		mLife += 50;
	}
	else{
		mLife = maxLife;
	}
}
