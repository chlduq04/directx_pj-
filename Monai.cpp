#include "Monai.h"

Monai::Monai(Monster* monster,Ball* charecter,Missile* missile[]){
	zero.x = 0.0f;
	zero.y = 0.0f;
	zero.z = 0.0f;

	ActionStart = -1.0f;
	mon = monster;
	cha = charecter;

	for(int i=0;i<10;i++){
		msi[i] = missile[i];
	}
	
}
Monai::~Monai(){}
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
		mon->setVelocity((mon->getGoal()-mon->getPosition())/200*GAMESPEED);
	}else{
		mon->setPostion(mon->getPosition()+mon->getVelocity());
		if( abs(mon->getPosition().x-mon->getGoal().x)< (MON_REAL_SIZE/2)*(MON_REAL_SIZE/2) ){
			mon->setVelocityX(0.0f);
			mon->setVelocityY(0.0f);
			mon->setVelocityZ(0.0f);
			mon->setisGoal(false);
		}
	}
}
void Monai::normalMove(double time){
	if(!mon->isGoal()){
		mon->setGoalX((rand()%(int)MAXBOUNDX)-MINBOUNDX);
		mon->setGoalY(1.0f);
		mon->setGoalZ((rand()%(int)MAXBOUNDZ)-MINBOUNDZ);
		mon->setVelocity((mon->getGoal()-mon->getPosition())/400*GAMESPEED);
		mon->setisGoal(true);

//		D3DXVec3Normalize(&face,&mon->getGoal());
//		rotate = D3DXVec3Dot(&zero,&mon->getGoal());
	}else{
		mon->setPostion(mon->getPosition()+mon->getVelocity());
		if( abs(mon->getPosition().x-mon->getGoal().x)< (MON_REAL_SIZE/2)*(MON_REAL_SIZE/2) ){
			mon->setVelocityX(0.0f);
			mon->setVelocityY(0.0f);
			mon->setVelocityZ(0.0f);
			mon->setisGoal(false);
		}
		if(mon->getPosition().x>MAXBOUNDX) mon->setPostionX(MAXBOUNDX);
		if(mon->getPosition().x<MINBOUNDX) mon->setPostionX(MINBOUNDX);
		if(mon->getPosition().y>MAXBOUNDY) mon->setPostionY(MAXBOUNDY);
		if(mon->getPosition().y<MINBOUNDY) mon->setPostionY(MINBOUNDY);
		if(mon->getPosition().z>MAXBOUNDZ) mon->setPostionZ(MAXBOUNDZ);
		if(mon->getPosition().z<MINBOUNDZ) mon->setPostionZ(MINBOUNDZ);
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
	for(int i=0;i<10;i++){
		msi[i]->moveMissile(mon,cha,time);
	}
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