#ifndef _CHECKAI_H_
#define _CHECKAI_H_

#include "Pattern.h"
#include "Settings.h"
class Checkai{
private:
	Pattern* checkResult[MOVE_PATTERN_COUNT][ACTION_PATTERN_COUNT];
public:
	Checkai();
	~Checkai();
	Pattern* doAction(int type,float time);
	inline void patternStart(int move,int type,float time){checkResult[move][type]->startPlay(time);};
	inline void patternEnd(int move,int type,float time){checkResult[move][type]->endPlay(time);};
	inline bool isPlay(int move,int type,float time){return checkResult[move][type]->isPlay(time);};
	inline void duringPlay(int move,int type,float time){checkResult[move][type]->duringPlay(time);};
	inline void notDuringPlay(int move,int type){checkResult[move][type]->notDuringPlay();}
	inline int getType(int move,int type){return checkResult[type][type]->getType();};
	void changePattern(int motionNum,int actionNum);
	//void Pattern* getDetailAction(int move,int action){return checkResult[move][action]};
};
#endif