#include "Timer.h"


Timer::Timer()
{
	mStartTicks = 0;
	mPausedTicks = 0;
	mPaused = false;
	mStarted = false;
}


Timer::~Timer()
{
}

void Timer::Start()
{
	if (mStarted == false)
	{
		mPaused = false;
		mStartTicks = SDL_GetTicks();
	}
}

void Timer::Stop()
{
	mStarted = false;
	mPaused = false;
}

void Timer::Pause()
{
	if ((mStarted) && (!mPaused))
	{
		mPaused = true;

		mPausedTicks = SDL_GetTicks() - mStartTicks;
	}
}

void Timer::Unpause()
{
	if (mPaused == true)
	{
		mPaused = false;

		mStartTicks = SDL_GetTicks() - mPausedTicks;

		mPausedTicks = 0;
	}
}

int Timer::GetTicks()
{
	if (mStarted)
	{
		if (mPaused)
		{
			return mPausedTicks;
		}
		else
		{
			return SDL_GetTicks() - mStartTicks;
		}
	}

	return 0;
}

bool Timer::isPaused()
{
	return mPaused;
}

bool Timer::isStarted()
{
	return mStarted;
}