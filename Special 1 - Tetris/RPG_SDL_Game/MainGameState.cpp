#include "MainGameState.h"

#include "Console_Screen.h"
#include "Console_Timer.h"
#include "Keyboard.h"

void MainGameState::Initialize()
{
	system("CLS");

	m_GameBounds.X = 1;
	m_GameBounds.Y = 1;
	m_GameBounds.Height = 20;
	m_GameBounds.Width = 10;
	TheConsoleScreen::Pointer()->SetDrawRect(m_GameBounds);

	m_NextBox.X = 15;
	m_NextBox.Y = 1;
	m_NextBox.Height = 6;
	m_NextBox.Width = 6;
	TheConsoleScreen::Pointer()->SetDrawRect(m_NextBox);
	
	m_CurrentBlock.GenerateRandomBlock();
	m_NextBlock.GenerateRandomBlock();

	//m_StartPosition.X = (m_GameBounds.X + (m_GameBounds.Width / 2)) - (m_CurrentBlock.GetWidth() / 2);
	//m_StartPosition.Y = 3;

	m_CurrentBlock.Draw(true);
	m_NextBlock.Draw(true);
}

int speed = 5;

void MainGameState::StopTetrisBlock()
{
	//destroy current block
	std::vector<Block> b = m_CurrentBlock.Destroy();
	m_GameBlocks.insert(std::end(m_GameBlocks), std::begin(b), std::end(b));

	//reset current block
	m_NextBlock.Clear();
	m_CurrentBlock = m_NextBlock;
	m_CurrentBlock.SetPosition2(PointF(6, 2));

	//make new next block
	m_NextBlock = TetrisBlock(PointF(18, 3));
	m_NextBlock.GenerateRandomBlock();
	m_NextBlock.Draw(true);

	speed = 5;
}

void MainGameState::Update()
{
	bool updatePosX = true;
	bool updatePosY = true;
	m_NewPosition = m_CurrentBlock.GetPosition();
	
	Keyboard keyboard = Keyboard::GetState();
	//Move right
	if (keyboard.KeyPressed(Keys::RIGHT))
		m_NewPosition.X += 1;
	//Move Left
	if (keyboard.KeyPressed(Keys::LEFT))
		m_NewPosition.X -= 1;
	//move faster
	if (keyboard.KeyPressed(Keys::DOWN))
		speed = 20;
	//Rotate
	if (keyboard.KeyPressed(Keys::SPACE))
		m_CurrentBlock.Rotate();

	//calculate new position
	m_NewPosition.Y += speed * Console_Timer::GetDT();
	
	//Collide with wall Left
	if (m_NewPosition.X + m_CurrentBlock.RelativeXMin() < m_GameBounds.X + 1)
		updatePosY = false;
	//Collide with wall Right
	else if (m_NewPosition.X + m_CurrentBlock.RelativeXMax() > (m_GameBounds.X + m_GameBounds.Width))
		updatePosY = false;

	//Collide with Bottom
	if ((int)(m_NewPosition.Y + m_CurrentBlock.RelativeYMax()) == (m_GameBounds.Y + m_GameBounds.Height) + 1)
	{
		StopTetrisBlock();
		updatePosY = false;
		return;
	}
	
	TetrisBlock tmp = m_CurrentBlock;
	tmp.SetPosition(m_NewPosition);
	//Collide with other boxes
	for (int i = 0; i < m_GameBlocks.size(); i++)
	{
		if (tmp.Colliding(m_GameBlocks[i]))
		{
			StopTetrisBlock();
			updatePosY = false;
			return;
		}
	}

	//Check if row complete
		//-Delete row
		//-Update Score
		//-Setup new block

	//set new position
	if(updatePosX && updatePosY)
		m_CurrentBlock.SetPosition(m_NewPosition);
	else if (updatePosY)
		m_CurrentBlock.SetPosition(PointF(m_CurrentBlock.GetPosition().X, m_NewPosition.Y));
}

void MainGameState::Draw()
{
	m_CurrentBlock.Draw();

	for (int i = 0; i < m_GameBlocks.size(); i++)
	{
		m_GameBlocks[i].Draw();
	}
}

void MainGameState::DeInitialize()
{

}

