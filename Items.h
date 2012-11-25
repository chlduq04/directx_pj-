#ifndef _ITEMS_H_
#define _ITEMS_H_

#include <d3d9.h>
#include <d3dx9.h>

class Items{
private:
	int itNum;
	int hp;
	int mp;
	int defence;
	int speed;
	
	
	float mTime;

	D3DXVECTOR3 ptPosition;
	D3DXVECTOR3 ptVelocity;
	D3DXVECTOR3 ptGoal;

	Items* iprev;
	Items* inext;

public:
	Items();
	Items(char* type,int level,D3DXVECTOR3 position,int static_item_number,float time);
	int getNumber();
	int getHp();
	int getMp();
	int getDef();
	int getSpd();
	void setPosition(D3DXVECTOR3 argu);
	void setVelocity(D3DXVECTOR3 argu);
	void setGoal(D3DXVECTOR3 argu);
	void setPositionX(float argu);
	void setPositionY(float argu);
	void setPositionZ(float argu);
	void setVelocityX(float argu);
	void setVelocityY(float argu);
	void setVelocityZ(float argu);
	void setGoalX(float argu);
	void setGoalY(float argu);
	void setGoalZ(float argu);


	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getVelocity();
	D3DXVECTOR3 getGoal();

	void setPrev(Items* argu);
	void setNext(Items* argu);
	Items* getPrev();
	Items* getNext();

	float getTime();
};

#endif