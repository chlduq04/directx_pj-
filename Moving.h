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
#include "Wall.h"
class Moving{
private:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 vel;
	D3DXVECTOR3 goal;
	int bCount;
	int bWallCount;
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
	bool monMaxWallX; 
	bool monMaxWallY; 
	bool monMaxWallZ; 
	bool monMinWallX; 
	bool monMinWallY; 
	bool monMinWallZ; 


public:
	Moving();
	void getPositionWall(Ball* cha,Wall* mWall,D3DXVECTOR3 wall,float speed);
	void getPosition(Ball* cha,float speed);
	void getItem(Ball* cha,ItemsList* itList);
	void crashMon(Ball* cha, Monster* mon,float time);
	void crashMissile(Ball* cha,Missile* msi);
	void returnWall();

	inline bool getMonWall(){return monWall;};

	inline bool getMonMaxWallX(){return monMaxWallX;};
	inline bool getMonMaxWallY(){return monMaxWallY;};
	inline bool getMonMaxWallZ(){return monMaxWallZ;};
	inline bool getMonMinWallX(){return monMinWallX;};
	inline bool getMonMinWallY(){return monMinWallY;};
	inline bool getMonMinWallZ(){return monMinWallZ;};

	inline float getMaxX(){return maxboundx;};
	inline float getMinX(){return minboundx;};
	inline float getMaxY(){return maxboundy;};
	inline float getMinY(){return minboundy;};
	inline float getMaxZ(){return maxboundz;};
	inline float getMinZ(){return minboundz;};

};

#endif