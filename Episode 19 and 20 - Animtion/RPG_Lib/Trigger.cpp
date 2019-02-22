#include "Trigger.h"

Trigger::Trigger()
{
	m_Timer.SetInterval(100);
}

void Trigger::Update()
{
	if (m_Timer.TimerHit())
		TriggerValue = false;
}

bool TriggerConditionTrigger::ConditionMet()
{
	if (((Trigger*)m_trigger)->TriggerValue)
		return true;
	else
		return false;
	
}

bool TriggerConditionBool::ConditionMet()
{
	if (((BoolTrigger*)m_trigger)->TriggerValue == m_ValueB)
		return true;
	else
		return false;
}

bool TriggerConditionInt::ConditionMet()
{
	IntTrigger* trigger = (IntTrigger*)m_trigger;

	switch (m_Condition)
	{
	case Equals:
		if (trigger->TriggerValue == m_ValueB)
			return true;
		else
			return false;
		break;
	case NotEquals:
		if (trigger->TriggerValue != m_ValueB)
			return true;
		else
			return false;
		break;
	case GreaterThan:
		if (trigger->TriggerValue > m_ValueB)
			return true;
		else
			return false;
		break;
	case LesserThan:
		if (trigger->TriggerValue < m_ValueB)
			return true;
		else
			return false;
		break;
	}

	throw "Should not be here";
}

bool TriggerConditionFloat::ConditionMet()
{
	FloatTrigger* trigger = (FloatTrigger*)m_trigger;

	switch (m_Condition)
	{
	case GreaterThan:
		if (trigger->TriggerValue > m_ValueB)
			return true;
		else
			return false;
		break;
	case LesserThan:
		if (trigger->TriggerValue < m_ValueB)
			return true;
		else
			return false;
		break;
	}

	throw "Should not be here";
}
