#include "Missile.h"

Missile::Missile(float missilesize,float monsize,float mysize,float max_x,float max_y,float max_z,float min_x,float min_y,float min_z){
	mySize = mysize;
	monSize = monsize;
	missileSize = missilesize;

	maxBoundx = max_x;
	maxBoundy = max_y;
	maxBoundz = max_z;

	minBoundx = min_x;
	minBoundz = min_y;
	minBoundy = min_z;

	vDemage = 10;
	nowType = 0;
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
void Missile::moveMissile(Monster* mon,Ball* cha){
	switch(nowType){
	case 0:
		startPosition(mon);
		rendGoal(cha);
		rendValue();
		nowType = 1;
		break;
	case 1:
		missile_wall_length = vPosition - vBackPosition;
		m = D3DXVec3Length(&missile_wall_length);
		if(D3DXVec3Length(&missile_wall_length)>4.0f){setPosition(vPosition+(vBackPosition-vPosition)/4000);}
		else{nowType = 2;}
		break;
	case 2:
		missile_my_length = vPosition - cha->getPosition();
		D3DXVec3Normalize(&vGoal,&vGoal);
		vVelocity = vGoal;
		setPosition(vPosition+vVelocity);
		if(vPosition.x>maxBoundx*2||vPosition.y>maxBoundy*2||vPosition.z>maxBoundz*2||vPosition.x<minBoundx-100||vPosition.y<minBoundy-100||vPosition.z<minBoundz-100){
			nowType = 3;
		}
		if(D3DXVec3Length(&missile_my_length)<(mySize+missileSize)*(mySize+missileSize)){
			//demage coding!
			nowType = 3;
		}
		break;
	case 3:
		break;
	}
}

