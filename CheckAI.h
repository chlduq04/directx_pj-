#ifndef _CHECKAI_H_
#define _CHECKAI_H_

#include "Pattern.h"
#include "Settings.h"
class Checkai{
private:
	Pattern* pCheckResult[MOVE_PATTERN_COUNT][ACTION_PATTERN_COUNT];
public:
	Checkai();
	~Checkai();
	Pattern* DoAction(int type,float time);
	void mixPattern();
	inline void StartPattern(int move,int type,float time){pCheckResult[move][type]->StartPlay(time);};
	inline void EndPattern(int move,int type,float time){pCheckResult[move][type]->EndPlay(time);};
	inline bool IsPlay(int move,int type,float time){return pCheckResult[move][type]->IsPlay(time);};
	inline void DuringPlay(int move,int type,float time){pCheckResult[move][type]->DuringPlay(time);};
	inline void NotDuringPlay(int move,int type){pCheckResult[move][type]->NotDuringPlay();}
	inline int GetType(int type){return pCheckResult[type][type]->GetType();};
	void ChangePattern(int motionNum,int actionNum);
	//void Pattern* getDetailAction(int move,int action){return pCheckResult[move][action]};
};
#endif