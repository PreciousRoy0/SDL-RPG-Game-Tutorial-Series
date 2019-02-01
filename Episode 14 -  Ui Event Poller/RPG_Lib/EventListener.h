#pragma once
#include <vector>
#include <functional>

class IEvent;

class EventListener
{
	friend class EventPoller;
	std::vector<std::function<void(IEvent*)>> m_Functions;
	std::vector<IEvent*> m_Events;

public:

	template <typename FunctionCLass> //simple way to bind.  Bind<class>(&class::function, this);
	std::function<void(IEvent*)> Bind(void (FunctionCLass::* function)(IEvent*), FunctionCLass* instance)
	{
		return std::bind(function, instance, std::placeholders::_1);
	}

	EventListener() {}
	void SetEvent(IEvent* ev);

	void AddListener(std::function<void(IEvent*)> func);
	void RemoveListener(std::function<void(IEvent*)> func);
};