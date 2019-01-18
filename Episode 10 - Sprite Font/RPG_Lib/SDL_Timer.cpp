#include "SDL_Timer.h"

#include <SDL.h>

unsigned int SDL_Timer::m_OldTick;
unsigned int SDL_Timer::m_CurrentTick;

void SDL_Timer::UpdateTimer()
{
	m_OldTick = m_CurrentTick;
	m_CurrentTick = SDL_GetTicks();
}

float SDL_Timer::GetDT()
{
	float res = (m_CurrentTick - m_OldTick) / 1000.0f;

	if (res > 0.2f)
		res = 0.2f;

	return res;
}
