#include "EventPoller.h"

void EventPoller::CheckEvents()
{
	while (!m_EventQueue.empty())
	{
		EventListener* evh = m_EventQueue.front();
		m_EventQueue.pop();

		for (IEvent* ev : evh->m_Events)
		{
			for (int i = 0; i < evh->m_Functions.size(); i++)
			{
				evh->m_Functions[i](ev);
			}

			delete ev;
		}
		evh->m_Events.clear();
	}
}
