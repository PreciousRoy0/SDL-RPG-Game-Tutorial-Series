#pragma once

#include "SDL_Time.h"

//Triggers are containers for different types of values 
// They do not do anything other than hold a value

class ITrigger
{
public:

	virtual void Update() {};

	virtual ~ITrigger() = 0 {};
};

//trigger is a bool value that resets after an amount of tile
class Trigger : public ITrigger
{
	friend class Animator;

	SDL_Timer m_Timer;

public:
	Trigger();

	bool TriggerValue = false;

	virtual void Update() override;
};

class BoolTrigger : public ITrigger
{
public:

	bool TriggerValue = false;
};

class IntTrigger : public ITrigger
{
public:

	int TriggerValue = 0;
};

class FloatTrigger : public ITrigger
{
public:

	float TriggerValue = 0.0f;
};


enum TriggerConditionTypes
{
	Equals,
	NotEquals,
	GreaterThan,
	LesserThan
};

class ITriggerCondition
{
protected:
	ITrigger* m_trigger;

public:
	ITriggerCondition(ITrigger* trigger) : m_trigger(trigger) {}

	virtual bool ConditionMet() = 0;
};

class TriggerConditionTrigger : public ITriggerCondition
{
public:
	TriggerConditionTrigger(ITrigger* trigger) : ITriggerCondition(trigger) {}

	virtual bool ConditionMet();
};

class TriggerConditionBool : public ITriggerCondition
{
	bool m_ValueB = true;
	
public:
	TriggerConditionBool(ITrigger* trigger, bool triggercondition) : ITriggerCondition(trigger), m_ValueB(triggercondition) {}

	virtual bool ConditionMet();
};

class TriggerConditionInt : public ITriggerCondition
{
	int m_ValueB = 0;
	TriggerConditionTypes m_Condition = TriggerConditionTypes::Equals;

public:
	TriggerConditionInt(ITrigger* trigger, TriggerConditionTypes condition, int valueB) : ITriggerCondition(trigger), m_Condition(condition), m_ValueB(valueB) {}

	virtual bool ConditionMet();
};

class TriggerConditionFloat : public ITriggerCondition
{
	float m_ValueB = 0;
	TriggerConditionTypes m_Condition = TriggerConditionTypes::GreaterThan;

public:

	TriggerConditionFloat(ITrigger* trigger, TriggerConditionTypes condition, float valueB) : ITriggerCondition(trigger), m_ValueB(valueB) 
	{
		if (condition == TriggerConditionTypes::Equals || condition == TriggerConditionTypes::NotEquals)
		{
			throw "Idiot you cant do that!!!";
		}
	}

	virtual bool ConditionMet();
};