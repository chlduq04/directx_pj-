#ifndef _MOVING_H_
#define _MOVING_H_

#include <d3dx9.h>
#include <d3d9.h>
#include <stdio.h>
#include "Monster.h"
#include "Ball.h"
#include "ItemsList.h"
#include "Settings.h"
#include "Missile.h"

class Moving{
private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 vel;
	D3DXVECTOR3 goal;
	int bCount;
	float crashTime;
	bool isCrash;
	float wall_bounce;
	float ActionStart;

	float maxboundx;
	float maxboundy;
	float maxboundz;
	float minboundx;
	float minboundy;
	float minboundz;
	bool monWall;

public:
	Moving();
	void getPositionWall(Ball* cha,D3DXVECTOR3 wall);
	void getPosition(Ball* cha,float speed);
	void getItem(Ball* cha,ItemsList* itList);
	void crashMon(Ball* cha, Monster* mon,float time);
	void crashMissile(Ball* cha,Missile* msi);
};

#endif