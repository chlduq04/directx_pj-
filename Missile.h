#ifndef _MISSILE_H_
#define _MISSILE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Monster.h"
#include "Ball.h"

class Missile{
private:
	D3DXVECTOR3 vPosition; //위치
	D3DXVECTOR3 vBackPosition; // 다른 이동 위치
	D3DXVECTOR3 vVelocity; //방향벡터
	D3DXVECTOR3 vGoal;
	D3DXVECTOR3 missile_wall_length; 
	D3DXVECTOR3 missile_my_length;
	D3DXVECTOR3 missile_goal_length;
	int vDemage;
	int nowType;
	bool isStart;
public:
	Missile();
	inline void setPosition(D3DXVECTOR3 position){vPosition = position;};
	inline D3DXVECTOR3 getPosition(){return vPosition;};
	inline void setBackPosition(D3DXVECTOR3 backposition){vBackPosition = backposition;};
	inline D3DXVECTOR3 getBackPosition(){return vBackPosition;};
	inline void setVelocity(D3DXVECTOR3 velocity){vVelocity = velocity;};
	inline D3DXVECTOR3 getVelocity(){return vVelocity;};
	inline void setGoal(D3DXVECTOR3 goal){vGoal = goal;};
	inline D3DXVECTOR3 getGoal(){return vGoal;};
	inline void setDemage(int demage){vDemage = demage;};
	inline int getDemage(){return vDemage;};
	inline bool getStart(){return isStart;};
	inline void setStart(bool on){isStart = on;};

	void startPosition(Monster* mon);
	void rendGoal(Ball* cha);
	void rendValue();
	void moveMissile(Monster* mon,Ball* cha,float time);
	inline void start(){nowType = 0;};
	inline int getType(){return nowType;};
};

#endif