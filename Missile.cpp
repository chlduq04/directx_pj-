#include "Missile.h"

Missile::Missile(){
	vDemage = -1;
	nowType = 0;
	isStart = false;
}

void Missile::startPosition(Monster* mon){
	setPosition(mon->getPosition() + D3DXVECTOR3(rand()%20-10,MINBOUNDY+rand()%20-10,rand()%20-10));
}
void Missile::rendGoal(Ball* cha){
	setGoal(cha->getPosition() + D3DXVECTOR3(rand()%10-5,rand()%10-5,rand()%10-5));
}
void Missile::rendValue(){
	setBackPosition(vPosition + D3DXVECTOR3(rand()%15-7,MINBOUNDY+rand()%15-7,rand()%15-7));
}
void Missile::moveMissile(Monster* mon,Ball* cha,float time){
	switch(nowType){
	case 0:
		isStart = true;
		startPosition(mon);
		rendValue();
		rendGoal(cha);
		nowType = 1;
		break;
	case 1:
		missile_wall_length = vPosition - vBackPosition;
		if(D3DXVec3Length(&missile_wall_length)>6.0f){setPosition(vPosition-(missile_wall_length)/1000);}
		else{nowType = 2;}
		break;
	case 2:
		vGoal = cha->getPosition()+cha->getVelocity()*3;
		missile_my_length = vGoal - vPosition;
		D3DXVec3Normalize(&missile_my_length,&missile_my_length);
		vVelocity = missile_my_length*4;
		nowType = 3;
		break;
	case 3:
		setPosition(vPosition+vVelocity/2);
		if(vPosition.x>MAXBOUNDX*2||vPosition.z>MAXBOUNDZ*2||vPosition.x<MINBOUNDX-100||vPosition.z<MINBOUNDZ-100){
			nowType = 4;
		}
		break;
	case 4:
		if(isStart){
			isStart = false;
		}
		break;
	}
}

