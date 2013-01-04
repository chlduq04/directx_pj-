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

VOID Monster::ResetMonster(){
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
}


void Monster::MonDefence(int def){
	mDefence = def;
}
void Monster::MonAttack(){
	mAttack = 20;
}
void Monster::MonMissile(){}
void Monster::MonJump(){}
void Monster::MonHealing(INT arge){
	if(mLife<maxLife){
		mLife += arge;
	}
	else{
		mLife = maxLife;
	}
}
