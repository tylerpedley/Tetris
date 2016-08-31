#ifndef TIMER_INCLUDED
#define TIMER_INCLUDED

#include <SDL.h>

class Timer
{
private:
	int mStartTicks, mPausedTicks;
	bool mPaused;
	bool mStarted;
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Pause();
	void Unpause();
	int GetTicks();
	bool isPaused();
	bool isStarted();
};

#endif