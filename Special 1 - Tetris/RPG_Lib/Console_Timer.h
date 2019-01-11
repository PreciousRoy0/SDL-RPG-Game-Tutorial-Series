#pragma once

class Console_Timer
{
	static unsigned int m_OldTick;
	static unsigned int m_CurrentTick;

	static void UpdateTimer();
	friend class Console_GameStateManager;

public:

	static float GetDT();
};