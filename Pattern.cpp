#include "Pattern.h"
Pattern::Pattern(){
	nNextPatternCount = 0;
	pNextPat = NULL;
	pPrevPat= NULL;
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
	nNextPatternCount = 0;
	pNextPat = NULL;
	pPrevPat = NULL;
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
Pattern::Pattern(int type, Pattern* nextpat1){
	nNextPatternCount = 1;
	nActionType = type;
	pNextPat = nextpat1;
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
	if(nNextPatternCount==1){
		delete pNextPat;
	}
}
bool Pattern::CanPlay(float time){
	if((bStart)&&(fEndTime+fEndDelay<time)){return true;}
	return false;
}
bool Pattern::IsPlay(float time){
	if(time - fStartTime < fStartDelay){
		return true;}
	else{return false;}
}

Pattern* Pattern::GetNextPat(){
	if(nNextPatternCount == 1){
		return pNextPat;
	}return NULL;
	
}

