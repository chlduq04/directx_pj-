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
#include "CModel.h"
class Monai{
private:
	FLOAT fAniMotionTime;
	INT nTypeCase;

	D3DXVECTOR3 vLength;
	D3DXVECTOR3 vVelocity;
	D3DXVECTOR3	vZline;
	D3DXVECTOR3 vFace;
	D3DXVECTOR3 vZero;

	float fMotionSpeed;

	float fActionStart;
	Monster* pMon;
	Ball* pCha;
	Moving* pMov;
	Wall* pWall;
	Checkai* pCheckResult;
	Missile* pMsi[MISSILE_COUNT];
	Pattern* pNowAction;
	Pattern* pCheckAction;
	CModel* pAniModel;
	float fSpeed;
	float fMonsize;
	float fMonSpeed;
	int nWallPos;

	BOOL bDoAction;

	BOOL bDefon;
	//BOOL bWallon;	
	float fHealEachDelay;
	BOOL bHealon;	
	BOOL bRaseron;
	BOOL bRushon;
	BOOL bMsion;
	BOOL bMsionAll;
	BOOL bMsionNext;
	BOOL bNaton;

	float g_fActionChange;

	float g_fCheckChaHP;
	float g_fCheckMonHP;

	int g_nMissileCount;
	INT g_nInitDefence;
	INT g_nInitHealing;
	INT g_nWallPosition;
	INT g_nPase;

public:
	Monai(Monster* monster,Ball* charecter,Missile* missile[MISSILE_COUNT],Moving* moving,Wall* createwall,Checkai* result,CModel* model,float time);
	~Monai();

	void Pase0();
	void Pase1();
	void Pase2();

	void SubAction(float time);

	void DefenceMode();
	void MissileMode();
	void WallMode();
	void HealingMode(float time);
	void LaserMode();
	void NormalAttMode();

	void DefenceModeStart();
	void MissileModeStart(float time);
	void WallModeStart();
	void HealingModeStart(float time);
	void LaserModeStart();
	void NormalAttModeStart();

	BOOL RushMode(float time);
	void GetPositionMon(float time);
	void NormalMove(float time);
	void ClosetoMove(float time);
	void StopMove(float time);
	void JumpMove(float time);
	void DodgeMove(float time);
	void Type(int type,float time);
	void Case(Pattern* pattern,float time);
	inline void RandPositionMon(){pMon->SetOriginType(rand()%20);};
	inline void SetPositionMon(int type){pMon->SetOriginType(type);};
	inline int GetRandType(){return rand()%5;};
	inline BOOL GetMsionall(){return bMsionAll;};

	void CheckChangePattern();
	D3DXVECTOR3 GetNormal();
	float GetRotation();
	void GetMoveType(float time);
	inline void InhenceMove(int type);
	void SetActionReset();
	inline float GetMotionTime(){return fAniMotionTime;};
	inline VOID SetMissileCount(INT count){g_nMissileCount = count;};
//	inline BOOL GetWallOn(){return bWallon;};
	inline INT OnWall(){return nWallPos;};
	inline INT OnWallPosition(){return g_nWallPosition;};
	inline VOID CheckMonster(){
		if(!pMon->IsAlive()){
			if(g_nPase == 0){
				Pase1();
				g_nPase = 1;
			}else{
				Pase2();
			}
			pMon->SetAlive(true);
		}
	}
};
#endif
