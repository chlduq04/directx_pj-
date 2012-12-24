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
	void MonMoving(D3DXVECTOR3 limitMove,float max_x,float max_y,float max_z,float error);
	void MonDefence(int def);
	void MonAttack();
	void MonMissile();
	void MonJump();
	void MonHealing();
	

	inline float GetAttack(){return mAttack;};
	inline void SetisGoal(bool argu){bGoal = argu;};
	inline bool IsGoal(){return bGoal;};
	inline bool IsAlive(){return mAlive;};
	inline float HisLife(){return mLife;};
	inline bool IsbGround(){return bGround;};

	inline void SetGoal(D3DXVECTOR3 goal){vGoal = goal;};
	inline void SetGoalX(float goal){vGoal.x = goal;};
	inline void SetGoalY(float goal){vGoal.y = goal;};
	inline void SetGoalZ(float goal){vGoal.z = goal;};
	inline D3DXVECTOR3 GetGoal(){return vGoal;};

	inline void SetPosition(D3DXVECTOR3 position){vPosition = position;};
	inline void SetPositionX(float position){vPosition.x = position;};
	inline void SetPositionY(float position){vPosition.y = position;};
	inline void SetPositionZ(float position){vPosition.z = position;};
	inline D3DXVECTOR3 GetPosition(){return vPosition;};

	inline void SetMove(bool argu){bMove = argu;};
	inline bool IsMove(){return bMove;};

	inline void SetJump(bool argu){bJump = argu;};
	inline bool IsJump(){return bJump;};

	inline void SetVelocity(D3DXVECTOR3 vel){vVelocity = vel;};
	inline void SetVelocityX(float vel){vVelocity.x = vel;};
	inline void SetVelocityY(float vel){vVelocity.y = vel;};
	inline void SetVelocityZ(float vel){vVelocity.z = vel;};
	inline D3DXVECTOR3 GetVelocity(){return vVelocity;};
	
	inline void SetOriginType(int type){originType = type;};
	inline int GetOriginType(){return originType;};
	inline void SetmType(int type){mType = type;};
	inline int GetmType(){return mType;};
	
	inline void SetsType(int type){sType= type;};
	inline int GetsType(){return sType;};
	
	inline float GetDefTime(){return defendTime;};
	inline int GetPase(){return pase;};
	inline bool IsAction(){return doAction;};

	inline int GetDef(){return mDefence;};
	inline float GetLife(){return mLife;};
	inline void SetLife(float dmg){
		mLife = dmg * (100-mDefence)/100 + mLife;
	};
	inline void SetRotate(D3DXVECTOR3 rotation){vRotate = rotation;};
	inline D3DXVECTOR3 GetRotation(){return vRotate;};
};
#endif