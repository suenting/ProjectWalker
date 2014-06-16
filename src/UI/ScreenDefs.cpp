#include "ScreenDefs.h"
#include "../Core/FontManager.h"
#include "Label.h"
#include "Button.h"
#include "../Simulation/Game.h"
#include "Menu.h"
#include "ToggleMenu.h"
#include "Toggle.h"
#include "StepCounter.h"

// navigation
namespace
{
	static void GoToMainMenu()
	{
		Game::Instance().ClearScreen();
		Game::Instance().EnableScreen("main");
		//Game::Instance().EndGame();
	}
	static void GoToGameScreen()
	{
		Game::Instance().ClearScreen();
		Game::Instance().EnableScreen("game");
		//Game::Instance().InitGame();
	}
	static void GoToWinScreen()
	{
		Game::Instance().ClearScreen();
		Game::Instance().EnableScreen("win");
		//Game::Instance().EndGame();
	}
	static void GoToLoseScreen()
	{
		Game::Instance().ClearScreen();
		Game::Instance().EnableScreen("lose");
		//Game::Instance().EndGame();
	}
	static void ExitGame()
	{
		exit(0);
	}
}

Screen* SplashScreen()
{
	Screen * screen = new Screen();

	Button* pButton = new Button();
	SDL_Color white = {255,255,255};
	pButton->SetText(FontManager::Instance().GetFont("script"),"Project Fairy",white);
	pButton->SetPosition(Math::Vector2f(300.f,180.f));
	pButton->SetCallback(&GoToMainMenu);
	screen->AddWidget(pButton);

	return screen;
}
Screen* WinScreen()
{
	Screen * screen = new Screen();

	Button* pButton = new Button();
	SDL_Color white = {255,255,255};
	pButton->SetText(FontManager::Instance().GetFont("airstrike"),"YOU WIN",white);
	pButton->SetPosition(Math::Vector2f(120.f,350.f));
	pButton->SetCallback(&GoToMainMenu);
	screen->AddWidget(pButton);

	return screen;
}
Screen* LoseScreen()
{
	Screen * screen = new Screen();
	SDL_Color white = {255,255,255};

	Label* pLabel1 = new Label();
	pLabel1->SetImage("fade.png");
	pLabel1->SetPosition(Math::Vector2f(0.f,350.f));
	screen->AddWidget(pLabel1);

	Button* pButton = new Button();
	pButton->SetText(FontManager::Instance().GetFont("airstrike"),"YOU DIED",white);
	pButton->SetPosition(Math::Vector2f(120.f,350.f));
	pButton->SetCallback(&GoToMainMenu);
	screen->AddWidget(pButton);

	return screen;
}

Screen* MainMenu()
{
	Screen * screen = new Screen();
	SDL_Color white = {255,255,255};

	Label* pLabel1 = new Label();
	pLabel1->SetText(FontManager::Instance().GetFont("orange"),"TK's",white);
	pLabel1->SetPosition(Math::Vector2f(175.f,25.f));
	screen->AddWidget(pLabel1);
	Label* pLabel2 = new Label();
	pLabel2->SetText(FontManager::Instance().GetFont("orange"),"Walkabout",white);
	pLabel2->SetPosition(Math::Vector2f(25.f,100.f));
	screen->AddWidget(pLabel2);

	Button* pButton = new Button();
	pButton->SetText(FontManager::Instance().GetFont("orange"),"Start Game",white);
	pButton->SetPosition(Math::Vector2f(25.f,700.f));
	pButton->SetCallback(&GoToGameScreen);
	screen->AddWidget(pButton);

	Button* pExit = new Button();
	pExit->SetText(FontManager::Instance().GetFont("orange"),"Exit",white);
	pExit->SetPosition(Math::Vector2f(25.f,800.f));
	pExit->SetCallback(&ExitGame);
	screen->AddWidget(pExit);
	return screen;
}

Screen* GameScreen()
{
	Screen * screen = new Screen();

	Button * pBack = new Button();
	pBack->SetImage("back.png");
	pBack->SetPosition(Math::Vector2f(10,10));
	pBack->SetCallback(&GoToMainMenu);
	screen->AddWidget(pBack);

	StepCounter * pStepCounter = new StepCounter();
	pStepCounter->SetPosition(Math::Vector2f(400,10));
	screen->AddWidget(pStepCounter);

	ToggleMenu * pToggleMenu = new ToggleMenu();
	pToggleMenu->SetPosition(Math::Vector2f(5.f,750.f));
	pToggleMenu->AddToggle(new Toggle("bleft.png","yleft.png"));
	pToggleMenu->AddToggle(new Toggle("bup.png","yup.png"));
	pToggleMenu->AddToggle(new Toggle("bright.png","yright.png"));
	pToggleMenu->InitKeys();
	pToggleMenu->SelectToggle(1);
	screen->AddWidget(pToggleMenu);
	
	return screen;
}