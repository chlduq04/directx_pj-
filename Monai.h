#ifndef _MONAI_H_
#define _MONAI_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "Monster.h"
#include "Ball.h"

class Monai{
private:
	D3DXVECTOR3 face;
	D3DXVECTOR3 zero;
	float rotate;

	int maxBoundx;
	int maxBoundy;
	int maxBoundz;
	int minBoundx;
	int minBoundy;
	int minBoundz;

	float ActionStart;
	Monster* mon;
	Ball* cha;
	float speed;
	float monsize;
public:
	Monai(Monster* monster,Ball* charecter, float max_x,float max_y,float max_z,float min_x,float min_y,float min_z,float game_speed, float mon_size);
	~Monai();
	void getPositionMon(double time);
	void normalMove(double time);
	void closetoMove(double time);
	void stopMove(double time);
	void jumpMove(double time);
	void dodgeMove(double time);

	void subAction(double time);
	void defenceMode(double time);
	void missileMode(double time);
	void wallMode(double time);
	void healingMode(double time);

	D3DXVECTOR3 getNormal();
	float getRotation();
};
#endif
