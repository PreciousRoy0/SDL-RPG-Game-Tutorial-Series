#include "Console_Timer.h"

#include <chrono>

unsigned int Console_Timer::m_OldTick = 0;
unsigned int Console_Timer::m_CurrentTick = 0;

void Console_Timer::UpdateTimer()
{
	m_OldTick = m_CurrentTick;
	m_CurrentTick = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

	if (m_OldTick == 0)
		m_OldTick = m_CurrentTick;
}

float Console_Timer::GetDT()
{
	float dt = (m_CurrentTick - m_OldTick) / 1000.0f;

	if (dt > 0.2)
		dt = 0.2;

	return dt;
}
