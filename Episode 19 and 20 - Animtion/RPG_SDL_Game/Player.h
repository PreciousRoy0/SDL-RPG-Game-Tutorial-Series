#pragma once

#include "Character.h"

class Player : public Character
{
	//Animations
	Animation2D m_IdleUp = Animation2D(&m_Animator);
	Animation2D m_IdleDown = Animation2D(&m_Animator);
	Animation2D m_IdleLeft = Animation2D(&m_Animator);
	Animation2D m_IdleRight = Animation2D(&m_Animator);

	Animation2D m_WalkUp = Animation2D(&m_Animator);
	Animation2D m_WalkDown = Animation2D(&m_Animator);
	Animation2D m_WalkLeft = Animation2D(&m_Animator);
	Animation2D m_WalkRight = Animation2D(&m_Animator);

	//Triggers
	BoolTrigger* WalkUpTrigger = new BoolTrigger();
	BoolTrigger* WalkDownTrigger = new BoolTrigger();
	BoolTrigger* WalkLeftTrigger = new BoolTrigger();
	BoolTrigger* WalkRightTrigger = new BoolTrigger();

	void MakeAnimation();
	void MakeTriggers();

	void MakeLinkTransitions();

	void MakeTransition(IAnimation* From, IAnimation* To, ITriggerCondition* condition);

public:
	int FireBallCount = 3;

	void Initialize();

	virtual void Update() override;
	virtual void Draw() override;
};
