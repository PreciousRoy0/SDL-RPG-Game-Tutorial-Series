#pragma once

#include "IAnimation.h"
#include "Animator.h"

//animation is a state
class Animation2D : public IAnimation
{
	SDL_Timer m_AnmimationTimer;
	std::vector<std::pair<int, int>> m_Frames; // frame , time

	int m_CurrentFrame = 0;

	friend class Animator;
	virtual void OnEnter() override;
	virtual void OnLeave() override;
	virtual void Update()  override;

public:
	Animation2D(Animator* animator) : IAnimation(animator) {}

	void AddFrame(int CellID, int time) { m_Frames.push_back(std::pair<int, int>(CellID, time)); }

	int GetCurrentFrame() { return m_Frames[m_CurrentFrame].first; }
};