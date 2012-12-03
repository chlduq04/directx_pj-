#ifndef _MOVING_H_
#define _MOVING_H_

#include <d3dx9.h>
#include <d3d9.h>
#include <stdio.h>
#include "Monster.h"
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

	bool wallxl;
	bool wallxr;
	bool wallyl;
	bool wallyr;
	bool wallzl;
	bool wallzr;
	float wall_position;
	float wall_bounce;

	float ActionStart;

public:
	Moving(float gravity,float reversegravity,float ground,float mysize,float ceiling,float threshold,float ballspeed,float gamespeed,float absorbance,float minboundx,float minboundy,float minboundz,float maxboundx,float maxboundy,float maxboundz);
	void getPositionWall(Ball* cha,float speed,D3DXVECTOR3 wall);
	void getPosition(Ball* cha,float speed);
	void getItem(Ball* cha,ItemsList* itList,int mySize,int itemSize);
	void crashMon(Ball* cha);
};

#endif