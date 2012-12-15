#ifndef _PATTERN_H_
#define _PATTERN_H_
#include "Settings.h"
class Pattern{
private:
	int actionType;
	float startDelay;
	float endDelay;
	float motionDelay;

	float endTime;
	float startTime;
	int nextPattern[6];

	bool start;
public:
	Pattern(int type);
	inline int getType(){return actionType;};
	void playAction(float time);
	inline void startPlay(float time){startTime = time; start = true;};
	inline void duringPlay(float time){startTime = time;};
	inline void notDuringPlay(){start = false;};
	inline void endPlay(float time){endTime = time; start = false;};

	bool canPlay(float time);
	bool isPlay(float time);
	void ActionPlay(float time);
};
#endif