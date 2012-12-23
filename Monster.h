#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Settings.h"
class Monster{
private:
	int pase;
	float mLife;
	int mWeight;
	float mAttack;
	int mDefence;
	int originType;
	int mType;
	int sType;

	float maxLife;
	
	int mMotion;

	bool mAlive;
	D3DXVECTOR3 vPosition; 
	D3DXVECTOR3 vVelocity;
	D3DXVECTOR3 vGoal;
	D3DXVECTOR3 vRotate;
	bool bGround;
	bool bMove;
	bool bJump;
	bool bGoal;
	bool doAction;
	float defendTime;

public:
	Monster();
	~Monster();
	Monster(D3DXVECTOR3 position,D3DXVECTOR3 velocity,D3DXVECTOR3 goal);
	void monMoving(D3DXVECTOR3 limitMove,float max_x,float max_y,float max_z,float error);
	void monDefence(int def);
	void monAttack();
	void monMissile();
	void monJump();
	void monHealing();
	

	inline float getAttack(){return mAttack;};
	inline void setisGoal(bool argu){bGoal = argu;};
	inline bool isGoal(){return bGoal;};
	inline bool isAlive(){return mAlive;};
	inline float hisLife(){return mLife;};
	inline bool isbGround(){return bGround;};

	inline void setGoal(D3DXVECTOR3 goal){vGoal = goal;};
	inline void setGoalX(float goal){vGoal.x = goal;};
	inline void setGoalY(float goal){vGoal.y = goal;};
	inline void setGoalZ(float goal){vGoal.z = goal;};
	inline D3DXVECTOR3 getGoal(){return vGoal;};

	inline void setPosition(D3DXVECTOR3 position){vPosition = position;};
	inline void setPositionX(float position){vPosition.x = position;};
	inline void setPositionY(float position){vPosition.y = position;};
	inline void setPositionZ(float position){vPosition.z = position;};
	inline D3DXVECTOR3 getPosition(){return vPosition;};

	inline void setMove(bool argu){bMove = argu;};
	inline bool isMove(){return bMove;};

	inline void setJump(bool argu){bJump = argu;};
	inline bool isJump(){return bJump;};

	inline void setVelocity(D3DXVECTOR3 vel){vVelocity = vel;};
	inline void setVelocityX(float vel){vVelocity.x = vel;};
	inline void setVelocityY(float vel){vVelocity.y = vel;};
	inline void setVelocityZ(float vel){vVelocity.z = vel;};
	inline D3DXVECTOR3 getVelocity(){return vVelocity;};
	
	inline void setOriginType(int type){originType = type;};
	inline int getOriginType(){return originType;};
	inline void setmType(int type){mType = type;};
	inline int getmType(){return mType;};
	
	inline void setsType(int type){sType= type;};
	inline int getsType(){return sType;};
	
	inline float getDefTime(){return defendTime;};
	inline int getPase(){return pase;};
	inline bool isAction(){return doAction;};

	inline int getDef(){return mDefence;};
	inline float getLife(){return mLife;};
	inline void setLife(float dmg){
		mLife = dmg * (100-mDefence)/100 + mLife;
	};
	inline void setRotate(D3DXVECTOR3 rotation){vRotate = rotation;};
	inline D3DXVECTOR3 getRotation(){return vRotate;};
};
#endif