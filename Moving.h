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
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vVel;
	D3DXVECTOR3 vGoal;
	int nCount;
	int nWallCount;
	float fCrashTime;
	bool bCrash;
	float fWallBounce;
	float fActionStart;

	float fMaxboundx;
	float fMaxboundy;
	float fMaxboundz;
	float fMinboundx;
	float fMinboundy;
	float fMinboundz;
	bool bMonWall;
	bool bMonMaxWallX; 
	bool bMonMaxWallY; 
	bool bMonMaxWallZ; 
	bool bMonMinWallX; 
	bool bMonMinWallY; 
	bool bMonMinWallZ; 
	
	Ball* pCha;
	Monster* pMon;
	Wall* pWall;

public:
	Moving(Ball* myball,Monster* monster,Wall* wallset);
	void GetPositionWall(D3DXVECTOR3 wall,float speed);
	void GetPosition(float speed);
	void GetItem(ItemsList* itList);
	void CrashMon(float time);
	void CrashMissile(Missile* msi);
	void ReturnWall();

	inline bool GetMonWall(){return bMonWall;};
	inline void SetMonWall(bool argu){bMonWall = argu;};
	inline bool GetMonMaxWallX(){return bMonMaxWallX;};
	inline bool GetMonMaxWallY(){return bMonMaxWallY;};
	inline bool GetMonMaxWallZ(){return bMonMaxWallZ;};
	inline bool GetMonMinWallX(){return bMonMinWallX;};
	inline bool GetMonMinWallY(){return bMonMinWallY;};
	inline bool GetMonMinWallZ(){return bMonMinWallZ;};

	inline float GetMaxX(){return fMaxboundx;};
	inline float GetMinX(){return fMinboundx;};
	inline float GetMaxY(){return fMaxboundy;};
	inline float GetMinY(){return fMinboundy;};
	inline float GetMaxZ(){return fMaxboundz;};
	inline float GetMinZ(){return fMinboundz;};

};

#endif