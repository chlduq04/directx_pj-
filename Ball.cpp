#include "Ball.h"

Ball::Ball(){
	
}
Ball::Ball(int setLife,int setMana,int setWeight,int setMaxLevel,D3DXVECTOR3 setPosition,D3DXVECTOR3 setVelocity,D3DXVECTOR3 setGoal){
	level = 1;
	maxLevel = setMaxLevel;
	alive = true;
	
	life = setLife;
	maxLife = setLife;
	def = 0;
	mana = setMana;
	maxMana = setMana;
	weight = setWeight;
	maxWeight = setWeight;

	ptPosition = setPosition;
	ptVelocity = setVelocity;
	ptGoal = setGoal;
	ptGround = false;
}
bool Ball::isAlive(){
	return alive;
}
void Ball::setAlive(bool argu){
	alive = argu;
}
int Ball::hisLife(){
	return life;
}
int Ball::hisMana(){
	return mana;
}
int Ball::hisWeight(){
	return weight;
}

void Ball::setPosition(D3DXVECTOR3 xyz){
	ptPosition = xyz;
}

void Ball::setVelocity(D3DXVECTOR3 xyz){
	ptVelocity= xyz;
}

void Ball::setGoal(D3DXVECTOR3 xyz){
	ptGoal = xyz;
}

void Ball::setLife(int argu){
	if(argu>=0){
		if(life+argu>maxLife){
			life = maxLife;
		}
		else{
			life = life + argu;
		}
	}
	else{
		if(life+argu<0){
			life = 0;
			setAlive(false);
		}
		else{
			life = life + argu;
		}
	}
}
void Ball::setMana(int argu){
	if(argu>=0){
		if(mana+argu>maxMana){
			mana = maxMana;
		}
		else{
			mana = mana + argu;
		}
	}
	else{
		if(mana+argu<0){
			mana = 0;
		}
		else{
			mana = mana + argu;
		}
	}
}
void Ball::setWeight(int argu){
	if(argu>=0){
		if(weight+argu>maxWeight){
			weight = maxWeight;
		}
		else{
			weight = weight + argu;
		}
	}
	else{
		if(weight+argu<0){
			weight = 1;
		}
		else{
			weight = weight + argu;
		}
	}
}

void Ball::upLevel(){
	level++;
	if(level>maxLevel){
		level = maxLevel;
	}
	maxLife = level*100;
	maxMana = maxLife*50;
	maxWeight = level*10;
	life = maxLife;
	mana = maxMana;
	weight = maxWeight;
}
void Ball::downLevel(){
	level--;
	if(level<=0){
		level = 0;
		setAlive(false);
	}
	maxLife = level*100;
	maxMana = maxLife*50;
	maxWeight = level*10;
	maxDef = level*20;

	life = maxLife;
	mana = maxMana;
	weight = maxWeight;
}

void Ball::move(){
}

bool Ball::isGround(){
	return ptGround;
}

void Ball::setGround(bool argu){
	ptGround = argu;
}

void Ball::setPositionX(float argu){
	ptPosition.x = argu;
}
void Ball::setPositionY(float argu){
	ptPosition.y = argu;
}
void Ball::setPositionZ(float argu){
	ptPosition.z = argu;
}
void Ball::setVelocityX(float argu){
	ptVelocity.x = argu;
}
void Ball::setVelocityY(float argu){
	ptVelocity.y = argu;
}
void Ball::setVelocityZ(float argu){
	ptVelocity.z = argu;
}
void Ball::setGoalX(float argu){
	ptGoal.x = argu;
}
void Ball::setGoalY(float argu){
	ptGoal.y = argu;
}
void Ball::setGoalZ(float argu){
	ptGoal.z = argu;
}
D3DXVECTOR3 Ball::getPosition(){
	return ptPosition;
}
D3DXVECTOR3 Ball::getVelocity(){
	return ptVelocity;
}
D3DXVECTOR3 Ball::getGoal(){
	return ptGoal;
}
void Ball::setDefence(int argu){
	if(def+argu > maxDef)
		def = maxDef;
	else
		def += argu;
}