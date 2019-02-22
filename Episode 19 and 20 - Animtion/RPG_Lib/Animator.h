#pragma once

#include <string>
#include <map>

class IAnimation;
//#include "Transition.h"
class Transition;
//#include "Trigger.h"
class ITrigger;

//this should and can become a component when i implement a component system
//animator is a state machine 
class Animator
{
	std::map<std::string, ITrigger*> m_TriggersS;
	std::map<int, ITrigger*> m_TriggersI;

	IAnimation* m_CurrentAnimation = nullptr;

	friend class IAnimation;
	void TransitionMet(Transition* transition);

public:
	void AddTrigger(std::string TriggerName, ITrigger* Trigger);
	int GetTriggerID(std::string TransitionName);

	void SetStartAnimation(IAnimation* animation);

	void SetTrigger(std::string TriggerName);
	void SetTrigger(int TriggerNameID);
	void SetBool(std::string TriggerName, bool value);
	void SetBool(int TriggerNameID, bool value);
	void SetInt(std::string TriggerName, int value);
	void SetInt(int TriggerNameID, int value);
	void SetFloat(std::string TriggerName, float value);
	void SetFloat(int TriggerNameID, float value);

	void Update();
	
	int GetCurrentFrame();
};