#include "Missile.h"

Missile::Missile(){
	vDemage = -10;
	nowType = 0;
	isStart = false;
}

void Missile::startPosition(Monster* mon){
	setPosition(mon->getPosition() + D3DXVECTOR3(rand()%20-10,rand()%20-10,rand()%20-10));
}
void Missile::rendGoal(Ball* cha){
	setGoal(cha->getPosition() + D3DXVECTOR3(rand()%10-5,rand()%10-5,rand()%10-5));
}
void Missile::rendValue(){
	setBackPosition(vPosition + D3DXVECTOR3(rand()%10-5,rand()%10-5,rand()%10-5));
}
void Missile::moveMissile(Monster* mon,Ball* cha,float time){
	switch(nowType){
	case 0:
		isStart = true;
		startPosition(mon);
		rendValue();
		nowType = 1;
		break;
	case 1:
		missile_wall_length = vPosition - vBackPosition;
		if(D3DXVec3Length(&missile_wall_length)>4.0f){setPosition(vPosition+(vBackPosition-vPosition)/4000);}
		else{nowType = 2;}
		break;
	case 2:
		vGoal = cha->getPosition()+cha->getVelocity()*3;
		missile_my_length = vGoal - vPosition;
		D3DXVec3Normalize(&missile_my_length,&missile_my_length);
		vVelocity = missile_my_length;
		nowType = 3;
		break;
	case 3:
		missile_goal_length = vGoal - vPosition;
		setPosition(vPosition+vVelocity);
		if(vPosition.x>MAXBOUNDX*2||vPosition.y>MAXBOUNDY*2||vPosition.z>MAXBOUNDZ*2||vPosition.x<MINBOUNDX-100||vPosition.y<MINBOUNDY-100||vPosition.z<MINBOUNDZ-100){
			nowType = 4;
		}
		break;
	case 4:
		isStart = false;
		break;
	}
}

