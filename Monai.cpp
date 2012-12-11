#include "Monai.h"

Monai::Monai(Monster* monster,Ball* charecter,Missile* missile[],Moving* moving,float time){
	zero.x = 0.0f;
	zero.y = 0.0f;
	zero.z = 0.0f;
	monSpeed = 0.0f;
	ActionStart = -1.0f;
	mon = monster;
	cha = charecter;
	mov = moving;

	for(int i=0;i<10;i++){
		msi[i] = missile[i];
	}

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

}
Monai::~Monai(){}
void Monai::getPositionMon(float time){	
	switch(mon->getmType()){
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		normalMove(time);
		//subAction(time);
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		closetoMove(time);
		bxreak;
	case 15:
	case 16:
	case 17:
		stopMove(time);
		break;
	case 18:
	case 19:
	case 20:
		jumpMove(time);
		break;
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
		dodgeMove(time);
		break;
	default:
		break;
	}
}
void Monai::closetoMove(float time){
	if(!mon->isGoal()){
		mon->setGoalX(cha->getPosition().x);
		mon->setGoalY(1.0f);
		mon->setGoalZ(cha->getPosition().z);
		mon->setVelocity((mon->getGoal()-mon->getPosition())/200*GAMESPEED);
	}else{
		mon->setPostion(mon->getPosition()+mon->getVelocity());
		if( abs(mon->getPosition().x-mon->getGoal().x)< (MON_REAL_SIZE/2)*(MON_REAL_SIZE/2) ){
			mon->setVelocityX(0.0f);
			mon->setVelocityY(0.0f);
			mon->setVelocityZ(0.0f);
			mon->setisGoal(false);
			randPositionMon(time);
		}
	}
}
void Monai::normalMove(float time){
	if(!mon->isGoal()){
		mon->setGoalX((rand()%(int)MAXBOUNDX)-MINBOUNDX);
		mon->setGoalY(1.0f);
		mon->setGoalZ((rand()%(int)MAXBOUNDZ)-MINBOUNDZ);
		mon->setVelocity((mon->getGoal()-mon->getPosition())/400*GAMESPEED);
		mon->setisGoal(true);

//		D3DXVec3Normalize(&face,&mon->getGoal());
//		rotate = D3DXVec3Dot(&zero,&mon->getGoal());
	}else{
		mon->setPostion(mon->getPosition()+mon->getVelocity());
		if( abs(mon->getPosition().x-mon->getGoal().x)< (MON_REAL_SIZE/2)*(MON_REAL_SIZE/2) ){
			mon->setVelocityX(0.0f);
			mon->setVelocityY(0.0f);
			mon->setVelocityZ(0.0f);
			mon->setisGoal(false);
			randPositionMon(time);
		}
		if(mon->getPosition().x>MAXBOUNDX) mon->setPostionX(MAXBOUNDX);
		if(mon->getPosition().x<MINBOUNDX) mon->setPostionX(MINBOUNDX);
		if(mon->getPosition().y>MAXBOUNDY) mon->setPostionY(MAXBOUNDY);
		if(mon->getPosition().y<MINBOUNDY) mon->setPostionY(MINBOUNDY);
		if(mon->getPosition().z>MAXBOUNDZ) mon->setPostionZ(MAXBOUNDZ);
		if(mon->getPosition().z<MINBOUNDZ) mon->setPostionZ(MINBOUNDZ);
	}
}
void Monai::jumpMove(float time){
	//delayed
	randPositionMon(time);
}
void Monai::dodgeMove(float time){
	if(!mon->isGoal()){
		mon->setGoalX((rand()%(int)MAXBOUNDX)-MINBOUNDX);
		mon->setGoalY(1.0f);
		mon->setGoalZ((rand()%(int)MAXBOUNDZ)-MINBOUNDZ);
		mon->setVelocity((mon->getGoal()-mon->getPosition())/100*GAMESPEED);
		mon->setisGoal(true);

//		D3DXVec3Normalize(&face,&mon->getGoal());
//		rotate = D3DXVec3Dot(&zero,&mon->getGoal());
	}else{
		mon->setPostion(mon->getPosition()+mon->getVelocity());
		if( abs(mon->getPosition().x-mon->getGoal().x)< (MON_REAL_SIZE/2)*(MON_REAL_SIZE/2) ){
			mon->setVelocityX(0.0f);
			mon->setVelocityY(0.0f);
			mon->setVelocityZ(0.0f);
			mon->setisGoal(false);
			randPositionMon(time);
		}
		if(mon->getPosition().x>MAXBOUNDX) mon->setPostionX(MAXBOUNDX);
		if(mon->getPosition().x<MINBOUNDX) mon->setPostionX(MINBOUNDX);
		if(mon->getPosition().y>MAXBOUNDY) mon->setPostionY(MAXBOUNDY);
		if(mon->getPosition().y<MINBOUNDY) mon->setPostionY(MINBOUNDY);
		if(mon->getPosition().z>MAXBOUNDZ) mon->setPostionZ(MAXBOUNDZ);
		if(mon->getPosition().z<MINBOUNDZ) mon->setPostionZ(MINBOUNDZ);
	}
}
void Monai::stopMove(float time){
	//stop
		randPositionMon(time);
}

