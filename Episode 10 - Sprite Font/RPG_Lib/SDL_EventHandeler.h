#pragma once

#include "Singleton.h"

class SDL_EventHandeler : public UnCopyable
{
	friend Singleton<SDL_EventHandeler>;
	SDL_EventHandeler() {}

public:
	void PoolEvents();

};

typedef	Singleton<SDL_EventHandeler> TheSDLEventHandeler;