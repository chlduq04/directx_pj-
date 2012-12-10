#include "Monai.h"

Monai::Monai(Monster* monster,Ball* charecter, float max_x,float max_y,float max_z,float min_x,float min_y,float min_z,float game_speed, float mon_size){
	zero.x = 0.0f;
	zero.y = 0.0f;
	zero.z = 0.0f;

	maxBoundx = (int)max_x;
	maxBoundy = (int)max_y;
	maxBoundz = (int)max_z;
	minBoundx = (int)min_x;
	minBoundy = (int)min_y;
	minBoundz = (int)min_z;
	ActionStart = -1.0f;
	mon = monster;
	cha = charecter;
	speed = game_speed;
	monsize = mon_size;
}
Monai::~Monai(){

}
void Monai::getPositionMon(double time){
	switch(mon->getmType()){
	case 0:
		normalMove(time);
		break;
	case 1:
		closetoMove(time);
		break;
	case 2:
		stopMove(time);
		break;
	case 3:
		jumpMove(time);
		break;
	case 4:
		dodgeMove(time);
		break;
	default:
		break;
	}
}
void Monai::closetoMove(double time){
	if(!mon->isGoal()){
		mon->setGoalX(cha->getPosition().x);
		mon->setGoalY(1.0f);
		mon->setGoalZ(cha->getPosition().z);
		mon->setVelocity((mon->getGoal()-mon->getPosition())/200*speed);
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
void Monai::normalMove(double time){
	if(!mon->isGoal()){
		mon->setGoalX((rand()%maxBoundx)-minBoundx);
		mon->setGoalY(1.0f);
		mon->setGoalZ((rand()%maxBoundz)-minBoundz);
		mon->setVelocity((mon->getGoal()-mon->getPosition())/400*speed);
		mon->setisGoal(true);

//		D3DXVec3Normalize(&face,&mon->getGoal());
//		rotate = D3DXVec3Dot(&zero,&mon->getGoal());
	}else{
		mon->setPostion(mon->getPosition()+mon->getVelocity());
		if( abs(mon->getPosition().x-mon->getGoal().x)< (monsize/2)*(monsize/2) ){
			mon->setVelocityX(0.0f);
			mon->setVelocityY(0.0f);
			mon->setVelocityZ(0.0f);
			mon->setisGoal(false);
		}
		if(mon->getPosition().x>maxBoundx) mon->setPostionX(maxBoundx);
		if(mon->getPosition().x<minBoundx) mon->setPostionX(minBoundx);
		if(mon->getPosition().y>maxBoundy) mon->setPostionY(maxBoundy);
		if(mon->getPosition().y<minBoundy) mon->setPostionY(minBoundy);
		if(mon->getPosition().z>maxBoundz) mon->setPostionZ(maxBoundz);
		if(mon->getPosition().z<minBoundz) mon->setPostionZ(minBoundz);
	}
}
void Monai::jumpMove(double time){

}
void Monai::dodgeMove(double time){

}
void Monai::stopMove(double time){

}

void Monai::defenceMode(double time){
	if(ActionStart < 0.0f){
		ActionStart = time;
	}

	mon->monDefence(100);

	if((float)timeGetTime() * 0.001f - ActionStart>mon->getDefTime()){
		ActionStart = -1.0f;
	}
}

void Monai::missileMode(double time){
	
}
void Monai::wallMode(double time){

}
void Monai::healingMode(double time){

}

void Monai::subAction(double time){
	switch(mon->getsType()){
	case 0:
		missileMode(time);
		break;
	case 1:
		wallMode(time);
		break;
	case 2:
		healingMode(time);
		break;
	default:
		break;
	}
}

D3DXVECTOR3 Monai::getNormal(){
	return face;
}
float Monai::getRotation(){
	return rotate;
}