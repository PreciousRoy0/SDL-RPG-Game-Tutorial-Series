#pragma once

#include <vector>

#include "Trigger.h"
class IAnimation;

class Transition
{
	IAnimation* m_NextAnimation = nullptr;
	std::vector<ITriggerCondition*> m_TriggerConditionss; 

	int FindCondition(ITriggerCondition* condition); 

public:

	void SetNextAnimation(IAnimation* animation);
	IAnimation* GetNextAnimation();
	int GetTriggerCount() { return m_TriggerConditionss.size(); }

	void AddTrigger(ITriggerCondition* condition);
	void RemoveTrigger(ITriggerCondition* condition);

	bool ConditionsMet();

	~Transition();
};