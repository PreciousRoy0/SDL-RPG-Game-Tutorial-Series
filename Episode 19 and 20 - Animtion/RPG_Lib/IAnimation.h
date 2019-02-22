#pragma once

#include <vector>

#include "SDL_Time.h"
#include "Transition.h"
#include "Animator.h"

class IAnimation
{
protected:
	friend class Animator;
	Animator* m_Animator = nullptr;
	std::vector <Transition> m_Transitions;
	bool Looping = true;
	bool AnimationEnd = false;

	void CheckTransitions();

public:
	IAnimation(Animator* animator) : m_Animator(animator) {}

	void AddTransition(Transition);
	void SetLooping(bool res) { Looping = res; }

	//when entering the animation stat this is called once
	virtual void OnEnter() = 0;
	//when leaving the animation state this is called once
	virtual void OnLeave() = 0;
	//called every frame
	virtual void Update() = 0;

	virtual ~IAnimation() = 0 {}
};

