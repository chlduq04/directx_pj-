#ifndef _MONAI_H_
#define _MONAI_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "Monster.h"
#include "Ball.h"
#include "Missile.h"
#include "Settings.h"
#include "Moving.h"
#include "Wall.h"
#include "Pattern.h"
#include "CheckAI.h"
class Monai{
private:
	int actionNum; 
	int motionNum;
	float motiontime;

	D3DXVECTOR3 velocty;
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
	Wall* wall;
	Checkai* checkResult;
	Missile* msi[10];
	Pattern* nowAction;
	float speed;
	float monsize;
	float monSpeed;
	int wallPos;

	bool doAction;

	float defStartTime; //��5sec
	float defEndTime; //��15sec
	bool defon;
	float wallStartTime; //��10sec
	float wallEndTime; //��25sec
	bool wallon;	
	float healStartTime; //��5sec
	float healEndTime; //��15sec
	float healEachDelay;
	bool healon;	
	float raserStartTime; //��5sec
	float raserEndTime; //��30sec
	bool raseron;
	float rushStartTime; //��5sec
	float rushEndTime; //��10sec
	bool rushon;
	float msiStartTime; 
	float msiEndTime; 
	bool msion;
	bool msionAll;
	float norAttStartTime; 
	float norAttEndTime; 
	bool naton;


public:
	Monai(Monster* monster,Ball* charecter,Missile* missile[],Moving* moving,Wall* createwall,Checkai* result,float time);
	~Monai();

	void Pase0(float time);
	void Pase1(float time);
	void Pase2(float time);


	void subAction(float time);
	bool defenceMode(float time);
	bool missileMode(float time);
	bool wallMode(float time);
	bool healingMode(float time);
	bool raserMode(float time);
	bool rushMode(float time);
	bool normalAtt(float time);
	bool canDef(float time);
	bool canMissile(float time);
	bool canHealing(float time);
	bool canRaser(float time);
	bool canRush(float time);
	bool canNorAtt(float time);
	void getPositionMon(float time);
	void normalMove(float time);
	void closetoMove(float time);
	void stopMove(float time);
	void jumpMove(float time);
	void dodgeMove(float time);
	void examType(int type,float time);
	inline void randPositionMon(){mon->setOriginType(rand()%26);};

	inline bool getMsionall(){return msionAll;};

	D3DXVECTOR3 getNormal();
	float getRotation();
};
#endif
