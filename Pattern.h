#ifndef _PATTERN_H_
#define _PATTERN_H_
#include "Settings.h"
class Pattern{
private:
	int nActionType;
	float fStartDelay;
	float fEndDelay;
	float fMotionDelay;

	float fEndTime;
	float fStartTime;
	int nNextPattern[6];

	bool bStart;

	float fRate;


	int nNextPatternCount;
	Pattern* pNextPat;
	Pattern* pPrevPat;
public:
	Pattern();
	Pattern(int type);
	Pattern(int type, Pattern* nextpat1);
	~Pattern();
	Pattern* GetNextPat();

	inline float GetMotionDelay(){return fMotionDelay;};
	inline int GetType(){return nActionType;};
	void PlayAction(float fTime);
	inline void StartPlay(float time){fStartTime = time; bStart = true;};
	inline void DuringPlay(float time){fStartTime = time;};
	inline void NotDuringPlay(){bStart = false;};
	inline void EndPlay(float time){fEndTime = time; bStart = false;};

	bool CanPlay(float time);
	bool IsPlay(float time);

	void ActionPlay(float time);
	inline float GetRate(){return fRate;};

};
#endif