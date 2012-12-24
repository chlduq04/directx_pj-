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

//	pCheckResult[행동][우선순위] = new pattern;
Checkai::Checkai(){
	pCheckResult[0][0] = new Pattern(2);
	pCheckResult[0][1] = new Pattern(0,new Pattern(1));
	pCheckResult[0][2] = new Pattern(0,new Pattern(2));
	pCheckResult[0][3] = new Pattern(5,new Pattern(0));
	pCheckResult[0][4] = new Pattern(5,new Pattern(1));
	pCheckResult[0][5] = new Pattern();

	pCheckResult[1][0] = new Pattern(4,new Pattern(2));
	pCheckResult[1][1] = new Pattern(5,new Pattern(0));
	pCheckResult[1][2] = new Pattern(0,new Pattern(4));
	pCheckResult[1][3] = new Pattern(2,new Pattern(4));
	pCheckResult[1][4] = new Pattern(3,new Pattern());
	pCheckResult[1][5] = new Pattern();

	pCheckResult[2][0] = new Pattern(3,new Pattern(0));
	pCheckResult[2][1] = new Pattern(0,new Pattern(1));
	pCheckResult[2][2] = new Pattern(0,new Pattern(2));
	pCheckResult[2][3] = new Pattern(1,new Pattern(3));
	pCheckResult[2][4] = new Pattern(2,new Pattern(3));
	pCheckResult[2][5] = new Pattern();

	pCheckResult[3][0] = new Pattern(3,new Pattern(0));
	pCheckResult[3][1] = new Pattern(0,new Pattern(0));
	pCheckResult[3][2] = new Pattern(1,new Pattern(0));
	pCheckResult[3][3] = new Pattern(2,new Pattern(0));
	pCheckResult[3][4] = new Pattern(5,new Pattern(0));
	pCheckResult[3][5] = new Pattern();

	pCheckResult[4][0] = new Pattern(3,new Pattern(0));
	pCheckResult[4][1] = new Pattern(5,new Pattern(0));
	pCheckResult[4][2] = new Pattern(4,new Pattern(3));
	pCheckResult[4][3] = new Pattern(2);
	pCheckResult[4][4] = new Pattern(0,new Pattern(3));
	pCheckResult[4][5] = new Pattern(2);
}
Checkai::~Checkai(){
	for(int i=0;i<MOVE_PATTERN_COUNT;i++){
		for(int j=0;j<ACTION_PATTERN_COUNT;j++){
			delete pCheckResult[i][j];
		}
	}
}

Pattern* Checkai::DoAction(int type,float time){
	for(int i=0;i<ACTION_PATTERN_COUNT;i++){
		if(pCheckResult[type][i]->CanPlay(time)){
			return pCheckResult[type][i];
			break;
		}
	}
	return pCheckResult[type][1];
}
void Checkai::ChangePattern(int motionNum,int actionNum){
	if(actionNum!=0){
		Pattern* origin = pCheckResult[motionNum][actionNum];
		pCheckResult[motionNum][actionNum] = pCheckResult[motionNum][actionNum-1];
		pCheckResult[motionNum][actionNum-1] = origin;
	}
}
void Checkai::mixPattern(){
}