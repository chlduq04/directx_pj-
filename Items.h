#ifndef _ITEMS_H_
#define _ITEMS_H_

#include <d3d9.h>
#include <d3dx9.h>

class Items{
private:
	int nType;
	int nItemNum;
	int nHp;
	int nMp;
	int nDefence;
	int nSpeed;
	
	float fTime;

	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vVelocity;
	D3DXVECTOR3 vGoal;

	Items* pPrev;
	Items* pNext;

public:
	Items();
	Items(int type,int level,D3DXVECTOR3 position,int static_item_number,float time);

	inline int GetNumber(){return nItemNum;};
	inline int GetHp(){return nHp;};
	inline int GetMp(){return nMp;};
	inline int GetDef(){return nDefence;};
	inline int GetSpd(){return nSpeed;};
	
	inline void SetPositionX(float argu){vPosition.x = argu;};
	inline void SetPositionY(float argu){vPosition.y = argu;};
	inline void SetPositionZ(float argu){vPosition.z = argu;};
	inline void SetVelocityX(float argu){vVelocity.x = argu;};
	inline void SetVelocityY(float argu){vVelocity.y = argu;};
	inline void SetVelocityZ(float argu){vVelocity.z = argu;};
	inline void SetGoalX(float argu){vGoal.x = argu;};
	inline void SetGoalY(float argu){vGoal.y = argu;};
	inline void SetGoalZ(float argu){vGoal.z = argu;};
	inline void SetPosition(D3DXVECTOR3 argu){vPosition = argu;};
	inline void SetVelocity(D3DXVECTOR3 argu){vVelocity = argu;};
	inline void SetGoal(D3DXVECTOR3 argu){vGoal = argu;};

	inline D3DXVECTOR3 GetPosition(){return vPosition;};
	inline D3DXVECTOR3 GetVelocity(){return vVelocity;};
	inline D3DXVECTOR3 GetGoal(){return vGoal;};
	inline void SetPrev(Items* argu){pPrev = argu;};
	inline void SetNext(Items* argu){pNext = argu;};
	inline Items* GetPrev(){return pPrev;};
	inline Items* GetNext(){return pNext;};
	inline float GetTime(){return fTime;};
	inline int GetType(){return nType;};
};
#endif