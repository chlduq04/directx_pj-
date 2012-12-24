#include "Wall.h"
Wall::Wall(){
	nBouncecount = 0;
	bGround = false;
	fHp = 100;
	fType = 0;
	vPosition = D3DXVECTOR3(0,MAXBOUNDY,0);
	vVelocity = D3DXVECTOR3(0,0,0);
}