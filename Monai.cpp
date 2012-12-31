#include "Monai.h"

Monai::Monai(Monster* pMonster,Ball* pCharecter,Missile* missile[MISSILE_COUNT],Moving* pMoving,Wall* createwall,Checkai* result,CModel* model,float time){
	bFirstAction = false;
	bSecondAction = false;
	bActionDelay = false;
	nTypeCase = 0;
	vZero = D3DXVECTOR3(0.0f,0.0f,0.0f);
	fMonSpeed = 0.0f;
	
	fAniMotionTime = 0.02f;

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
	fMotionSpeedX = 1.0f;
	fMotionSpeedY = 1.0f;
	fMotionSpeedZ = 1.0f;
	bMotionDelay = false;
	fMsiStartTime = time; 
	fMsiEndTime = time; 
	fDefStartTime = time;
	fDefEndTime = time;
	fWallStartTime = time;
	fWallEndTime = time;
	fHealStartTime = time;
	fHealEndTime = time;
	fHealEachDelay = time;
	fRaserStartTime = time;
	fRaserEndTime = time;
	fRushStartTime = time;
	fRushEndTime = time;
	fNorAttStartTime = time;
	fNorAttEndTime = time;

	bMsion = false;
	bDefon = false;
	bWallon = false;
	bHealon = false;
	bRaseron = false;
	bRushon = false;
	bNaton = false;
	bMsionAll = false;
	bMsionNext = false;
	nActionNum = 0;
	nNextActionNum = 0;
}
Monai::~Monai(){}
void Monai::GetPositionMon(float time){	
	GetMoveType(time);
	RealType(pMon->GetmType(),time);
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
		fMotionSpeedY = 1.0f;
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
			fMotionSpeedY = 10.0f;
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
		vVelocity.y *= fMotionSpeedY;
		pMon->SetVelocity(vVelocity*GAMESPEED*fMotionSpeed);
		pMon->SetRotate(vVelocity);
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
	pMon->MonDefence(100);
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
	for(int i=0;i<MISSILE_COUNT;i++){pMsi[i]->Start();}
	pAniModel->SetCurrentAnimation(4);
	fAniMotionTime = 0.005f;
}
void Monai::WallMode(){
	nWallPos = rand()%2;
	if(nWallPos){
		nWallPos = pCha->GetPosition().x;
	}
	else{
		nWallPos = pCha->GetPosition().z;
	}
	pAniModel->SetCurrentAnimation(3);
	pMov->SetMonWall(true);
	fAniMotionTime = 0.001f;
}
void Monai::DefenceModeStart(){
	pAniModel->SetCurrentAnimation(5);
	fAniMotionTime = 0.001f;
}
void Monai::MissileModeStart(float time){
	bMsionAll = false;
	bMsionNext = false;
	for(int i=0;i<MISSILE_COUNT;i++){
		pMsi[i]->MoveMissile(pMon,pCha,time);
		if(!bMsionAll&&pMsi[i]->NowStart()){
			bMsionAll = true;
			bMsionNext = true;
		}
	}

}
void Monai::WallModeStart(){
	if(nWallPos){
		pMov->GetPositionWall(D3DXVECTOR3(nWallPos,0,0),GAMESPEED);//x
	}
	else{
		pMov->GetPositionWall(D3DXVECTOR3(0,0,nWallPos),GAMESPEED);//z
	}

	if( !pWall->IsGround() )
	{
		pWall->SetPosition(pWall->GetPosition()+pWall->GetVelocity()*BALLSPEED);
		if(pWall->GetVelocity().y>0)
			pWall->SetVelocityY(pWall->GetVelocity().y-(GRAVITY+REVERSE_GRAVITY)*BALLSPEED*15.0f);
		else
			pWall->SetVelocityY(pWall->GetVelocity().y-(GRAVITY*BALLSPEED)*5.0f);

		if( pWall->GetPosition().y < -GROUND)
		{
			if(pWall->GetBcount()>7){
				pWall->IsGround(true);
			}else{
				pWall->SetPositionY(-GROUND );
				pWall->SetVelocityY(-pWall->GetVelocity().y* ( 1 - ABSORBANCE*20 ));
				pWall->SetBcount();
			}

		}
	}
}
void Monai::HealingModeStart(float time){
	if(time - fHealEachDelay > 1){
		fHealEachDelay = time;
		pMon->MonHealing();
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

void Monai::RealMixType(int type,float time){
	switch(nTypeCase){
	case 0:
		pNowAction = pCheckResult->DoAction(type,time);
		pNextAction = pNowAction->GetNextPat();
		nActionNum = pNowAction->GetType();
		fMotiontime = time;
		nTypeCase = 1;
		break;
	case 1:
		if(time - fMotiontime > pNowAction->GetMotionDelay()){
			switch(nActionNum){
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
			pNowAction->StartPlay(time);
			nTypeCase = 2;
		}
		break;
	case 2:
		if(pNextAction != NULL){
			nNextActionNum = pNextAction->GetType();
			switch(nNextActionNum){
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
			pNextAction->StartPlay(time);
			nTypeCase = 3;
		}
		else{
			nTypeCase = 4;
		}
		break;
	case 3:
		if(bMsionAll || pNowAction->IsPlay(time)){
			switch(nActionNum){
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
		}else{
			pNowAction->EndPlay(time);
		}
		if(bMsionNext||pNextAction->IsPlay(time)){
			switch(nNextActionNum){
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
		}else{
			pNextAction->EndPlay(time);
		}
		if(!bMsionNext&&!pNextAction->IsPlay(time)&&!bMsionAll&&!pNowAction->IsPlay(time)){
			nTypeCase = 5;
		}
		break;
	case 4:
		if(bMsionAll || pNowAction->IsPlay(time)){
			switch(nActionNum){
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
			pNowAction->EndPlay(time);
			nTypeCase = 5;
		}
		break;
	case 5:
		SetActionReset();
		break;
	}
}

void Monai::RealType(int type,float time){
	switch(nTypeCase){
	case 0:
		pNowAction = pCheckResult->DoAction(type,time);
		pNextAction = pNowAction->GetNextPat();
		fMotiontime = time;
		nActionNum = CHANGE_ACTION_NUM;
		nTypeCase = 1;
		break;
	case 1:
		nTypeCase = 2;
		nActionNum = pNowAction->GetType();
		break;
	case 2:
		if(time - fMotiontime > pNowAction->GetMotionDelay()){
			pNowAction->StartPlay(time);
			switch(nActionNum){
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
			nTypeCase = 3;
		}
		break;
	case 3:
		if(bMsionAll || pNowAction->IsPlay(time)){
			switch(nActionNum){
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
			nTypeCase = 4;
		}
		break;
	case 4:
		if(pNextAction != NULL){
			nNextActionNum = pNextAction->GetType();
			switch(nNextActionNum){
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
			pNowAction->EndPlay(time);
			pNextAction->StartPlay(time);
			nTypeCase = 5;
		}
		else{		
			pNowAction->EndPlay(time);
			nTypeCase = 6;
		}
		break;
	case 5:
		if(bMsion||pNextAction->IsPlay(time)){
			switch(nNextActionNum){
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
			pNextAction->EndPlay(time);
			nTypeCase = 6;
		}
		break;
	case 6:
		SetActionReset();
		break;
	}
}
void Monai::SetActionReset(){
	pMon->MonDefence(10);
	if(nActionNum == 5||nNextActionNum == 5){
		pMov->ReturnWall();
		pWall->ResetPosVel();
	}
	bMsion = false;
	bDefon = false;
	bWallon = false;
	bHealon = false;
	bRaseron = false;
	bRushon = false;
	bNaton = false;
	nNextActionNum = 0;
	nTypeCase = 0;
}


bool Monai::RushMode(float time){
	if((bRushon == false)&&(time-fRushEndTime-RUSH_END_DELAY>0)){
		fRushStartTime = time;
		bRushon = true;
	}
	if(bRushon == true){
		if(time - fRushStartTime < RUSH_START_DELAY){
			//		for(int i=0;i<10;i++){
			//			pMsi[i]->pMoveMissile(pMon,pCha,time);
			//		}
			return true;
		}
		else{
			bRushon = false;
			fRushEndTime = time;
			return false;
		}
	}
	return false;

}

D3DXVECTOR3 Monai::GetNormal(){
	return vFace;
}
float Monai::GetRotation(){
	return fRotate;
}
bool Monai::CanDef(float time){
	if(fDefEndTime+DEF_END_DELAY<time){return true;}
	return false;
}
bool Monai::CanMissile(float time){
	if(fMsiEndTime+MSI_END_DELAY<time){return true;}
	return false;
}
bool Monai::CanHealing(float time){
	if(fHealEndTime+HEAL_END_DELAY<time){return true;}
	return false;
}
bool Monai::CanRaser(float time){
	if(fRaserEndTime+LASER_END_DELAY<time){return true;}
	return false;
}
bool Monai::CanRush(float time){
	if(fRushEndTime+RUSH_END_DELAY<time){return true;}
	return false;
}
bool Monai::CanNorAtt(float time){
	if(fNorAttEndTime+NATT_END_DELAY<time){return true;}
	return false;
}

void Monai::CheckChangePattern(){
	
}