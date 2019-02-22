#include "Transition.h"

int Transition::FindCondition(ITriggerCondition* condition)
{
	int res = -1;

	for (size_t i = 0; i < (int)m_TriggerConditionss.size(); i++)
	{
		if (m_TriggerConditionss[i] == condition)
		{
			res = i;
			break;
		}
	}

	return res;
}

void Transition::SetNextAnimation(IAnimation* animation)
{
	if (!animation)
		throw "You idiot exption";

	m_NextAnimation = animation;
}

IAnimation* Transition::GetNextAnimation()
{
	return m_NextAnimation;
}

void Transition::AddTrigger(ITriggerCondition* condition)
{
	int exists = FindCondition(condition);
	if (exists < 0)
		m_TriggerConditionss.push_back(condition);

}

void Transition::RemoveTrigger(ITriggerCondition* condition)
{
	int exists = FindCondition(condition);
	if (exists < 0)
	{
		//do not forget to delete it ?
		delete m_TriggerConditionss[exists];

		m_TriggerConditionss.erase(m_TriggerConditionss.begin() + exists);
	}
}

bool Transition::ConditionsMet()
{
	bool res = true;

	for (size_t i = 0; i < (int)m_TriggerConditionss.size(); i++)
	{
		res = m_TriggerConditionss[i]->ConditionMet();

		if (!res)
			break;
	}

	return res;
}

Transition::~Transition()
{
	//for (size_t i = 0; i < (int)m_TriggerConditionss.size(); i++)
	//{
	//	delete m_TriggerConditionss[i];
	//}
}
