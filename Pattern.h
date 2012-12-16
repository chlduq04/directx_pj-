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

	float rate;

	int nextPatternCount;
	Pattern* nextPat;
	Pattern* prevPat;
public:
	Pattern();
	Pattern(int type);
	Pattern(int type, Pattern* nextpat1);
	~Pattern();
	Pattern* getNextPat();

	inline float getMotionDelay(){return motionDelay;};
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