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
	m_Interval = Interval;
}

void SDL_Timer::SetInterval(unsigned int i)
{
	m_Interval = i;
}

unsigned int SDL_Timer::GetInterval()
{
	return m_Interval;
}

void SDL_Timer::Start()
{
	m_StartTime = SDL_GetTicks();
	m_Started = true;
}

void SDL_Timer::Stop()
{
	m_Started = false;
}

bool SDL_Timer::TimerHit()
{
	if(!m_Started)
		return false;

	unsigned int tick = SDL_GetTicks();

	if (tick - m_StartTime > m_Interval)
		return true;
	else
		return false;
}

bool SDL_Timer::TimerHitR()
{
	bool res = TimerHit();
	if (res)
		m_StartTime = SDL_GetTicks();
	return res;
}

SDL_FlipFlopTimer::SDL_FlipFlopTimer(int Interval)
{
	m_Interval = Interval;
}

bool SDL_FlipFlopTimer::IsSet()
{
	if (TimerHitR())
		mSet = !mSet;

	return mSet;
}