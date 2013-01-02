#include "Monai.h"

Monai::Monai(Monster* pMonster,Ball* pCharecter,Missile* missile[MISSILE_COUNT],Moving* pMoving,Wall* createwall,Checkai* result,CModel* model,float time){
	nTypeCase = 0;
	vZero = D3DXVECTOR3(0.0f,0.0f,0.0f);
	vZline = D3DXVECTOR3(0.0f,0.0f,1.0f);
	vFace = D3DXVECTOR3(0.0f,0.0f,0.0f);
	fMonSpeed = 0.0f;
	
	fAniMotionTime = 0.02f;
	nWallPos = 0;
	fActionStart = -1.0f;
	pMon = pMonster;
	pCha = pCharecter;
	pMov = pMoving;
	pWall = createwall;
	pCheckResult = result;
	pAniModel = model;
	bDoAction = false;
	for(int i=0;i<MISSILE_COUNT;i++){
		pMsi[i] = missile[i];
	}
	fMotionSpeed = 0.5f;
	
	bMsion = false;
	bDefon = false;
	//bWallon = false;
	bHealon = false;
	bRaseron = false;
	bRushon = false;
	bNaton = false;
	bMsionAll = false;
	bMsionNext = false;
	g_nMissileCount = MISSILE_INITIAL_COUNT;
	g_nInitDefence = 50;
	g_nInitHealing = 20;
	g_nWallPosition = 0;
	g_nPase = 0;
}
Monai::~Monai(){

	pMon = NULL;
	pCha = NULL;
	pMov = NULL;
	pWall = NULL;
	pCheckResult = NULL;
	for(int i=0;i<MISSILE_COUNT;i++){
		pMsi[i] = NULL;
	}
	pNowAction = NULL;
	pCheckAction = NULL;
	pAniModel = NULL;

}
void Monai::GetPositionMon(float time){	
	CheckMonster();
	GetMoveType(time);
	Type(pMon->GetmType(),time);
}

void Monai::InhenceMove(int type){
	pMon->SetisGoal(false);
	if(type<MOVE_PATTERN_COUNT){
		pMon->SetOriginType(type);
	}else{
		pMon->SetOriginType(0);
	}
}

void Monai::GetMoveType(float time){
	if(!pMon->IsGoal()){
		switch(pMon->GetOriginType()){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			pMon->SetmType(0);
			pMon->SetGoal(D3DXVECTOR3((rand()%(int)MAXBOUNDX)-MINBOUNDX,0.0f,(rand()%(int)MAXBOUNDZ)-MINBOUNDZ));
			fMotionSpeed = 0.2f;
			vVelocity = pMon->GetGoal() - pMon->GetPosition();
			D3DXVec3Normalize(&vVelocity,&vVelocity);
			pAniModel->SetCurrentAnimation(9);
			fAniMotionTime = 0.01f;
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			pMon->SetmType(1);
			pMon->SetGoal(D3DXVECTOR3(pCha->GetPosition().x,0.0f,pCha->GetPosition().z));
			fMotionSpeed = 0.5f;
			vVelocity = pMon->GetGoal() - pMon->GetPosition();
			D3DXVec3Normalize(&vVelocity,&vVelocity);
			pAniModel->SetCurrentAnimation(9);
			fAniMotionTime = 0.02f;
			break;
		case 11:
		case 12:
			pMon->SetmType(2);
			vVelocity = D3DXVECTOR3(0,0,0);
			fActionStart = time;
			pAniModel->SetCurrentAnimation(6);
			fAniMotionTime = 0.001f;
			break;
		case 13:
		case 14:
		case 15:
			pMon->SetmType(3);
			pMon->SetGoal(pCha->GetPosition()+D3DXVECTOR3(rand()%10-5,1.0f,rand()%10-5));
			fMotionSpeed = 0.5f;
			vVelocity = pMon->GetGoal() - pMon->GetPosition();
			D3DXVec3Normalize(&vVelocity,&vVelocity);
			pAniModel->SetCurrentAnimation(7);
			fAniMotionTime = 0.0001f;
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			pMon->SetmType(4);
			pMon->SetGoal(D3DXVECTOR3((rand()%(int)MAXBOUNDX)-MINBOUNDX,0.0f,(rand()%(int)MAXBOUNDZ)-MINBOUNDZ));
			fMotionSpeed = 0.5f;
			vVelocity = pMon->GetGoal() - pMon->GetPosition();
			D3DXVec3Normalize(&vVelocity,&vVelocity);
			pAniModel->SetCurrentAnimation(8);
			fAniMotionTime = 0.001f;			
			break;
		}
		if(bNaton){
			pAniModel->SetCurrentAnimation(1);
		}
		pMon->SetVelocity(vVelocity*GAMESPEED*fMotionSpeed);
		pMon->SetisGoal(true);
	}
	else{
		switch (pMon->GetmType()){
		case 2:
			if(time - fActionStart>3.0f){
				pMon->SetisGoal(false);
				RandPositionMon();
			}
			break;
		default:
			if	( abs(pMon->GetPosition().x-pMon->GetGoal().x)< (MON_REAL_SIZE/2)*(MON_REAL_SIZE/2) ){
				pMon->SetVelocityX(0.0f);
				pMon->SetVelocityY(0.0f);
				pMon->SetVelocityZ(0.0f);
				pMon->SetisGoal(false);
				RandPositionMon();
			}
			break;
		}
	}
}
void Monai::StopMove(float time){
	if(!bDoAction){
		fActionStart = time;
		bDoAction = true;
	}
	if(bDoAction){
		if(time-fActionStart>5.0f){
			RandPositionMon();
			bDoAction = false;
		}
	}
}


