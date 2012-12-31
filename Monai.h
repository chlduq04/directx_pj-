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
	float fAniMotionTime;
	int nTypeCase;
	bool bFirstAction;
	bool bSecondAction;
	int nActionNum; 
	int nNextActionNum;
	int nMotionNum;
	float fMotiontime;
	bool bActionDelay;
	D3DXVECTOR3 vLength;
	bool bMotionDelay;
	D3DXVECTOR3 vVelocity;
	D3DXVECTOR3 vFace;
	D3DXVECTOR3 vZero;
	float fRotate;
	float fMotionSpeed;
	float fMotionSpeedX;
	float fMotionSpeedY;
	float fMotionSpeedZ;

	int nMaxBoundx;
	int nMaxBoundy;
	int nMaxBoundz;
	int nMinBoundx;
	int nMinBoundy;
	int nMinBoundz;

	float fActionStart;
	Monster* pMon;
	Ball* pCha;
	Moving* pMov;
	Wall* pWall;
	Checkai* pCheckResult;
	Missile* pMsi[MISSILE_COUNT];
	Pattern* pNowAction;
	Pattern* pNextAction;
	CModel* pAniModel;
	float fSpeed;
	float fMonsize;
	float fMonSpeed;
	int nWallPos;

	bool bDoAction;

	float fDefStartTime; //선5sec
	float fDefEndTime; //후15sec
	bool bDefon;
	float fWallStartTime; //선10sec
	float fWallEndTime; //후25sec
	bool bWallon;	
	float fHealStartTime; //선5sec
	float fHealEndTime; //후15sec
	float fHealEachDelay;
	bool bHealon;	
	float fRaserStartTime; //선5sec
	float fRaserEndTime; //후30sec
	bool bRaseron;
	float fRushStartTime; //선5sec
	float fRushEndTime; //후10sec
	bool bRushon;
	float fMsiStartTime; 
	float fMsiEndTime; 
	bool bMsion;
	bool bMsionAll;
	bool bMsionNext;
	float fNorAttStartTime; 
	float fNorAttEndTime; 
	bool bNaton;


public:
	Monai(Monster* monster,Ball* charecter,Missile* missile[MISSILE_COUNT],Moving* moving,Wall* createwall,Checkai* result,CModel* model,float time);
	~Monai();

	void Pase0(float time);
	void Pase1(float time);
	void Pase2(float time);

	inline int GetActionNum(){return nActionNum;};
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

	bool RushMode(float time);
	bool CanDef(float time);
	bool CanMissile(float time);
	bool CanHealing(float time);
	bool CanRaser(float time);
	bool CanRush(float time);
	bool CanNorAtt(float time);
	void GetPositionMon(float time);
	void NormalMove(float time);
	void ClosetoMove(float time);
	void StopMove(float time);
	void JumpMove(float time);
	void DodgeMove(float time);
	void RealType(int type,float time);
	void RealMixType(int type,float time);
	inline void RandPositionMon(){pMon->SetOriginType(rand()%20);};
	inline void SetPositionMon(int type){pMon->SetOriginType(type);};
	inline int GetRandType(){return rand()%5;};
	inline bool GetMsionall(){return bMsionAll;};

	void CheckChangePattern();
	D3DXVECTOR3 GetNormal();
	float GetRotation();
	void GetMoveType(float time);
	inline void InhenceMove(int type);
	void SetActionReset();

	inline float GetMotionTime(){return fAniMotionTime;};
};
#endif
