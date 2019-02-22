#include "IAnimation.h"
#include "Animator.h"

//do i want to check for certain transition first before going for the first one i fond valid
void IAnimation::CheckTransitions()
{
	for (int i = 0; i < (int)m_Transitions.size(); i++)
	{
		if (m_Transitions[i].GetTriggerCount() == 0 && AnimationEnd)
		{
			m_Animator->TransitionMet(&m_Transitions[i]);
			break;
		}
		else if (m_Transitions[i].GetTriggerCount() > 0 && m_Transitions[i].ConditionsMet())
		{
			m_Animator->TransitionMet(&m_Transitions[i]);
			break;
		}
	}

	AnimationEnd = false;
}

void IAnimation::AddTransition(Transition tansition)
{
	m_Transitions.push_back(tansition);
}


