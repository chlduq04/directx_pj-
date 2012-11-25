#ifndef _MOVING_H_
#define _MOVING_H_

#include <d3dx9.h>
#include <d3d9.h>
#include "Ball.h"
#include "ItemsList.h"

class Moving{
private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 vel;
	D3DXVECTOR3 goal;
	int bCount;
	float vGravity;
	float rGravity;
	float yGround;
	float mySize;
	float rThreshold;
	float bSpeed;
	float gSpeed;
	float gAbsorbance;
	float minBoundx;
	float minBoundy;
	float minBoundz;
	float maxBoundx;
	float maxBoundy;
	float maxBoundz;
	float rCeiling;
public:
	Moving(float gravity,float reversegravity,float ground,float mysize,float ceiling,float threshold,float ballspeed,float gamespeed,float absorbance,float minboundx,float minboundy,float minboundz,float maxboundx,float maxboundy,float maxboundz);
	void getPosition(Ball* cha,float speed);
	void getItem(Ball* cha,ItemsList* itList,int mySize,int itemSize);
	void crashMon(Ball* cha);
};

#endif