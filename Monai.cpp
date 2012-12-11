#include "Monai.h"

Monai::Monai(Monster* monster,Ball* charecter,Missile* missile[],Moving* moving,float time){
	zero.x = 0.0f;
	zero.y = 0.0f;
	zero.z = 0.0f;

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

	msion = false;
	defon = false;
	wallon = false;
	healon = false;
	raseron = false;
	rushon = false;

	msiStartDelay = 20;
	msiEndDelay = 30;

	defStartDelay = 5;
	defEndDelay = 15;

	wallStartDelay = 10;
	wallEndDelay = 25;

	healStartDelay = 5;
	healEndDelay = 15;

	raserStartDelay = 5;
	raserEndDelay = 30;

	rushStartDelay = 5;
	rushEndDelay = 10;

}
Monai::~Monai(){}
void Monai::getPositionMon(float time){	
	switch(mon->getmType()){
	case 0:
		normalMove(time);
		subAction(time);
		break;
	case 1:
		closetoMove(time);
		break;
	case 2:
		stopMove(time);
		break;
	case 3:
		jumpMove(time);
		break;
	case 4:
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

}
void Monai::dodgeMove(float time){

}
void Monai::stopMove(float time){
	//stop
}

bool Monai::defenceMode(float time){
	if((defon == false)&&(time-(defEndTime+defEndDelay>0))){
		defStartTime = time;
		defon = true;
	}
	if(defon == true){
		if(time - defStartTime < defStartDelay){
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
	if((msion == false)&&(time-(msiEndTime+msiEndDelay>0))){
		msiStartTime = time;
		msion = true;
		for(int i=0;i<10;i++){
			msi[i]->start();
		}

	}
	if(msion == true){
		if(time - msiStartTime < msiStartDelay){
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
	if((wallon == false)&&(time-(wallEndTime+wallEndDelay>0))){
			wallStartTime = time;
			wallon = true;
			wallPos = rand()%(int)MAXBOUNDX;	}
	if(wallon == true){
		if(time - wallStartTime < wallStartDelay){
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
	if((healon == false)&&(time-(healEndTime+healEndDelay>0))){
		healStartTime = time;
		healEachDelay = time;
		healon = true;
	}
	if(healon == true){
		if(time - healStartTime < healStartDelay){
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
	if((raseron == false)&&(time-(raserEndTime+raserEndDelay>0))){
		raserStartTime = time;
		raseron = true;
	}
	if(raseron == true){
		if(time - raserStartTime < raserStartDelay){
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
bool Monai::rushMode(float time){
	if((rushon == false)&&(time-(rushEndTime+rushEndDelay>0))){
		rushStartTime = time;
		rushon = true;
	}
	if(rushon == true){
		if(time - rushStartTime < rushStartDelay){
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
	if(defEndTime+defEndDelay<time){return true;}
	return false;
}
bool Monai::canMissile(float time){
	if(msiEndTime+msiEndDelay<time){return true;}
	return false;
}
bool Monai::canHealing(float time){
	if(healEndTime+healEndDelay<time){return true;}
	return false;
}
bool Monai::canRaser(float time){
	if(raserEndTime+raserEndDelay<time){return true;}
	return false;
}
bool Monai::canRush(float time){
	if(rushEndTime+rushEndDelay<time){return true;}
	return false;
}
