#include "EventListener.h"
#include "EventPoller.h"

//deleted event in case of no functions registered
void EventListener::SetEvent(void* sender, IEvent * ev)
{
	if (m_Functions.size() > 0)
	{
		m_Events.push_back(std::make_pair(sender, ev));
		TheEventPoller::Pointer()->m_EventQueue.push(this);
	}
	else
		delete ev;
}

void EventListener::AddListener(std::function<void(void*, IEvent*)> func)
{
	m_Functions.push_back(func);
}

void EventListener::RemoveListener(std::function<void(void*, IEvent*)> func)
{
	for (int i = 0; i < (int)m_Functions.size(); i++)
	{
		if (m_Functions[i].target_type() == func.target_type())
		{
			m_Functions.erase(m_Functions.begin() + i);
			break;
		}
	}
}