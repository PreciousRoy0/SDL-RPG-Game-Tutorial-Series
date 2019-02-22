#include "Animator.h"

#include "Trigger.h"
#include "Transition.h"
#include "Animation2D.h"

void Animator::TransitionMet(Transition* transition)
{
	IAnimation* nextanim = transition->GetNextAnimation();

	if (nextanim == nullptr)
		throw "You idiot exception";

	m_CurrentAnimation->OnLeave();

	m_CurrentAnimation = nextanim;

	m_CurrentAnimation->OnEnter();
}

void Animator::AddTrigger(std::string TriggerName, ITrigger* Trigger)
{
	if (Trigger && TriggerName != "")
	{
		m_TriggersI[m_TriggersS.size()] = Trigger;
		m_TriggersS[TriggerName] = Trigger;
	}
	else
		throw "Need actual values";
}

int Animator::GetTriggerID(std::string TransitionName)
{
	int index = 0;

	for (std::pair<std::string, ITrigger*> trigger : m_TriggersS)
	{
		if (trigger.first == TransitionName)
			return index;
		index++;
	}

	return -1;
}

void Animator::SetStartAnimation(IAnimation * animation)
{
	if(m_CurrentAnimation)
		m_CurrentAnimation->OnLeave();

	m_CurrentAnimation = animation;

	m_CurrentAnimation->OnEnter();
}

void Animator::SetTrigger(std::string TriggerName)
{
	Trigger* trigger = dynamic_cast<Trigger*>(m_TriggersS[TriggerName]);
	if (trigger)
	{
		trigger->m_Timer.Start();
		trigger->TriggerValue = true;
	}
	else
		throw "Not the correct object or object not found";
}

void Animator::SetTrigger(int TriggerNameID)
{
	Trigger* trigger = dynamic_cast<Trigger*>(m_TriggersI[TriggerNameID]);
	if (trigger)
	{
		trigger->m_Timer.Start();
		trigger->TriggerValue = true;
	}
	else
		throw "Not the correct object or object not found";
}

void Animator::SetBool(std::string TriggerName, bool value)
{
	BoolTrigger* trigger = dynamic_cast<BoolTrigger*>(m_TriggersS[TriggerName]);

	if(trigger)
		trigger->TriggerValue = value;
	else 
		throw "Not the correct object or object not found";
}

void Animator::SetBool(int TriggerNameID, bool value)
{
	BoolTrigger* trigger = dynamic_cast<BoolTrigger*>(m_TriggersI[TriggerNameID]);

	if (trigger)
		trigger->TriggerValue = value;
	else
		throw "Not the correct object or object not found";
}

void Animator::SetInt(std::string TriggerName, int value)
{
	IntTrigger* trigger = dynamic_cast<IntTrigger*>(m_TriggersS[TriggerName]);

	if (trigger)
		trigger->TriggerValue = value;
	else
		throw "Not the correct object or object not found";
}

void Animator::SetInt(int TriggerNameID, int value)
{
	IntTrigger* trigger = dynamic_cast<IntTrigger*>(m_TriggersI[TriggerNameID]);

	if (trigger)
		trigger->TriggerValue = value;
	else
		throw "Not the correct object or object not found";
}

void Animator::SetFloat(std::string TriggerName, float value)
{
	FloatTrigger* trigger = dynamic_cast<FloatTrigger*>(m_TriggersS[TriggerName]);

	if (trigger)
		trigger->TriggerValue = value;
	else
		throw "Not the correct object or object not found";
}

void Animator::SetFloat(int TriggerNameID, float value)
{
	FloatTrigger* trigger = dynamic_cast<FloatTrigger*>(m_TriggersI[TriggerNameID]);

	if (trigger)
		trigger->TriggerValue = value;
	else
		throw "Not the correct object or object not found";
}

void Animator::Update()
{
	for (std::pair<std::string, ITrigger*> trigger : m_TriggersS)
	{
		trigger.second->Update();
	}

	m_CurrentAnimation->Update();
}

int Animator::GetCurrentFrame()
{
	return ((Animation2D*)m_CurrentAnimation)->GetCurrentFrame();
}
