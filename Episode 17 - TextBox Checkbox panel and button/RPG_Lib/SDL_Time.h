#pragma once

class SDL_DeltaTime
{
	static unsigned int m_OldTick;
	static unsigned int m_CurrentTick;

	friend class SDL_GameStateManager;
	static void UpdateTimer();

public:

	static float GetDT();
};

class SDL_Timer
{
protected:
	unsigned int mStartTime = 0;
	unsigned int mInterval = 1;

public:

	SDL_Timer() {};
	SDL_Timer(int Interval);

	void SetInterval(unsigned int i);
	unsigned int GetInterval();

	void Start();
	bool TimerHit();
	bool TimerHitR(); //auto reset
};


class SDL_FlipFlopTimer : public SDL_Timer
{
	bool mSet;

public:

	SDL_FlipFlopTimer() {}
	SDL_FlipFlopTimer(int Interval);

	bool IsSet();
};