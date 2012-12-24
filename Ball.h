#ifndef _BALL_H_
#define _BALL_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Settings.h"
class Ball{
private:
	int nLevel;
	int nMaxLevel;

	bool bAlive;
	int nLife;
	int nMana;
	int nWeight;
	int nDef;

	int nMaxLife;
	int nMaxMana;
	int nMaxWeight;
	int nMaxDef;
	bool bGround;

	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vVelocity;
	D3DXVECTOR3 vGoal;
	
public:
	Ball();
	Ball(D3DXVECTOR3 setPosition,D3DXVECTOR3 setVelocity,D3DXVECTOR3 setGoal);

	void SetMaxLife(int argu);
	void SetMaxMana(int argu);
	void SetMaxWeight(int argu);
	void SetMaxDef(int argu);

	void SetLife(int argu);
	void SetMana(int argu);
	void SetDef(int argu);

	bool SpendMana(int argu);
	bool SpendDef(int argu);

	void UpLevel();
	void DownLevel();
	
	void SetDefence(int argu);
	void GetDefence();

	inline bool IsAlive(){return bAlive;};
	inline void SetAlive(bool argu){bAlive = argu;};
	inline int HisLife(){return nLife;};
	inline int HisMana(){return nMana;};
	inline int HisWeight(){return nWeight;};
	inline int HisDef(){return nDef;};
	inline void SetPosition(D3DXVECTOR3 xyz){vPosition = xyz;};
	inline void SetVelocity(D3DXVECTOR3 xyz){vVelocity= xyz;};
	inline void SetGoal(D3DXVECTOR3 xyz){vGoal = xyz;};
	
	inline bool IsGround(){return bGround;}
	inline void SetGround(bool argu){bGround = argu;}

	inline void SetPositionX(float argu){vPosition.x = argu;}
	inline void SetPositionY(float argu){vPosition.y = argu;}
	inline void SetPositionZ(float argu){vPosition.z = argu;}
	inline void SetVelocityX(float argu){vVelocity.x = argu;}
	inline void SetVelocityY(float argu){vVelocity.y = argu;}
	inline void SetVelocityZ(float argu){vVelocity.z = argu;}
	inline void SetGoalX(float argu){vGoal.x = argu;}
	inline void SetGoalY(float argu){vGoal.y = argu;}
	inline void SetGoalZ(float argu){vGoal.z = argu;}
	inline D3DXVECTOR3 GetPosition(){return vPosition;}
	inline D3DXVECTOR3 GetVelocity(){return vVelocity;}
	inline D3DXVECTOR3 GetGoal(){return vGoal;}


};
#endif 