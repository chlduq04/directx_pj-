#include "Pattern.h"
Pattern::Pattern(int type){
	actionType = type;
	switch(type){
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
bool Pattern::canPlay(float time){
	if((start)&&(endTime+endDelay<time)){return true;}
	return false;
};
bool Pattern::isPlay(float time){
	if(time - startTime < startDelay){
		return true;}
	else{return false;}
}
void Pattern::playAction(float time){
};

