#include "Monai.h"

Monai::Monai(Monster* pMonster,Ball* pCharecter,Missile* missile[MISSILE_COUNT],Moving* pMoving,Wall* createwall,Checkai* result,CModel* model,SettingUI* ui,float time){
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
	pUI = ui;
	bDoAction = false;
	for(int i=0;i<MISSILE_COUNT;i++){
		pMsi[i] = missile[i];
	}
	fMotionSpeed = 0.5f;
	g_fNormalAttack = 0;
	bMsion = false;
	bDefon = false;
	//bWallon = false;
	bHealon = false;
	bLaseron = false;
	bRushon = false;
	bNaton = false;
	bMsionAll = false;
	bMsionNext = false;
	g_nMissileCount = MISSILE_INITIAL_COUNT;
	g_nInitDefence = 50;
	g_nInitHealing = 20;
	g_nWallPosition = 0;
	g_nPase = 0;
	g_bChangeThread = FALSE;
	g_bChangePattern = FALSE;

	g_fActionStart = 0;
	g_fNormalAttack = 0;
	g_bNormalAttack = TRUE;

	g_fLaserLength = 1;
	g_fLaserDamage = -20;
	g_fNAttackDamage = -5;
}
Monai::~Monai(){
	pMon = NULL;
	pCha = NULL;
	pMov = NULL;
	pWall = NULL;
	pUI = NULL;
	pCheckResult = NULL;
	for(int i=0;i<MISSILE_COUNT;i++){
		pMsi[i] = NULL;
	}
	pNowAction = NULL;
	pCheckAction = NULL;
	pAniModel = NULL;

}
void Monai::GetPositionMon(float time){	
	//GetMoveType(time);
	if(!g_bChangePattern){
		GetMoveType(time);
	}
	if(!g_bChangeThread){
		Type(pMon->GetmType(),time);
	}else{
		pCheckResult->StartSorting();
		g_bChangeThread = FALSE;
		g_bChangePattern = FALSE;
	}
	/*
	if(!bNaton&&time - g_fNormalAttack>5.0f){
		vLength = pMon->GetPosition()-pCha->GetPosition(); 
		if(D3DXVec3Length(&vLength)<MON_REAL_SIZE+MON_ATTACK_RANGE){
			g_bNormalAttack = FALSE;
		}
		if(!g_bNormalAttack){
			pAniModel->SetCurrentAnimation(0);
			fAniMotionTime = 0.01f;
			g_fNormalAttackStart = time;
			g_bNormalAttack = TRUE;
			bNaton = TRUE;
		}else{
			if(time - g_fNormalAttackStart>2.0f){
				pCha->SetLife(-1);
			}else{
				g_bNormalAttack = FALSE;
				bNaton = FALSE;
			}
		}
	}
	
	*///if(!g_bChangeThread){
	//	Type(pMon->GetmType(),time);
	//}else{
	//	if(g_bChangePattern){
	//		pCheckResult->start();
	//		g_bChangePattern = FALSE;
	//	}else{
	//		if(pCheckResult->NowChange()){
	//			pCheckResult->SetChange(FALSE);
	//			g_bChangeThread = FALSE;
	//		}
	//	}
	//}
}

