#include "EventPoller.h"

void EventPoller::CheckEvents()
{
	while (!m_EventQueue.empty())
	{
		EventListener* evh = m_EventQueue.front();
		m_EventQueue.pop();

		for (auto ev : evh->m_Events)
		{
			for (int i = 0; i < (int)evh->m_Functions.size(); i++)
			{
				evh->m_Functions[i](ev.first, ev.second);
			}

			delete ev.second;
		}
		evh->m_Events.clear();
	}
}
