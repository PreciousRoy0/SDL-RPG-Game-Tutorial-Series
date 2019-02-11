#pragma once
#include <vector>
#include <functional>
#include "IEvent.h"

template <typename FunctionCLass> //simple way to bind.  Bind<MainMenuState>(&class::function, this);
static std::function<void(void*, IEvent*)> Bind(void (FunctionCLass::* function)(void*, IEvent*), FunctionCLass* instance)
{
	return std::bind(function, instance, std::placeholders::_1, std::placeholders::_2);
}

class EventListener
{
	friend class EventPoller;
	std::vector<std::function<void(void*, IEvent*)>> m_Functions;
	std::vector<std::pair<void*, IEvent*>> m_Events;

public:

	EventListener() {}
	void SetEvent(void* sender, IEvent* ev);

	void AddListener(std::function<void(void*, IEvent*)> func);
	void RemoveListener(std::function<void(void*, IEvent*)> func);
};