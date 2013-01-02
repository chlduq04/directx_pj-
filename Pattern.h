#ifndef _PATTERN_H_
#define _PATTERN_H_
#include "Settings.h"
#include "Monster.h"
class Pattern{
private:
	INT g_nType;
	INT nActionType;
	FLOAT fStartDelay;
	FLOAT fEndDelay;
	FLOAT fMotionDelay;

	FLOAT fEndTime;
	FLOAT fStartTime;
	INT nNextPattern[6];

	BOOL bStart;

    INT nRate;
	INT nDoCount;
	INT nEffective;

	INT nNextPatternCount;
	Pattern* pNextPat;
	Monster* g_pMonster;
public:
	Pattern();
	Pattern(Pattern* randpat,INT count);
	Pattern(int type);
	Pattern(int type, Pattern* nextpat);
	~Pattern();
	Pattern* GetNextPat();
	inline int GetNextPatternCount(){return nNextPatternCount;};
	inline float GetMotionDelay(){return fMotionDelay;};
	inline int GetType(){return nActionType;};
	inline int GetNowAction(){return g_nType;};
	inline void SetNowAction(int type){g_nType = type;};
	void PlayAction(float fTime);
	inline void StartPlay(float time){fStartTime = time; bStart = true;};
	inline void DuringPlay(float time){fStartTime = time;};
	inline void NotDuringPlay(){bStart = false;};
	inline void EndPlay(float time){
		fEndTime = time;
		bStart = false;
		SetRate();
	};
	bool CanPlay(float time);
	bool IsPlay(float time);
	
	void ActionPlay(float time);
	inline float GetRate(){return nRate;};

	inline VOID ResetRate(){
		nDoCount = 1;
		nEffective = 1;
		nRate = 0;
	};
	inline VOID UpDo(INT up){
		nDoCount += up;
	};
	inline VOID UpEffective(INT up){
		nEffective += up;
	};
	inline VOID SetRate(){
		nRate = (float)(nEffective/(nDoCount))*1000;
	};
};
#endif