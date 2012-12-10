#include "Ball.h"

Ball::Ball(){
	
}
Ball::Ball(D3DXVECTOR3 setPosition,D3DXVECTOR3 setVelocity,D3DXVECTOR3 setGoal){
	level = 1;
	maxLevel = CHARACTER_MAX_LEVEL;
	alive = true;

	life = START_LIFE;
	maxLife = START_LIFE;

	def = 20;
	maxDef = 20;

	mana = START_MANA;
	maxMana = START_MANA;

	weight = START_WEIGHT;
	maxWeight = START_WEIGHT;

	ptPosition = setPosition;
	ptVelocity = setVelocity;
	ptGoal = setGoal;
	ptGround = false;
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
bool Ball::spendLife(int argu){
	if(life+argu<0){
		life = 0;
		setAlive(false);
		return false;
	}
	else{
		life = life + argu;
		return true;
	}
	return false;
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
bool Ball::spendMana(int argu){
	if(mana+argu<0){
		return false;
	}
	else{
		mana = mana + argu;
		return true;
	}
	return false;
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
		if(weight+argu<1){
			weight = 1;
		}
		else{
			weight = weight + argu;
		}
	}
}
bool Ball::spendWeight(int argu){
	if(weight+argu<1){
		weight = 1;
		return false;
	}
	else{
		weight = weight + argu;
		return true;
	}
	return true;
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

void Ball::setDefence(int argu){
	if(argu>0){
		if(def+argu > maxDef)
			def = maxDef;
		else
			def += argu;
	}
	else{
		if(def+argu < 0){
			life -= def + argu;
		}
		else{
			def += argu;
		}
	}
}