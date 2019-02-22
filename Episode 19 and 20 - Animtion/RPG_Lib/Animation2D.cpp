#include "Animation2D.h"
#include "Animator.h"

void Animation2D::OnEnter()
{
	m_CurrentFrame = 0;
	m_AnmimationTimer.SetInterval(m_Frames[0].second);
	m_AnmimationTimer.Start();
}

void Animation2D::OnLeave()
{
	m_AnmimationTimer.Stop();
}

void Animation2D::Update()
{
	if (m_AnmimationTimer.TimerHit())
	{
		if (m_CurrentFrame == (int)m_Frames.size() - 1 && !Looping)
		{
			AnimationEnd = true;
		}
		else
			if (m_CurrentFrame == (int)m_Frames.size() - 1)
			{
				AnimationEnd = true;
				m_CurrentFrame = 0;
				m_AnmimationTimer.SetInterval(m_Frames[m_CurrentFrame].second);
				m_AnmimationTimer.Start();
			}
			else
			{
				m_CurrentFrame++;
				m_AnmimationTimer.SetInterval(m_Frames[m_CurrentFrame].second);
				m_AnmimationTimer.Start();
			}
	}

	CheckTransitions();
}
