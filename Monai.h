#ifndef _MONAI_H_
#define _MONAI_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "Monster.h"
#include "Ball.h"
#include "Missile.h"
#include "Settings.h"
#include "Moving.h"
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
	Moving* mov;
	Missile* msi[10];
	float speed;
	float monsize;
	int wallPos;
	float monSpeed;

	float defStartTime; //��5sec
	float defEndTime; //��15sec
	float defStartDelay;
	float defEndDelay;
	bool defon;
	float wallStartTime; //��10sec
	float wallEndTime; //��25sec
	float wallStartDelay;
	float wallEndDelay;
	bool wallon;	
	float healStartTime; //��5sec
	float healEndTime; //��15sec
	float healStartDelay;
	float healEndDelay;
	float healEachDelay;
	bool healon;	
	float raserStartTime; //��5sec
	float raserEndTime; //��30sec
	float raserStartDelay;
	float raserEndDelay;
	bool raseron;
	float rushStartTime; //��5sec
	float rushEndTime; //��10sec
	float rushStartDelay;
	float rushEndDelay;
	bool rushon;
	float msiStartTime; 
	float msiEndTime; 
	float msiStartDelay;
	float msiEndDelay;
	bool msion;

public:
	Monai(Monster* monster,Ball* charecter,Missile* missile[],Moving* moving,float time);
	~Monai();
	void subAction(float time);
	bool defenceMode(float time);
	bool missileMode(float time);
	bool wallMode(float time);
	bool healingMode(float time);
	bool raserMode(float time);
	bool rushMode(float time);
	
	bool canDef(float time);
	bool canMissile(float time);
	bool canHealing(float time);
	bool canRaser(float time);
	bool canRush(float time);
	
	void getPositionMon(float time);
	void normalMove(float time);
	void closetoMove(float time);
	void stopMove(float time);
	void jumpMove(float time);
	void dodgeMove(float time);

	inline void randPositionMon(float time){mon->setsType(rand()%26);};

	D3DXVECTOR3 getNormal();
	float getRotation();
};
#endif
