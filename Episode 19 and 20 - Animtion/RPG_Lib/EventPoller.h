#pragma once
#include <map>
#include <queue>

#include "Singleton.h"
#include "EventListener.h"

class EventPoller : public UnCopyable
{
	std::queue<EventListener*> m_EventQueue;

private:
	friend class EventListener;
	friend class Singleton<EventPoller>;
	EventPoller() {}

public:
	void CheckEvents();
};

typedef Singleton<EventPoller> TheEventPoller;