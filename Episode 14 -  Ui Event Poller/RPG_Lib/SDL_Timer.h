#pragma once

class SDL_Timer
{
	static unsigned int m_OldTick;
	static unsigned int m_CurrentTick;

	friend class SDL_GameStateManager;
	static void UpdateTimer();

public:

	static float GetDT();
};