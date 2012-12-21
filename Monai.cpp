#include "Monai.h"

Monai::Monai(Monster* monster,Ball* charecter,Missile* missile[],Moving* moving,Wall* createwall,Checkai* result,float time){
	firstAction = false;
	secondAction = false;
	actionDelay = false;
	typeCase = 0;
	zero.x = 0.0f;
	zero.y = 0.0f;
	zero.z = 0.0f;
	monSpeed = 0.0f;

	ActionStart = -1.0f;
	mon = monster;
	cha = charecter;
	mov = moving;
	wall = createwall;
	checkResult = result;
	doAction = false;
	for(int i=0;i<10;i++){
		msi[i] = missile[i];
	}
	motionSpeed = 0.5f;
	motionSpeedX = 1.0f;
	motionSpeedY = 1.0f;
	motionSpeedZ = 1.0f;
	motionDelay = false;
	msiStartTime = time; 
	msiEndTime = time; 
	defStartTime = time;
	defEndTime = time;
	wallStartTime = time;
	wallEndTime = time;
	healStartTime = time;
	healEndTime = time;
	healEachDelay = time;
	raserStartTime = time;
	raserEndTime = time;
	rushStartTime = time;
	rushEndTime = time;
	norAttStartTime = time;
	norAttEndTime = time;

	msion = false;
	defon = false;
	wallon = false;
	healon = false;
	raseron = false;
	rushon = false;
	naton = false;
	msionAll = false;
	msionNext = false;
	actionNum = 0;
	nextActionNum = 0;
}
Monai::~Monai(){}
void Monai::getPositionMon(float time){	
	getMoveType(time);
	realType(mon->getmType(),time);
}

void Monai::inhenceMove(int type){
	mon->setisGoal(false);
	if(type<MOVE_PATTERN_COUNT){
		mon->setOriginType(type);
	}else{
		mon->setOriginType(0);
	}
}

void Monai::getMoveType(float time){
	if(!mon->isGoal()){
		motionSpeedY = 1.0f;
		switch(mon->getOriginType()){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			mon->setmType(0);
			mon->setGoal(D3DXVECTOR3((rand()%(int)MAXBOUNDX)-MINBOUNDX,0.0f,(rand()%(int)MAXBOUNDZ)-MINBOUNDZ));
			motionSpeed = 0.2f;
			velocty = mon->getGoal() - mon->getPosition();
			D3DXVec3Normalize(&velocty,&velocty);
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			mon->setmType(1);
			mon->setGoal(D3DXVECTOR3(cha->getPosition().x,0.0f,cha->getPosition().z));
			motionSpeed = 0.5f;
			velocty = mon->getGoal() - mon->getPosition();
			D3DXVec3Normalize(&velocty,&velocty);
			break;
		case 11:
		case 12:
			mon->setmType(2);
			velocty = D3DXVECTOR3(0,0,0);
			ActionStart = time;
			break;
		case 13:
		case 14:
		case 15:
			mon->setmType(3);
			mon->setGoal(cha->getPosition()+D3DXVECTOR3(rand()%10-5,1.0f,rand()%10-5));
			motionSpeed = 0.5f;
			motionSpeedY = 10.0f;
			velocty = mon->getGoal() - mon->getPosition();
			D3DXVec3Normalize(&velocty,&velocty);
			break;
		case 16:
		case 17:
		case 18:
		case 19:
			mon->setmType(4);
			mon->setGoal(D3DXVECTOR3((rand()%(int)MAXBOUNDX)-MINBOUNDX,0.0f,(rand()%(int)MAXBOUNDZ)-MINBOUNDZ));
			motionSpeed = 0.5f;
			velocty = mon->getGoal() - mon->getPosition();
			D3DXVec3Normalize(&velocty,&velocty);
			break;
		}
		velocty.y *= motionSpeedY;
		mon->setVelocity(velocty*GAMESPEED*motionSpeed);
		mon->setRotate(velocty);
		mon->setisGoal(true);
	}
	else{
		switch (mon->getmType()){
		case 2:
			if(time - ActionStart>3.0f){
				mon->setisGoal(false);
				randPositionMon();
			}
			break;
		default:
			if	( abs(mon->getPosition().x-mon->getGoal().x)< (MON_REAL_SIZE/2)*(MON_REAL_SIZE/2) ){
				mon->setVelocityX(0.0f);
				mon->setVelocityY(0.0f);
				mon->setVelocityZ(0.0f);

				mon->setisGoal(false);
				randPositionMon();
			}
			break;
		}
	}
}
void Monai::stopMove(float time){
	if(!doAction){
		ActionStart = time;
		doAction = true;
	}
	if(doAction){
		if(time-ActionStart>5.0f){
			randPositionMon();
			doAction = false;
		}
	}
}
void Monai::defenceMode(float time){
	mon->monDefence(100);
}
void Monai::laserMode(float time){}
void Monai::normalAttMode(float time){}
void Monai::healingMode(float time){
	healEachDelay = time;
}
void Monai::missileMode(float time){
	msionAll = true;
	msionNext = true;
	for(int i=0;i<10;i++){msi[i]->start();}
}
void Monai::wallMode(float time){
	wallPos = rand()%2;
	if(wallPos){
		wallPos = cha->getPosition().x;
	}
	else{
		wallPos = cha->getPosition().z;
	}
	mov->setMonWall(true);
}
void Monai::defenceModeStart(){
}
void Monai::missileModeStart(float time){
	msionAll = false;
	msionNext = false;
	for(int i=0;i<10;i++){
		msi[i]->moveMissile(mon,cha,time);
		if(!msionAll&&msi[i]->nowStart()){
			msionAll = true;
			msionNext = true;
		}
	}

}
void Monai::wallModeStart(){
	if(wallPos){
		mov->getPositionWall(D3DXVECTOR3(wallPos,0,0),GAMESPEED);//x
	}
	else{
		mov->getPositionWall(D3DXVECTOR3(0,0,wallPos),GAMESPEED);//z
	}

}
void Monai::healingModeStart(float time){
	if(time - healEachDelay > 1){
		healEachDelay = time;
		mon->monHealing();
	}

}
void Monai::laserModeStart(){
}
void Monai::normalAttModeStart(){
	mLength = mon->getPosition()-cha->getPosition(); 
	if(D3DXVec3Length(&mLength)<MON_REAL_SIZE+BALL_REAL_SIZE+MON_ATTACK_RANGE){
		cha->setLife(-10);
	}
}

