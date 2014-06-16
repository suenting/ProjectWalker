#include "Game.h"
#include "..\Core\ResourceManager.h"
#include "..\UI\ScreenDefs.h"

namespace
{
	static int TICKS=1;
	static const int SPEEDUPRATE=300;
}

Game::Game()
{
	srand(time(NULL));
	LoadScreens();
	mbGameScreenActive = false;
	mbPaused = false;
}
Game::~Game()
{
	for(std::map<std::string,Screen*>::iterator it = mScreens.begin(); it != mScreens.end();++it)
	{
		delete (it->second);
	}
}
void Game::Render() const
{
	if(mbGameScreenActive)
	{
		SDL_SetRenderDrawColor(ResourceManager::Instance().GetRenderer(), 0x00, 0x00, 0x00, 0xFF);
	}
	else
	{
		SDL_SetRenderDrawColor(ResourceManager::Instance().GetRenderer(), 0x00, 0x00, 0x00, 0xFF);
	}
	SDL_RenderClear(ResourceManager::Instance().GetRenderer());

	// draw game here
	
	if(mbGameScreenActive)
	{
		// draw stage
		mStage.Render();

		// draw actor
		mActor.Render();
	}

	// draw screens / UI
	for(std::vector<Screen*>::const_iterator it = mActiveScreens.begin(); it != mActiveScreens.end();++it)
	{
		(*it)->Render();
	}
}

void Game::Update()
{
	if(mbGameScreenActive &&!mbPaused)
	{
		mStage.Update();
		mActor.Update();
		if(!mStage.IsOnStage())
		{
			//ClearScreen();
			mbPaused = true;
			EnableScreen("lose");
		}
		if(0 == (TICKS%SPEEDUPRATE))
		{
			mActor.IncrementRate();
			mStage.IncrementRate();
		}
		++TICKS;
	}
	for(std::vector<Screen*>::const_iterator it = mActiveScreens.begin(); it != mActiveScreens.end();++it)
	{
		(*it)->Update();
	}
}


void Game::LoadScreens()
{
	mScreens["splash"]=SplashScreen();
	mScreens["main"]=MainMenu();
	mScreens["game"]=GameScreen();
	mScreens["win"]=WinScreen();
	mScreens["lose"]=LoseScreen();
	EnableScreen("main");
}

void Game::EnableScreen( std::string screenname )
{
	mActiveScreens.push_back(mScreens[screenname]);
	if("game"==screenname)
	{
		mbGameScreenActive= true;
		mStage.Init();
		mScreens["game"]->Init();
		mbPaused = false;
	}
}

void Game::DisableScreen( std::string screenname )
{
	std::vector<Screen*>::iterator position = std::find(mActiveScreens.begin(), mActiveScreens.end(), mScreens[screenname]);
	if (position != mActiveScreens.end())
	{
		mActiveScreens.erase(position);
	}
	if("game"==screenname){mbGameScreenActive= false;}
}

void Game::FrontScreen( std::string screenname )
{
	DisableScreen(screenname);
	EnableScreen(screenname);
}

void Game::ClearScreen()
{
	mActiveScreens.clear();
	mbGameScreenActive= false;
}

void Game::Input( SDL_Event &rSDL_Event )
{
	// poll controller input
	//InputManager::Instance().ControllerInputEvent(rSDL_Event);

	// top level widgets first
	for(std::vector<Screen*>::const_iterator it = mActiveScreens.begin(); it != mActiveScreens.end();++it)
	{
		if((*it)->Input(rSDL_Event))
		{
			return;
		}
	}
}