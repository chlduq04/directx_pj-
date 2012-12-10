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
		nowType = 1;
		break;
	case 1:
		missile_wall_length = vBackPosition - vPosition;
		if(!D3DXVec3Length(&missile_wall_length)<4.0f){setPosition(vPosition+vBackPosition/400);}
		else{nowType = 2;}
		break;
	case 2:
		missile_my_length = cha->getPosition() - vPosition;
		D3DXVec3Normalize(&vGoal,&vGoal);
		vVelocity = vGoal*30.0f;
		setPosition(vPosition+vVelocity);
		if(vPosition.x>maxBoundx||vPosition.y>maxBoundy||vPosition.z>maxBoundz||vPosition.x<minBoundx||vPosition.y<minBoundy||vPosition.z<minBoundz){
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

