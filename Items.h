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

	inline int getNumber(){return itNum;};
	inline int getHp(){return hp;};
	inline int getMp(){return mp;};
	inline int getDef(){return defence;};
	inline int getSpd(){return speed;};
	inline void setPositionX(float argu){ptPosition.x = argu;};
	inline void setPositionY(float argu){ptPosition.y = argu;};
	inline void setPositionZ(float argu){ptPosition.z = argu;};
	inline void setVelocityX(float argu){ptVelocity.x = argu;};
	inline void setVelocityY(float argu){ptVelocity.y = argu;};
	inline void setVelocityZ(float argu){ptVelocity.z = argu;};
	inline void setGoalX(float argu){ptGoal.x = argu;};
	inline void setGoalY(float argu){ptGoal.y = argu;};
	inline void setGoalZ(float argu){ptGoal.z = argu;};
	inline void setPosition(D3DXVECTOR3 argu){ptPosition = argu;};
	inline void setVelocity(D3DXVECTOR3 argu){ptVelocity = argu;};
	inline void setGoal(D3DXVECTOR3 argu){ptGoal = argu;};


	inline D3DXVECTOR3 getPosition(){return ptPosition;};
	inline D3DXVECTOR3 getVelocity(){return ptVelocity;};
	inline D3DXVECTOR3 getGoal(){return ptGoal;};

	inline void setPrev(Items* argu){iprev = argu;};
	inline void setNext(Items* argu){inext = argu;};
	inline Items* getPrev(){return iprev;};
	inline Items* getNext(){return inext;};
	inline float getTime(){return mTime;};
};
#endif