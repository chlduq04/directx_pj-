#include "CheckAI.h"

//  NORMAL_MOVE_PATTERN 0
//	CONTECT_MOVE_PATTERN 1
//	DODGE_MOVE_PATTERN 2
//	STOP_MOVE_PATTERN 3
//	JUMP_MOVE_PATTERN 4
//
//	MISSILE_ACTION_PATTERN 0
//	HEALING_ACTION_PATTERN 1
//	DEFENCE_ACTION_PATTERN 2
//	LASER_ACTION_PATTERN 3
//	NATTACK_ACTION_PATTERN 4	
//	WALL_ACTION_PATTERN 5

//	checkresult[행동][우선순위] = new pattern;
Checkai::Checkai(){
	checkResult[0][0] = new Pattern(2);
	checkResult[0][1] = new Pattern(0,new Pattern(1));
	checkResult[0][2] = new Pattern(0,new Pattern(2));
	checkResult[0][3] = new Pattern(5,new Pattern(0));
	checkResult[0][4] = new Pattern(5,new Pattern(1));
	checkResult[0][5] = new Pattern();

	checkResult[1][0] = new Pattern(4,new Pattern(2));
	checkResult[1][1] = new Pattern(5,new Pattern(0));
	checkResult[1][2] = new Pattern(0,new Pattern(4));
	checkResult[1][3] = new Pattern(2,new Pattern(4));
	checkResult[1][4] = new Pattern(3,new Pattern());
	checkResult[1][5] = new Pattern();

	checkResult[2][0] = new Pattern(3,new Pattern(0));
	checkResult[2][1] = new Pattern(0,new Pattern(1));
	checkResult[2][2] = new Pattern(0,new Pattern(2));
	checkResult[2][3] = new Pattern(1,new Pattern(3));
	checkResult[2][4] = new Pattern(2,new Pattern(3));
	checkResult[2][5] = new Pattern();
	

	checkResult[3][0] = new Pattern(3,new Pattern(0));
	checkResult[3][1] = new Pattern(0,new Pattern(0));
	checkResult[3][2] = new Pattern(1,new Pattern(0));
	checkResult[3][3] = new Pattern(2,new Pattern(0));
	checkResult[3][4] = new Pattern(5,new Pattern(0));
	checkResult[3][5] = new Pattern();

	checkResult[4][0] = new Pattern(3,new Pattern(0));
	checkResult[4][1] = new Pattern(5,new Pattern(0));
	checkResult[4][2] = new Pattern(4,new Pattern(3));
	checkResult[4][3] = new Pattern(2);
	checkResult[4][4] = new Pattern(0,new Pattern(3));
	checkResult[4][5] = new Pattern(2);
}
Checkai::~Checkai(){
	for(int i=0;i<MOVE_PATTERN_COUNT;i++){
		for(int j=0;j<ACTION_PATTERN_COUNT;j++){
			delete checkResult[i][j];
		}
	}
}
Pattern* Checkai::doAction(int type,float time){
	for(int i=0;i<ACTION_PATTERN_COUNT;i++){
		if(checkResult[type][i]->canPlay(time)){
			return checkResult[type][i];
			break;
		}
	}
	return checkResult[type][1];
}
void Checkai::changePattern(int motionNum,int actionNum){
	if(actionNum!=0){
		Pattern* origin = checkResult[motionNum][actionNum];
		checkResult[motionNum][actionNum] = checkResult[motionNum][actionNum-1];
		checkResult[motionNum][actionNum-1] = origin;
	}
}