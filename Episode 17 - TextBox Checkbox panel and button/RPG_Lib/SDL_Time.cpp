#include "SDL_Time.h"

#include <SDL.h>

unsigned int SDL_DeltaTime::m_OldTick;
unsigned int SDL_DeltaTime::m_CurrentTick;

void SDL_DeltaTime::UpdateTimer()
{
	m_OldTick = m_CurrentTick;
	m_CurrentTick = SDL_GetTicks();
}

float SDL_DeltaTime::GetDT()
{
	float res = (m_CurrentTick - m_OldTick) / 1000.0f;

	if (res > 0.2f)
		res = 0.2f;

	return res;
}


SDL_Timer::SDL_Timer(int Interval)
{
	mInterval = Interval;
}

void SDL_Timer::SetInterval(unsigned int i)
{
	mInterval = i;
}

unsigned int SDL_Timer::GetInterval()
{
	return mInterval;
}

void SDL_Timer::Start()
{
	mStartTime = SDL_GetTicks();
}

bool SDL_Timer::TimerHit()
{
	unsigned int tick = SDL_GetTicks();

	if (tick - mStartTime > mInterval)
		return true;
	else
		return false;
}

bool SDL_Timer::TimerHitR()
{
	bool res = TimerHit();
	if (res)
		mStartTime = SDL_GetTicks();
	return res;
}

SDL_FlipFlopTimer::SDL_FlipFlopTimer(int Interval)
{
	mInterval = Interval;
}

bool SDL_FlipFlopTimer::IsSet()
{
	if (TimerHitR())
		mSet = !mSet;

	return mSet;
}