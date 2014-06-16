#include "ToggleMenu.h"
#include "..\Simulation\Game.h"

namespace
{
	static const int RANDOM_RATE=200;
	static int TICKS=0;
}

ToggleMenu::ToggleMenu()
{

}

ToggleMenu::~ToggleMenu()
{
	for(std::vector<Toggle*>::iterator it=mToggleList.begin(); it != mToggleList.end(); ++it)
	{
		delete *it;
	}
}

void ToggleMenu::Render() const
{
	for(std::vector<Toggle*>::const_iterator it=mToggleList.begin(); it != mToggleList.end(); ++it)
	{
		(*it)->Render();
	}
}

bool ToggleMenu::Input( SDL_Event &rSDL_Event )
{
	int idx = 0;
	for(std::vector<Toggle*>::iterator it=mToggleList.begin(); it != mToggleList.end(); ++it)
	{
		Toggle* pToggle = *it;
		if(pToggle->Input(rSDL_Event))
		{
			SelectToggle(idx);
		}
		++idx;
	}
	return false;
}

void ToggleMenu::AddToggle( Toggle* pToggle )
{
	float x = (m_position.x);
	float y = (m_position.y);
	for(std::vector<Toggle*>::const_iterator it=mToggleList.begin(); it != mToggleList.end(); ++it)
	{
		x+=(*it)->GetWidth();
	}
	pToggle->SetPosition(Math::Vector2f(x,y));
	mInitialPositions.push_back(Math::Vector2f(x,y));
	mCurrentPositions.push_back(Math::Vector2f(x,y));
	mToggleList.push_back(pToggle);

}

void ToggleMenu::SelectToggle( size_t idx )
{
	for(std::vector<Toggle*>::iterator it=mToggleList.begin(); it != mToggleList.end(); ++it)
	{
		(*it)->IsDown(false);
	}
	mToggleList[idx]->IsDown(true);
}

void ToggleMenu::Update()
{
	for(std::vector<Toggle*>::iterator it=mToggleList.begin(); it != mToggleList.end(); ++it)
	{
		Toggle *pToggle = *it;
		pToggle->Update();
		if(pToggle->IsDown())
		{
			Game::Instance().SetDirection(static_cast<Direction>(pToggle->GetKey()));
		}
	}
	if(!Game::Instance().IsPaused())
	{
		++TICKS;
	}
	if(0==(TICKS%RANDOM_RATE))
	{
		std::random_shuffle(mCurrentPositions.begin(),mCurrentPositions.end());
		size_t i = 0;
		for(std::vector<Toggle*>::iterator it=mToggleList.begin(); it != mToggleList.end(); ++it)
		{
			(*it)->SetDesiredPosition(mCurrentPositions[i]);
			++i;
		}
	}
}

void ToggleMenu::InitKeys()
{
	int idx = 0;
	for(std::vector<Toggle*>::iterator it=mToggleList.begin(); it != mToggleList.end(); ++it)
	{
		Toggle *pToggle = *it;
		pToggle->SetKey(idx);
		++idx;
	}
}

void ToggleMenu::Init()
{
	SelectToggle(1);
	size_t i = 0;
	for(std::vector<Toggle*>::iterator it=mToggleList.begin(); it != mToggleList.end(); ++it)
	{
		(*it)->SetPosition(mInitialPositions[i]);
		(*it)->SetDesiredPosition(mInitialPositions[i]);
		++i;
	}
}

