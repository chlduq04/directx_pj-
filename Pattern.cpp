#include "Pattern.h"
Pattern::Pattern(){
	bMissile = false;
	nRate = 0;
	nDoCount = 1;
	nEffective = 1;
	g_nType = 0;
	nNextPatternCount = 0;
	pNextPat = NULL;
	nActionType = rand()%ACTION_PATTERN_COUNT;
	switch(nActionType){
	case 0:
		fStartDelay = MSI_START_DELAY;
		fEndDelay = MSI_END_DELAY;
		fMotionDelay = MSI_MOTION_DELAY;
		break;
	case 1:
		fStartDelay = HEAL_START_DELAY;
		fEndDelay = HEAL_END_DELAY;
		fMotionDelay = HEAL_MOTION_DELAY;
		break;
	case 2:
		fStartDelay = DEF_START_DELAY;
		fEndDelay = DEF_END_DELAY;
		fMotionDelay = DEF_MOTION_DELAY;
		break;
	case 3:
		fStartDelay = LASER_START_DELAY;
		fEndDelay = LASER_END_DELAY;
		fMotionDelay = LASER_MOTION_DELAY;
		break;
	case 4:
		fStartDelay = NATT_START_DELAY;
		fEndDelay = NATT_END_DELAY;
		fMotionDelay = NATT_MOTION_DELAY;
		break;
	case 5:
		fStartDelay = WALL_START_DELAY;
		fEndDelay = WALL_END_DELAY;
		fMotionDelay = WALL_MOTION_DELAY;
		break;
	default:
		break;
	}
}
Pattern::Pattern(Pattern* randpat,INT count){
	bMissile = false;
	nRate = 0;
	nDoCount = 1;
	nEffective = 1;
	g_nType = 0;

	nNextPatternCount = count;
	if(count){
		pNextPat = new Pattern();
	}else{
		pNextPat = new Pattern(randpat,count-1);
	}
	nActionType = rand()%ACTION_PATTERN_COUNT;
	switch(nActionType){
	case 0:
		fStartDelay = MSI_START_DELAY;
		fEndDelay = MSI_END_DELAY;
		fMotionDelay = MSI_MOTION_DELAY;
		break;
	case 1:
		fStartDelay = HEAL_START_DELAY;
		fEndDelay = HEAL_END_DELAY;
		fMotionDelay = HEAL_MOTION_DELAY;
		break;
	case 2:
		fStartDelay = DEF_START_DELAY;
		fEndDelay = DEF_END_DELAY;
		fMotionDelay = DEF_MOTION_DELAY;
		break;
	case 3:
		fStartDelay = LASER_START_DELAY;
		fEndDelay = LASER_END_DELAY;
		fMotionDelay = LASER_MOTION_DELAY;
		break;
	case 4:
		fStartDelay = NATT_START_DELAY;
		fEndDelay = NATT_END_DELAY;
		fMotionDelay = NATT_MOTION_DELAY;
		break;
	case 5:
		fStartDelay = WALL_START_DELAY;
		fEndDelay = WALL_END_DELAY;
		fMotionDelay = WALL_MOTION_DELAY;
		break;
	default:
		break;
	}
}
Pattern::Pattern(int type){
	bMissile = false;
	nRate = 0;
	nDoCount = 1;
	nEffective = 1;
	g_nType = 0;
	nNextPatternCount = 0;
	pNextPat = NULL;
	nActionType = type;
	switch(nActionType){
	case 0:
		fStartDelay = MSI_START_DELAY;
		fEndDelay = MSI_END_DELAY;
		fMotionDelay = MSI_MOTION_DELAY;
		break;
	case 1:
		fStartDelay = HEAL_START_DELAY;
		fEndDelay = HEAL_END_DELAY;
		fMotionDelay = HEAL_MOTION_DELAY;
		break;
	case 2:
		fStartDelay = DEF_START_DELAY;
		fEndDelay = DEF_END_DELAY;
		fMotionDelay = DEF_MOTION_DELAY;
		break;
	case 3:
		fStartDelay = LASER_START_DELAY;
		fEndDelay = LASER_END_DELAY;
		fMotionDelay = LASER_MOTION_DELAY;
		break;
	case 4:
		fStartDelay = NATT_START_DELAY;
		fEndDelay = NATT_END_DELAY;
		fMotionDelay = NATT_MOTION_DELAY;
		break;
	case 5:
		fStartDelay = WALL_START_DELAY;
		fEndDelay = WALL_END_DELAY;
		fMotionDelay = WALL_MOTION_DELAY;
		break;
	default:
		break;
	}
}
Pattern::Pattern(int type, Pattern* nextpat){
	bMissile = false;
	nRate = 0;
	nDoCount = 1;
	nEffective = 1;
	nNextPatternCount = 1;
	g_nType = 0;
	nActionType = type;
	pNextPat = nextpat;
	switch(nActionType){
	case 0:
		fStartDelay = MSI_START_DELAY;
		fEndDelay = MSI_END_DELAY;
		fMotionDelay = MSI_MOTION_DELAY;
		break;
	case 1:
		fStartDelay = HEAL_START_DELAY;
		fEndDelay = HEAL_END_DELAY;
		fMotionDelay = HEAL_MOTION_DELAY;
		break;
	case 2:
		fStartDelay = DEF_START_DELAY;
		fEndDelay = DEF_END_DELAY;
		fMotionDelay = DEF_MOTION_DELAY;
		break;
	case 3:
		fStartDelay = LASER_START_DELAY;
		fEndDelay = LASER_END_DELAY;
		fMotionDelay = LASER_MOTION_DELAY;
		break;
	case 4:
		fStartDelay = NATT_START_DELAY;
		fEndDelay = NATT_END_DELAY;
		fMotionDelay = NATT_MOTION_DELAY;
		break;
	case 5:
		fStartDelay = WALL_START_DELAY;
		fEndDelay = WALL_END_DELAY;
		fMotionDelay = WALL_MOTION_DELAY;
		break;
	default:
		break;
	}

}

Pattern::~Pattern(){
	if(nNextPatternCount<1){
	}
	else{
		if(pNextPat != NULL){
			delete pNextPat;
		}
	}
}

bool Pattern::CanPlay(float time){
	if((bStart)&&(fEndTime+fEndDelay<time)){return true;}
	return false;
}
bool Pattern::IsPlay(float time){
	if(time - fStartTime < fStartDelay||bMissile){
		return true;}
	else{return false;}
}

Pattern* Pattern::GetNextPat(){
	if(nNextPatternCount == 1){
		return pNextPat;
	}return NULL;
	
}

