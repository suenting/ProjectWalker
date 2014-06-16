#include "StepCounter.h"
#include "..\Core\FontManager.h"
#include "..\Simulation\Game.h"

StepCounter::StepCounter()
{

}

StepCounter::~StepCounter()
{

}

void StepCounter::Render() const
{
	char buffer [4];
	sprintf(buffer,"%d",Game::Instance().GetSteps());
	FontManager::Instance().RenderText("airstrike",std::string(buffer),m_position.x,m_position.y);
}

void StepCounter::Update()
{

}

