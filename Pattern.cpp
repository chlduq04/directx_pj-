#include "Pattern.h"
Pattern::Pattern(){
	nextPatternCount = 0;
	nextPat = NULL;
	prevPat= NULL;
	actionType = rand()%ACTION_PATTERN_COUNT;
	switch(actionType){
	case 0:
		startDelay = MSI_START_DELAY;
		endDelay = MSI_END_DELAY;
		motionDelay = MSI_MOTION_DELAY;
		break;
	case 1:
		startDelay = HEAL_START_DELAY;
		endDelay = HEAL_END_DELAY;
		motionDelay = HEAL_MOTION_DELAY;
		break;
	case 2:
		startDelay = DEF_START_DELAY;
		endDelay = DEF_END_DELAY;
		motionDelay = DEF_MOTION_DELAY;
		break;
	case 3:
		startDelay = LASER_START_DELAY;
		endDelay = LASER_END_DELAY;
		motionDelay = LASER_MOTION_DELAY;
		break;
	case 4:
		startDelay = NATT_START_DELAY;
		endDelay = NATT_END_DELAY;
		motionDelay = NATT_MOTION_DELAY;
		break;
	case 5:
		startDelay = WALL_START_DELAY;
		endDelay = WALL_END_DELAY;
		motionDelay = WALL_MOTION_DELAY;
		break;
	default:
		break;
	}
}
Pattern::Pattern(int type){
	nextPatternCount = 0;
	nextPat = NULL;
	prevPat = NULL;
	actionType = type;
	switch(actionType){
	case 0:
		startDelay = MSI_START_DELAY;
		endDelay = MSI_END_DELAY;
		motionDelay = MSI_MOTION_DELAY;
		break;
	case 1:
		startDelay = HEAL_START_DELAY;
		endDelay = HEAL_END_DELAY;
		motionDelay = HEAL_MOTION_DELAY;
		break;
	case 2:
		startDelay = DEF_START_DELAY;
		endDelay = DEF_END_DELAY;
		motionDelay = DEF_MOTION_DELAY;
		break;
	case 3:
		startDelay = LASER_START_DELAY;
		endDelay = LASER_END_DELAY;
		motionDelay = LASER_MOTION_DELAY;
		break;
	case 4:
		startDelay = NATT_START_DELAY;
		endDelay = NATT_END_DELAY;
		motionDelay = NATT_MOTION_DELAY;
		break;
	case 5:
		startDelay = WALL_START_DELAY;
		endDelay = WALL_END_DELAY;
		motionDelay = WALL_MOTION_DELAY;
		break;
	default:
		break;
	}
}
Pattern::Pattern(int type, Pattern* nextpat1){
	nextPatternCount = 1;
	actionType = type;
	nextPat = nextpat1;
	switch(actionType){
	case 0:
		startDelay = MSI_START_DELAY;
		endDelay = MSI_END_DELAY;
		motionDelay = MSI_MOTION_DELAY;
		break;
	case 1:
		startDelay = HEAL_START_DELAY;
		endDelay = HEAL_END_DELAY;
		motionDelay = HEAL_MOTION_DELAY;
		break;
	case 2:
		startDelay = DEF_START_DELAY;
		endDelay = DEF_END_DELAY;
		motionDelay = DEF_MOTION_DELAY;
		break;
	case 3:
		startDelay = LASER_START_DELAY;
		endDelay = LASER_END_DELAY;
		motionDelay = LASER_MOTION_DELAY;
		break;
	case 4:
		startDelay = NATT_START_DELAY;
		endDelay = NATT_END_DELAY;
		motionDelay = NATT_MOTION_DELAY;
		break;
	case 5:
		startDelay = WALL_START_DELAY;
		endDelay = WALL_END_DELAY;
		motionDelay = WALL_MOTION_DELAY;
		break;
	default:
		break;
	}

}

Pattern::~Pattern(){
	if(nextPatternCount==1){
		delete nextPat;
	}
}
bool Pattern::canPlay(float time){
	if((start)&&(endTime+endDelay<time)){return true;}
	return false;
}
bool Pattern::isPlay(float time){
	if(time - startTime < startDelay){
		return true;}
	else{return false;}
}

Pattern* Pattern::getNextPat(){
	if(nextPatternCount == 1){
		return nextPat;
	}return NULL;
	
}

void Pattern::playAction(float time){
}