void Monai::realMixType(int type,float time){
	switch(typeCase){
	case 0:
		nowAction = checkResult->doAction(type,time);
		nextAction = nowAction->getNextPat();
		actionNum = nowAction->getType();
		motiontime = time;
		typeCase = 1;
		break;
	case 1:
		if(time - motiontime > nowAction->getMotionDelay()){
			switch(actionNum){
			case 0:
				missileMode(time);
				break;
			case 1:
				healingMode(time);
				break;
			case 2:
				defenceMode(time);
				break;
			case 3:
				laserMode(time);
				break;
			case 4:
				normalAttMode(time);
				break;
			case 5:
				wallMode(time);
				break;
			}
			nowAction->startPlay(time);
			typeCase = 2;
		}
		break;
	case 2:
		if(nextAction != NULL){
			nextActionNum = nextAction->getType();
			switch(nextActionNum){
			case 0:
				missileMode(time);
				break;
			case 1:
				healingMode(time);
				break;
			case 2:
				defenceMode(time);
				break;
			case 3:
				laserMode(time);
				break;
			case 4:
				normalAttMode(time);
				break;
			case 5:
				wallMode(time);
				break;
			}
			nextAction->startPlay(time);
			typeCase = 3;
		}
		else{
			typeCase = 4;
		}
		break;
	case 3:
		if(msionAll || nowAction->isPlay(time)){
			switch(actionNum){
			case 0:
				missileModeStart(time);
				break;
			case 1:
				healingModeStart(time);
				break;
			case 2:
				defenceModeStart();
				break;
			case 3:
				laserModeStart();
				break;
			case 4:
				normalAttModeStart();
				break;
			case 5:
				wallModeStart();
				break;
			}
		}else{
			nowAction->endPlay(time);
		}
		if(msionNext||nextAction->isPlay(time)){
			switch(nextActionNum){
			case 0:
				missileModeStart(time);
				break;
			case 1:
				healingModeStart(time);
				break;
			case 2:
				defenceModeStart();
				break;
			case 3:
				laserModeStart();
				break;
			case 4:
				normalAttModeStart();
				break;
			case 5:
				wallModeStart();
				break;
			}
		}else{
			nextAction->endPlay(time);
		}
		if(!msionNext&&!nextAction->isPlay(time)&&!msionAll&&!nowAction->isPlay(time)){
			typeCase = 5;
		}
		break;
	case 4:
		if(msionAll || nowAction->isPlay(time)){
			switch(actionNum){
			case 0:
				missileModeStart(time);
				break;
			case 1:
				healingModeStart(time);
				break;
			case 2:
				defenceModeStart();
				break;
			case 3:
				laserModeStart();
				break;
			case 4:
				normalAttModeStart();
				break;
			case 5:
				wallModeStart();
				break;
			}
		}
		else{
			nowAction->endPlay(time);
			typeCase = 5;
		}
		break;
	case 5:
		setActionReset();
		break;
	}
}

