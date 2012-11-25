#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <d3d9.h>
#include <d3dx9.h>

class Monster{
private:
	bool alive;
	int life;
	int weight;
	D3DXVECTOR3 vPosition; 
	D3DXVECTOR3 vVelocity;
	D3DXVECTOR3 vGoal;
	bool bGround;
public:
	Monster();
	Monster(int life,int weight,D3DXVECTOR3 position,D3DXVECTOR3 velocity,D3DXVECTOR3 goal);
	bool isAlive();
	int hisLife();
	int hisWeight();
	D3DXVECTOR3 hisPosition();
	D3DXVECTOR3 hisVelocity();
	D3DXVECTOR3 hisGoal();
	bool isGround();
};
#endif