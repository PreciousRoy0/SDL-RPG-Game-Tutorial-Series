#include "Player.h"

#include "AssetManager.h"
#include "SDL_ScreenHandeler.h"

#include "Keyboard.h"

void Player::MakeAnimation()
{
	//idle animation
	m_IdleDown.AddFrame(24, 100);//no idle animation

	m_IdleLeft.AddFrame(23, 100);	//no idle animation
	m_IdleRight.AddFrame(26, 100);	//no idle animation
	m_IdleUp.AddFrame(25, 100);	//no idle animation

	//walk animations
	m_WalkDown.AddFrame(24, 150);
	m_WalkDown.AddFrame(51, 150);
	m_WalkDown.AddFrame(78, 150);

	m_WalkLeft.AddFrame(23, 150);
	m_WalkLeft.AddFrame(50, 150);
	m_WalkLeft.AddFrame(77, 150);

	m_WalkRight.AddFrame(26, 150);
	m_WalkRight.AddFrame(53, 150);
	m_WalkRight.AddFrame(80, 150);

	m_WalkUp.AddFrame(25, 150);
	m_WalkUp.AddFrame(52, 150);
	m_WalkUp.AddFrame(79, 150);

	m_Animator.SetStartAnimation(&m_IdleDown);
}

void Player::MakeTriggers()
{
	m_Animator.AddTrigger("WalkDown", WalkDownTrigger);
	m_Animator.AddTrigger("WalkLeft", WalkLeftTrigger);
	m_Animator.AddTrigger("WalkRight", WalkRightTrigger);
	m_Animator.AddTrigger("WalkUp", WalkUpTrigger);
}

void Player::MakeLinkTransitions()
{
	//idle to walk
	MakeTransition(&m_IdleUp, &m_WalkUp, new TriggerConditionBool(WalkUpTrigger, true));
	MakeTransition(&m_IdleDown, &m_WalkDown, new TriggerConditionBool(WalkDownTrigger, true));
	MakeTransition(&m_IdleLeft, &m_WalkLeft, new TriggerConditionBool(WalkLeftTrigger, true));
	MakeTransition(&m_IdleRight, &m_WalkRight, new TriggerConditionBool(WalkRightTrigger, true));

	//walk to idle
	MakeTransition(&m_WalkUp, &m_IdleUp, new TriggerConditionBool(WalkUpTrigger, false));
	MakeTransition(&m_WalkDown, &m_IdleDown, new TriggerConditionBool(WalkDownTrigger, false));
	MakeTransition(&m_WalkLeft, &m_IdleLeft, new TriggerConditionBool(WalkLeftTrigger, false));
	MakeTransition(&m_WalkRight, &m_IdleRight, new TriggerConditionBool(WalkRightTrigger, false));

	//Down Idle
	MakeTransition(&m_IdleDown, &m_WalkLeft, new TriggerConditionBool(WalkLeftTrigger, true));
	MakeTransition(&m_IdleDown, &m_WalkRight, new TriggerConditionBool(WalkRightTrigger, true));
	MakeTransition(&m_IdleDown, &m_WalkUp, new TriggerConditionBool(WalkUpTrigger, true));

	//Up Idle
	MakeTransition(&m_IdleUp, &m_WalkLeft, new TriggerConditionBool(WalkLeftTrigger, true));
	MakeTransition(&m_IdleUp, &m_WalkRight, new TriggerConditionBool(WalkRightTrigger, true));
	MakeTransition(&m_IdleUp, &m_WalkDown, new TriggerConditionBool(WalkDownTrigger, true));

	//Left Idle
	MakeTransition(&m_IdleLeft, &m_WalkUp, new TriggerConditionBool(WalkUpTrigger, true));
	MakeTransition(&m_IdleLeft, &m_WalkRight, new TriggerConditionBool(WalkRightTrigger, true));
	MakeTransition(&m_IdleLeft, &m_WalkDown, new TriggerConditionBool(WalkDownTrigger, true));

	//Right Idle
	MakeTransition(&m_IdleRight, &m_WalkUp, new TriggerConditionBool(WalkUpTrigger, true));
	MakeTransition(&m_IdleRight, &m_IdleLeft, new TriggerConditionBool(WalkLeftTrigger, true));
	MakeTransition(&m_IdleRight, &m_WalkDown, new TriggerConditionBool(WalkDownTrigger, true));
}

void Player::MakeTransition(IAnimation* From, IAnimation* To, ITriggerCondition* condition)
{
	Transition tansition;
	tansition.SetNextAnimation(To);
	if (condition)
		tansition.AddTrigger(condition);
	(*From).AddTransition(tansition);
}

void Player::Initialize()
{
	MakeAnimation();
	MakeTriggers();

	MakeLinkTransitions();

	m_AnimationSheet = TheAssetManager::Pointer()->GetAsset<SDL_TileSheet>("Media/tilemap_packed.png");
}

void Player::Update()
{
	m_NewPosition = m_Box.Location();
	m_Animator.Update();

	KeyboardState keystate = Keyboard::GetState();
	for (std::pair<Keys, KeyState> k : keystate.GetPressedRepeatKeys())
	{
		switch (k.first)
		{
		case Keys::UP:
		case Keys::w:
		{
			if (k.second == KeyState::Pressed)
			{
				m_Animator.SetBool("WalkUp", true);
				m_AnimationDirection = AnimationDirection::AD_Up;
			}
			else if (k.second == KeyState::Released)
			{
				m_Animator.SetBool("WalkUp", false);
			}
		}
		break;

		case Keys::DOWN:
		case Keys::s:
		{
			if (k.second == KeyState::Pressed)
			{
				m_Animator.SetBool("WalkDown", true);
				m_AnimationDirection = AnimationDirection::AD_Down;
			}
			else if (k.second == KeyState::Released)
			{
				m_Animator.SetBool("WalkDown", false);
			}
		}
		break;

		case Keys::RIGHT:
		case Keys::d:
		{
			if (k.second == KeyState::Pressed)
			{
				m_Animator.SetBool("WalkRight", true);
				m_AnimationDirection = AnimationDirection::AD_Right;
			}
			else if (k.second == KeyState::Released)
			{
				m_Animator.SetBool("WalkRight", false);
			}
		}
		break;

		case Keys::LEFT:
		case Keys::a:
		{
			if (k.second == KeyState::Pressed)
			{
				m_Animator.SetBool("WalkLeft", true);
				m_AnimationDirection = AnimationDirection::AD_Left;
			}
			else if (k.second == KeyState::Released)
			{
				m_Animator.SetBool("WalkLeft", false);
			}
		}
		break;
		}
	}
}

void Player::Draw()
{
	m_AnimationSheet->Draw(m_Animator.GetCurrentFrame(), Rectangle(m_Box.Location(), Size(64,64)));
}


