#include "Monai.h"

Monai::Monai(Monster* monster,Ball* charecter, float max_x,float max_z,float min_x,float min_z,float game_speed, float mon_size){
	maxBoundx = max_x;
	maxBoundz = max_z;
	minBoundx = min_x;
	minBoundz = min_z;
	ActionStart = -1.0f;
	mon = monster;
	cha = charecter;
	speed = game_speed;
	monsize = mon_size;
}
Monai::~Monai(){
}
void Monai::getPositionMon(){
	switch(mon->getmType()){
	case 0:
		normalMove();
		break;
	case 1:
		closetoMove();
		break;
	case 2:
		stopMove();
		break;
	case 3:
		jumpMove();
		break;
	case 4:
		dodgeMove();
		break;
	default:
		break;
	}
}
void Monai::closetoMove(){
	if(!mon->isGoal()){
		mon->setGoalX(cha->getPosition().x);
		mon->setGoalY(1.0f);
		mon->setGoalZ(cha->getPosition().z);
	}else{
		mon->setPostion(mon->getPosition()+mon->getVelocity());
		if( abs(mon->getPosition().x-mon->getGoal().x)< (monsize/2)*(monsize/2) ){
			mon->setVelocityX(0.0f);
			mon->setVelocityY(0.0f);
			mon->setVelocityZ(0.0f);
			mon->setisGoal(false);
		}
	}
}
void Monai::normalMove(){
	if(!mon->isGoal()){
		mon->setGoalX(rand()/maxBoundx-minBoundx);
		mon->setGoalY(1.0f);
		mon->setGoalZ(rand()/maxBoundz-minBoundz);
		mon->setVelocity((mon->getGoal()-mon->getPosition())/400*speed);
		mon->setisGoal(true);
	}else{
		mon->setPostion(mon->getPosition()+mon->getVelocity());
		if( abs(mon->getPosition().x-mon->getGoal().x)< (monsize/2)*(monsize/2) ){
			mon->setVelocityX(0.0f);
			mon->setVelocityY(0.0f);
			mon->setVelocityZ(0.0f);
			mon->setisGoal(false);
		}
	}
}
void Monai::jumpMove(){

}
void Monai::dodgeMove(){

}
void Monai::stopMove(){

}

void Monai::defenceMode(){
	if(ActionStart < 0.0f){
		ActionStart = (float)timeGetTime() * 0.001f;
	}

	mon->monDefence(100);

	if((float)timeGetTime() * 0.001f - ActionStart>mon->getDefTime()){
		ActionStart = -1.0f;
	}
}

void Monai::missileMode(){
	
}
void Monai::wallMode(){

}
void Monai::healingMode(){

}

void Monai::subAction(){
	switch(mon->getsType()){
	case 0:
		missileMode();
		break;
	case 1:
		wallMode();
		break;
	case 2:
		healingMode();
		break;
	default:
		break;
}
