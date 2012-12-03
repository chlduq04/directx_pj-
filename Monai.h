#ifndef _MONAI_H_
#define _MONAI_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "Monster.h"
#include "Ball.h"

class Monai{
private:
	float maxBoundx;
	float maxBoundz;
	float minBoundx;
	float minBoundz;
	float ActionStart;
	Monster* mon;
	Ball* cha;
	float speed;
	float monsize;
public:
	Monai(Monster* monster,Ball* cha,float max_x,float max_z,float min_x,float min_z,float game_speed, float mon_size);
	~Monai();
	void getPositionMon();
	void normalMove();
	void closetoMove();
	void stopMove();
	void jumpMove();
	void dodgeMove();

	void subAction();
	void defenceMode();
	void missileMode();
	void wallMode();
	void healingMode();
};
#endif
