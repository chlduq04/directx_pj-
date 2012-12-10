#include "Monster.h"

Monster::~Monster(){}
Monster::Monster(D3DXVECTOR3 position,D3DXVECTOR3 velocity,D3DXVECTOR3 goal){
	maxLife = MON_HEALTH;
	mLife = MON_HEALTH;
	mWeight = MON_WEIGHT;
	mAttack = 0;
	mDefence = 0;
	mType = 0;
	sType = 0;
	mMotion = 0;
	mAlive = true;
	vPosition = position; 
	vVelocity = velocity;
	vGoal = goal;
	bGround = true;
	bMove = false;
	bJump = false;
	bGoal = false;

	defendTime = 8.0f;
}



void Monster::monDefence(int def){mDefence = def;
}
void Monster::monAttack(){mAttack = 20;
}
void Monster::monMissile(){}
void Monster::monJump(){}
void Monster::monHealing(){
	if(mLife<maxLife){
		mLife += 0.1;
	}
}
