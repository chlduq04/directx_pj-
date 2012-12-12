#include "Wall.h"
Wall::Wall(){
	bouncecount = 0;
	ground = false;
	hp = 100;
	type = 0;
	vPosition = D3DXVECTOR3(0,MAXBOUNDY,0);
	vVelocity = D3DXVECTOR3(0,0,0);
}