void Monai::DefenceMode(){
	pAniModel->SetCurrentAnimation(5);
	pMon->MonDefence(g_nInitDefence);
	fAniMotionTime = 0.001f;
}
void Monai::LaserMode(){}
void Monai::NormalAttMode(){
	pAniModel->SetCurrentAnimation(1);
	fAniMotionTime = 0.001f;
	bNaton = true;
}
void Monai::HealingMode(float time){
	fHealEachDelay = time;
	pAniModel->SetCurrentAnimation(2);
	fAniMotionTime = 0.001f;
}
void Monai::MissileMode(){
	bMsionAll = true;
	bMsionNext = true;
	for(int i=0;i<g_nMissileCount;i++){pMsi[i]->Start();}
	pAniModel->SetCurrentAnimation(4);
	fAniMotionTime = 0.005f;
}
void Monai::WallMode(){
	pAniModel->SetCurrentAnimation(3);
	nWallPos = rand()%2;
	if(nWallPos){
		nWallPos = pCha->GetPosition().x;
		if(pCha->GetPosition().x>nWallPos){
			g_nWallPosition = 1;
		}
		else{
			g_nWallPosition = 2;
		}
	}
	else{
		nWallPos = pCha->GetPosition().z;
		if(pCha->GetPosition().z>nWallPos){
			g_nWallPosition = 3;
		}
		else{
			g_nWallPosition = 4;
		}
	}
	fAniMotionTime = 0.001f;
}

void Monai::DefenceModeStart(){
	pAniModel->SetCurrentAnimation(5);
	fAniMotionTime = 0.001f;
}
void Monai::MissileModeStart(float time){
	bMsionAll = false;
	bMsionNext = false;
	for(int i=0;i<g_nMissileCount;i++){
		pMsi[i]->MoveMissile(pMon,pCha,time);
		if(!bMsionAll&&pMsi[i]->NowStart()){
			bMsionAll = true;
			bMsionNext = true;
		}
	}

}
void Monai::WallModeStart(){

}
void Monai::HealingModeStart(float time){
	if(time - fHealEachDelay > 1){
		fHealEachDelay = time;
		pMon->MonHealing(g_nInitHealing);
	}
}
void Monai::LaserModeStart(){
}
void Monai::NormalAttModeStart(){
	vLength = pMon->GetPosition()-pCha->GetPosition(); 
	if(D3DXVec3Length(&vLength)<MON_REAL_SIZE+BALL_REAL_SIZE+MON_ATTACK_RANGE){
		pCha->SetLife(-10);
	}
}
void Monai::Case(Pattern* pattern,float time){
	switch(pattern->GetNowAction()){
	case 0:
		switch(pattern->GetType()){
		case 0:
			MissileMode();
			break;
		case 1:
			HealingMode(time);
			break;
		case 2:
			DefenceMode();
			break;
		case 3:
			LaserMode();
			break;
		case 4:
			NormalAttMode();
			break;
		case 5:
			WallMode();
			break;
		}
		pattern->SetNowAction(1);
		pattern->StartPlay(time);
		break;
	case 1:
		if(bMsionAll || pattern->IsPlay(time)){
			switch(pattern->GetType()){
			case 0:
				MissileModeStart(time);
				break;
			case 1:
				HealingModeStart(time);
				break;
			case 2:
				DefenceModeStart();
				break;
			case 3:
				LaserModeStart();
				break;
			case 4:
				NormalAttModeStart();
				break;
			case 5:
				WallModeStart();
				break;
			}
		}
		else{
			pattern->EndPlay(time);
			pattern->SetNowAction(0);
			nTypeCase = 2;
		}
		break;
	}
}
void Monai::Type(int type,float time){
	switch(nTypeCase){
	case 0:
		pCheckAction = pCheckResult->DoAction(type,time);
		pNowAction = pCheckAction;
		g_fCheckChaHP = pCha->HisLife();
		g_fCheckMonHP = pMon->HisLife();
		nTypeCase = 1;
		break;
	case 1:
		Case(pNowAction, time);
		break;
	case 2:
		pNowAction = pNowAction->GetNextPat();
		if(pNowAction != NULL){
		nTypeCase = 1;
		}
		else{
			nTypeCase = 3;
		}
		break;
	case 3:
		pCheckAction->UpDo(1);
		pCheckAction->UpEffective((g_fCheckChaHP - pCha->HisLife()/5));
		pCheckAction->UpDo((g_fCheckMonHP - pMon->HisLife()/100));
		SetActionReset();
		nTypeCase = 0;
		break;
	}
}

void Monai::SetActionReset(){
	pMon->MonDefence(10);
	pWall->ResetPosVel();
	bMsion = false;
	bDefon = false;
	bHealon = false;
	bRaseron = false;
	bRushon = false;
	bNaton = false;
	g_nWallPosition = 0;
}


BOOL Monai::RushMode(float time){
	return TRUE;
}

D3DXVECTOR3 Monai::GetNormal(){
	return vFace;
}

VOID Monai::Pase0(){
	SetMissileCount(15);
	for(int i=0;i<g_nMissileCount;i++){
		pMsi[i]->SetSpeed(4);
	}
	g_nInitDefence = 50;
	g_nInitHealing = 20;
}
VOID Monai::Pase1(){
	SetMissileCount(25);
	for(int i=0;i<g_nMissileCount;i++){
		pMsi[i]->SetSpeed(4.5);
	}
	g_nInitDefence = 70;
	g_nInitHealing = 35;
}
VOID Monai::Pase2(){
	SetMissileCount(35);
	for(int i=0;i<g_nMissileCount;i++){
		pMsi[i]->SetSpeed(5);
	}
	g_nInitDefence = 90;
	g_nInitHealing = 50;
}