bool Monai::defenceMode(float time){
	if((defon == false)&&(time-(defEndTime+DEF_END_DELAY>0))){
		defStartTime = time;
		defon = true;
	}
	if(defon == true){
		if(time - defStartTime < DEF_START_DELAY){
			mon->monDefence(100);
			return true;
		}
		else{
			defon = false;
			defEndTime = time;
			return false;
		}
		return false;
	}
	return false;

}

bool Monai::missileMode(float time){
	if((msion == false)&&(time-(msiEndTime+MSI_END_DELAY>0))){
		msiStartTime = time;
		msion = true;
		for(int i=0;i<10;i++){
			msi[i]->start();
		}

	}
	if(msion == true){
		if(time - msiStartTime < MSI_START_DELAY){
			for(int i=0;i<10;i++){
				msi[i]->moveMissile(mon,cha,time);
			}
			return true;
		}
		else{
			msion = false;
			msiEndTime = time;
			return false;
		}
		return false;
	}
	return false;

}
bool Monai::wallMode(float time){
	if((wallon == false)&&(time-(wallEndTime+WALL_END_DELAY>0))){
			wallStartTime = time;
			wallon = true;
			wallPos = rand()%(int)MAXBOUNDX;	}
	if(wallon == true){
		if(time - wallStartTime < WALL_START_DELAY){
			switch(wallPos%3){
			case 0:
				mov->getPositionWall(cha,D3DXVECTOR3(wallPos,0,0));
				break;
			case 1:
				mov->getPositionWall(cha,D3DXVECTOR3(0,wallPos,0));
				break;
			case 2:
				mov->getPositionWall(cha,D3DXVECTOR3(0,0,wallPos));
				break;
			}
			return true;
		}
		else{
			wallon = false;
			wallEndTime = time;
			return false;
		}
		return false;
	}
	return false;
}
bool Monai::healingMode(float time){
	if((healon == false)&&(time-(healEndTime+HEAL_END_DELAY>0))){
		healStartTime = time;
		healEachDelay = time;
		healon = true;
	}
	if(healon == true){
		if(time - healStartTime < HEAL_START_DELAY){
			if(time - healEachDelay > 1){
				healEachDelay = time;
				mon->monHealing();
			}
			return true;
		}
		else{
			healon = false;
			healEndTime = time;
			return false;
		}
		return false;
	}
	return false;

}
bool Monai::raserMode(float time){
	if((raseron == false)&&(time-(raserEndTime+RASER_END_DELAY>0))){
		raserStartTime = time;
		raseron = true;
	}
	if(raseron == true){
		if(time - raserStartTime < RASER_START_DELAY){
	//		for(int i=0;i<10;i++){
	//			msi[i]->moveMissile(mon,cha,time);
	//		}
			return true;
		}
		else{
			raseron = false;
			raserEndTime = time;
			return false;
		}
		return false;
	}
	return false;

}
bool Monai::normalAtt(float time){

}

bool Monai::rushMode(float time){
	if((rushon == false)&&(time-(rushEndTime+RUSH_END_DELAY>0))){
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
		return false;
	}
	return false;

}

void Monai::subAction(float time){
	switch(mon->getsType()){
	case 0:
		missileMode(time);
		break;
	case 1:
		wallMode(time);
		break;
	case 2:
		healingMode(time);
		break;
	case 3:
		raserMode(time);
		break;
	case 4:
		rushMode(time);
		break;
	default:
		break;
	}
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
	if(raserEndTime+RASER_END_DELAY<time){return true;}
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


void Monai::Pase0(float time){
	switch(mon->getmType()){
	case 0:
		if(canMissile(time)){missileMode(time);}
		else if(canNorAtt(time)){normalAtt(time);}
		else if(canHealing(time)){healingMode(time);}
		break;
	case 1:
		if(canNorAtt(time)){normalAtt(time);}
		else if(canRush(time)){rushMode(time);}
		break;
	case 2:
		if(canMissile(time)){missileMode(time);}
		else if(canRaser(time)){raserMode(time);}
		else if(canHealing(time)){healingMode(time);}
		break;
	case 3:
		if(canDef(time)){defenceMode(time);}
		else if(canMissile(time)){missileMode(time);}
		break;
	case 4:
		if(canRush(time)){rushMode(time);}
		else if(canNorAtt(time)){normalAtt(time);}
		break;
	}
}
void Monai::Pase1(float time){
	switch(mon->getmType()){
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
}
void Monai::Pase2(float time){
	switch(mon->getmType()){
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
}
