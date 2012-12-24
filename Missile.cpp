#include "Missile.h"

Missile::Missile(){
	nDemage = -1;
	nNowType = 0;
	bStart = false;
}

void Missile::StartPosition(Monster* mon){
	SetPosition(mon->GetPosition() + D3DXVECTOR3(rand()%20-10,MINBOUNDY+rand()%20-10,rand()%20-10));
}
void Missile::RendGoal(Ball* cha){
	SetGoal(cha->GetPosition() + D3DXVECTOR3(rand()%10-5,rand()%10-5,rand()%10-5));
}
void Missile::RendValue(){
	SetBackPosition(vPosition + D3DXVECTOR3(rand()%15-7,MINBOUNDY+rand()%15-7,rand()%15-7));
}
void Missile::MoveMissile(Monster* mon,Ball* cha,float time){
	switch(nNowType){
	case 0:
		bStart = true;
		StartPosition(mon);
		RendValue();
		RendGoal(cha);
		nNowType = 1;
		break;
	case 1:
		vMissile_wall_length = vPosition - vBackPosition;
		if(D3DXVec3Length(&vMissile_wall_length)>6.0f){SetPosition(vPosition-(vMissile_wall_length)/1000);}
		else{nNowType = 2;}
		break;
	case 2:
		vGoal = cha->GetPosition()+cha->GetVelocity()*3;
		vMissile_my_length = vGoal - vPosition;
		D3DXVec3Normalize(&vMissile_my_length ,&vMissile_my_length );
		vVelocity = vMissile_my_length *4;
		nNowType = 3;
		break;
	case 3:
		SetPosition(vPosition+vVelocity/2);
		if(vPosition.x>MAXBOUNDX*2||vPosition.z>MAXBOUNDZ*2||vPosition.x<MINBOUNDX-100||vPosition.z<MINBOUNDZ-100){
			nNowType = 4;
		}
		break;
	case 4:
		if(bStart){
			bStart = false;
		}
		break;
	}
}

