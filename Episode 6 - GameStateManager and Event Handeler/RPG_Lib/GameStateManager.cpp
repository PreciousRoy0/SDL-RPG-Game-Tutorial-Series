#include "GameStateManager.h"

void GameStateManager::SetState(IGameState * gs)
{
	if (m_CurrentState != nullptr)
		m_CurrentState->DeInitialize();

	if (gs != nullptr)
		gs->Initialize();

	m_CurrentState = gs;
}

void GameStateManager::Run()
{
	while (m_CurrentState != nullptr)
	{
		Update();
		Draw();
	}
}

void GameStateManager::Update()
{
	if (m_CurrentState != nullptr)
		m_CurrentState->Update();
}

void GameStateManager::Draw()
{
	if (m_CurrentState != nullptr)
		m_CurrentState->Draw();
}