void Monai::InhenceMove(int type){
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
			if(!bNaton){
				pAniModel->SetCurrentAnimation(9);
			}
			fAniMotionTime = 0.005f;
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
			if(!bNaton){
				pAniModel->SetCurrentAnimation(9);
			}
			fAniMotionTime = 0.02f;
			break;
		case 11:
		case 12:
			pMon->SetmType(2);
			vVelocity = D3DXVECTOR3(0,0,0);
			fActionStart = time;
			pAniModel->SetCurrentAnimation(8);
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
			if(!bNaton){
				pAniModel->SetCurrentAnimation(9);
			}
			fAniMotionTime = 0.01f;
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
			if(!bNaton){
				pAniModel->SetCurrentAnimation(5);
			}
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
			if(time - fActionStart>5.0f){
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

void Monai::DefenceMode(){
	pAniModel->SetCurrentAnimation(7);
	pMon->MonDefence(g_nInitDefence);
	fAniMotionTime = 0.001f;
}
void Monai::LaserMode(){
	g_vec3LaserPosition = pCha->GetPosition();
	pUI->SetLaserUI();
	pAniModel->SetCurrentAnimation(2);
	fAniMotionTime = 0.001f;
}
void Monai::NormalAttMode(){
	pAniModel->SetCurrentAnimation(0);
	fAniMotionTime = 0.001f;
	bNaton = true;
}
void Monai::HealingMode(float time){
	fHealEachDelay = time;
	pAniModel->SetCurrentAnimation(6);
	fAniMotionTime = 0.001f;
}
void Monai::MissileMode(){
	bMsionAll = true;
	for(int i=0;i<g_nMissileCount;i++){pMsi[i]->Start();}
	pAniModel->SetCurrentAnimation(3);
	fAniMotionTime = 0.005f;
}
void Monai::WallMode(){
	pAniModel->SetCurrentAnimation(4);
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
void Monai::MissileModeStart(float time,Pattern* pat){
	pat->SetMissile(false);
	for(int i=0;i<g_nMissileCount;i++){
		pMsi[i]->MoveMissile(pMon,pCha,time);
		if(!pat->GetMissile()&&pMsi[i]->NowStart()){
			pat->SetMissile(true);
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
	D3DXVECTOR3 length = g_vec3LaserPosition - pCha->GetPosition();
	FLOAT M = D3DXVec3LengthSq(&length);
	if(D3DXVec3LengthSq(&length)<(MYSIZE+LASER_SIZE)*(MYSIZE*LASER_SIZE)*g_fLaserLength){
		pUI->DamageUI();
		pCha->SetLife(g_fLaserDamage);
	}
}
void Monai::NormalAttModeStart(){
	vLength = pMon->GetPosition()-pCha->GetPosition(); 
	if(D3DXVec3Length(&vLength)<MON_REAL_SIZE+BALL_REAL_SIZE+MON_ATTACK_RANGE){
		pUI->DamageUI();
		pCha->SetLife(g_fNAttackDamage);
	}
}
bool Monai::Case(Pattern* pattern,float time){
	switch(pattern->GetNowAction()){
	case 0: 
		switch(pattern->GetType()){
		case 0:
			MissileMode();
			pattern->SetMissile(true);
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
		return false;
	case 1:
		if(time - pattern->GetStartPlay() > pattern->GetMotionDelay()){
			g_bChangePattern = FALSE;			
			pattern->SetNowAction(2);
			pMon->SetisGoal(false);
		}
		return false;
	case 2:
		if(pattern->IsPlay(time)){
			switch(pattern->GetType()){
			case 0:
				MissileModeStart(time,pattern);
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
			pattern->SetNowAction(3);
		}
		return false;
	case 3:
		return true;
	}
}
void Monai::Type(int type,float time){
	switch(nTypeCase){
	case 0:
		if(time - g_fActionStart>2.0f){	
			g_bChangePattern = TRUE;
			pMon->SetVelocity(D3DXVECTOR3(0.0f,0.0f,0.0f));
			g_fActionStart = time;
			pCheckAction = pCheckResult->DoAction(type,time);
			pNowAction = pCheckAction;
			g_fCheckChaHP = pCha->HisLife();
			g_fCheckMonHP = pMon->HisLife();
			if(pNowAction->GetNextPat()== NULL){
				nTypeCase = 1;
			}else{
				if(pNowAction->GetNextPat()->GetNextPat() == NULL){
					nTypeCase = 2;
				}else{
					nTypeCase = 3;				
				}
			}
		}
		break;
	case 1:
		if(!Case(pNowAction , time)){
			pNowAction = pNowAction->GetNextPat();
			if(pNowAction == NULL){
				nTypeCase = 5;
			}
		}
		break;
	case 2:
		if(!Case(pNowAction, time) || !Case(pNowAction->GetNextPat(), time)){
		}else{
			nTypeCase = 5;
		}
		break;
	case 3:
		if(!Case(pNowAction, time) || !Case(pNowAction->GetNextPat(), time) || !Case(pNowAction->GetNextPat()->GetNextPat(), time)){
		}else{
			nTypeCase = 5;
		}
		break;
	case 5:
		pCheckAction->UpEffective((g_fCheckChaHP - pCha->HisLife()/5));
		pCheckAction->UpDo((g_fCheckMonHP - pMon->HisLife()/100 + 1));
		SetActionReset(time);
		nTypeCase = 0;
		break;
	}
}

void Monai::SetActionReset(float time){
	pMon->MonDefence(10);
	pWall->ResetPosVel();
	bMsion = false;
	bDefon = false;
	bHealon = false;
	bLaseron = false;
	bRushon = false;
	bNaton = false;
	bMsionAll = false;
	g_nWallPosition = 0;
	g_fActionStart = time;
	RandPositionMon();
	if(pMon->HisLife()<100){
		pMon->SetAlive(false);
		if(g_nPase == 0){
			Pase1();
			g_nPase = 1;
		}else{
			Pase2();
			g_nPase = 2;
		}
		pMon->SetAlive(true);
		g_bChangeThread = TRUE;
	}
}

BOOL Monai::RushMode(float time){
	return TRUE;
}

D3DXVECTOR3 Monai::GetNormal(){
	return vFace;
}

VOID Monai::Pase0(){
	pMon->ResetMonster();
	SetMissileCount(15);
	for(int i=0;i<g_nMissileCount;i++){
		pMsi[i]->SetSpeed(4);
	}
	g_nInitDefence = 50;
	g_nInitHealing = 20;
	g_fLaserLength = 1;
	g_fLaserDamage = -20;
	g_fNAttackDamage = -5;

}
VOID Monai::Pase1(){
	pMon->ResetMonster();
	SetMissileCount(25);
	for(int i=0;i<g_nMissileCount;i++){
		pMsi[i]->SetSpeed(4.5);
	}
	g_nInitDefence = 70;
	g_nInitHealing = 35;
	g_fLaserLength = 1.2;
	g_fLaserDamage = -25;
	g_fNAttackDamage = -10;

}
VOID Monai::Pase2(){
	pMon->ResetMonster();
	SetMissileCount(35);
	for(int i=0;i<g_nMissileCount;i++){
		pMsi[i]->SetSpeed(5);
	}
	g_nInitDefence = 90;
	g_nInitHealing = 50;
	g_fLaserLength = 1.5;
	g_fLaserDamage = -30;
	g_fNAttackDamage = -15;
}
