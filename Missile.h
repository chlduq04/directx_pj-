#ifndef _MISSILE_H_
#define _MISSILE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Monster.h"
#include "Ball.h"
#include "Settings.h"
class Missile{
private:
	D3DXVECTOR3 vPosition; //위치
	D3DXVECTOR3 vBackPosition; // 다른 이동 위치
	D3DXVECTOR3 vVelocity; //방향벡터
	D3DXVECTOR3 vGoal;
	D3DXVECTOR3 vMissile_wall_length; 
	D3DXVECTOR3 vMissile_my_length;
	D3DXVECTOR3 vMissile_goal_length;
	int nDemage;
	int nNowType;
	bool bStart;
public:
	Missile();
	inline void SetPosition(D3DXVECTOR3 position){vPosition = position;};
	inline D3DXVECTOR3 GetPosition(){return vPosition;};
	inline void SetBackPosition(D3DXVECTOR3 backposition){vBackPosition = backposition;};
	inline D3DXVECTOR3 GetBackPosition(){return vBackPosition;};
	inline void SetVelocity(D3DXVECTOR3 velocity){vVelocity = velocity;};
	inline D3DXVECTOR3 GetVelocity(){return vVelocity;};
	inline void SetGoal(D3DXVECTOR3 goal){vGoal = goal;};
	inline D3DXVECTOR3 GetGoal(){return vGoal;};
	inline void SetDemage(int demage){nDemage = demage;};
	inline int GetDemage(){return nDemage;};
	inline bool GetStart(){return bStart;};
	inline void GetStart(bool on){bStart = on;};

	void StartPosition(Monster* mon);
	void RendGoal(Ball* cha);
	void RendValue();
	void MoveMissile(Monster* mon,Ball* cha,float time);
	inline void Start(){nNowType = 0;};
	inline bool NowStart(){return bStart;};
	inline int GetType(){return nNowType;};

};

#endif