void Monai::realType(int type,float time){
	switch(typeCase){
	case 0:
		nowAction = checkResult->doAction(type,time);
		nextAction = nowAction->getNextPat();
		motiontime = time;
		actionNum = CHANGE_ACTION_NUM;
		typeCase = 1;
		break;
	case 1:
		typeCase = 2;
		actionNum = nowAction->getType();
		break;
	case 2:
		if(time - motiontime > nowAction->getMotionDelay()){
			nowAction->startPlay(time);
			switch(actionNum){
			case 0:
				missileMode(time);
				break;
			case 1:
				healingMode(time);
				break;
			case 2:
				defenceMode(time);
				break;
			case 3:
				laserMode(time);
				break;
			case 4:
				normalAttMode(time);
				break;
			case 5:
				wallMode(time);
				break;
			}
			typeCase = 3;
		}
		break;
	case 3:
		if(msionAll || nowAction->isPlay(time)){
			switch(actionNum){
			case 0:
				missileModeStart(time);
				break;
			case 1:
				healingModeStart(time);
				break;
			case 2:
				defenceModeStart();
				break;
			case 3:
				laserModeStart();
				break;
			case 4:
				normalAttModeStart();
				break;
			case 5:
				wallModeStart();
				break;
			}
		}
		else{
			typeCase = 4;
		}
		break;
	case 4:
		if(nextAction != NULL){
			nextActionNum = nextAction->getType();
			switch(nextActionNum){
			case 0:
				missileMode(time);
				break;
			case 1:
				healingMode(time);
				break;
			case 2:
				defenceMode(time);
				break;
			case 3:
				laserMode(time);
				break;
			case 4:
				normalAttMode(time);
				break;
			case 5:
				wallMode(time);
				break;
			}
			nowAction->endPlay(time);
			nextAction->startPlay(time);
			typeCase = 5;
		}
		else{		
			nowAction->endPlay(time);
			typeCase = 6;
		}
		break;
	case 5:
		if(msion||nextAction->isPlay(time)){
			switch(nextActionNum){
			case 0:
				missileModeStart(time);
				break;
			case 1:
				healingModeStart(time);
				break;
			case 2:
				defenceModeStart();
				break;
			case 3:
				laserModeStart();
				break;
			case 4:
				normalAttModeStart();
				break;
			case 5:
				wallModeStart();
				break;
			}
		}
		else{
			nextAction->endPlay(time);
			typeCase = 6;
		}
		break;
	case 6:
		setActionReset();
		break;
	}
}
void Monai::setActionReset(){
	mon->monDefence(10);
	if(actionNum == 5||nextActionNum == 5){
		mov->returnWall();
	}
	nextActionNum = 0;
	typeCase = 0;
}


bool Monai::rushMode(float time){
	if((rushon == false)&&(time-rushEndTime-RUSH_END_DELAY>0)){
		rushStartTime = time;
		rushon = true;
	}
	if(rushon == true){
		if(time - rushStartTime < RUSH_START_DELAY){
			//		for(int i=0;i<10;i++){
			//			msi[i]->moveMissile(mon,cha,time);
			//		}
			return true;
		}
		else{
			rushon = false;
			rushEndTime = time;
			return false;
		}
	}
	return false;

}

D3DXVECTOR3 Monai::getNormal(){
	return face;
}
float Monai::getRotation(){
	return rotate;
}
bool Monai::canDef(float time){
	if(defEndTime+DEF_END_DELAY<time){return true;}
	return false;
}
bool Monai::canMissile(float time){
	if(msiEndTime+MSI_END_DELAY<time){return true;}
	return false;
}
bool Monai::canHealing(float time){
	if(healEndTime+HEAL_END_DELAY<time){return true;}
	return false;
}
bool Monai::canRaser(float time){
	if(raserEndTime+LASER_END_DELAY<time){return true;}
	return false;
}
bool Monai::canRush(float time){
	if(rushEndTime+RUSH_END_DELAY<time){return true;}
	return false;
}
bool Monai::canNorAtt(float time){
	if(norAttEndTime+NATT_END_DELAY<time){return true;}
	return false;
}

void Monai::checkChangePattern(){
	
}