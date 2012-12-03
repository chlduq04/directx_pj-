#ifndef _MONSTER_H_
#define _MONSTER_H_

#include <d3d9.h>
#include <d3dx9.h>

class Monster{
private:
	float mLife;
	int mWeight;
	float mAttack;
	int mDefence;
	int mType;
	int sType;

	float maxLife;
	
	int mMotion;
	bool mAlive;
	D3DXVECTOR3 vPosition; 
	D3DXVECTOR3 vVelocity;
	D3DXVECTOR3 vGoal;
	bool bGround;
	bool bMove;
	bool bJump;
	bool bGoal;
	
	float defendTime;

public:
	Monster();
	~Monster();
	Monster(float life,int weight,D3DXVECTOR3 position,D3DXVECTOR3 velocity,D3DXVECTOR3 goal);
	bool isAlive();
	int hisLife();
	bool isbGround();
	
	void setGoal(D3DXVECTOR3 goal);
	void setGoalX(float goal);
	void setGoalY(float goal);
	void setGoalZ(float goal);

	D3DXVECTOR3 getGoal();
	
	void setPostion(D3DXVECTOR3 position);
	void setPostionX(float position);
	void setPostionY(float position);
	void setPostionZ(float position);
	D3DXVECTOR3 getPosition();

	void setVelocity(D3DXVECTOR3 vel);
	void setVelocityX(float vel);
	void setVelocityY(float vel);
	void setVelocityZ(float vel);
	D3DXVECTOR3 getVelocity();



	void setMove(bool argu);
	bool isMove();

	void setJump(bool argu);
	bool isJump();

	void setmType(int type);
	int getmType();
	void setsType(int type);
	int getsType();

	bool isGoal();

	void monMoving(D3DXVECTOR3 limitMove,float max_x,float max_y,float max_z,float error);
	void monDefence(int def);
	void monAttack();
	void monMissile();
	void monJump();
	void monHealing();

	void setisGoal(bool argu);

	float getDefTime();
};
#endif