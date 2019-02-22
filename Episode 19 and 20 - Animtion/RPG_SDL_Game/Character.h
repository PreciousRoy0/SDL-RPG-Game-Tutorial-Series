#pragma once

#include <map>
#include <vector>
#include <string>

#include "Rectangle2D.h"
#include "SDL_Time.h"

#include "SDL_TileSheet.h"

#include "Animator.h"
#include "Animation2D.h"
#include "Transition.h"
#include "Trigger.h"

enum AnimationDirection
{
	AD_Up,
	AD_Down,
	AD_Left,
	AD_Right
};

class Character
{
protected:
	Animator m_Animator;
	SDL_TileSheet* m_AnimationSheet;
	AnimationDirection m_AnimationDirection = AnimationDirection::AD_Down;

	bool m_Alive = true;

	RectangleF m_Box; //contains the location and is also the bounding box
	Vector2F m_Acceleration;
	Vector2F m_Velocity;
	Vector2F m_NewPosition;

public:
	void SetLocation(Vector2 loc) { m_Box.X = loc.X; m_Box.Y = loc.Y; }

	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~Character() = 0 {}
};

