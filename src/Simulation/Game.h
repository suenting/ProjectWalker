#ifndef GAME_H
#define GAME_H
#include "../pch.h"
#include "../UI/Screen.h"
#include "Actor.h"
#include "Stage.h"

enum Direction
{
	D_LEFT,
	D_UP,
	D_RIGHT
};

class Game
{
public:
	static Game& Instance()
	{
		static Game instance;
		return instance;
	}

	~Game();;
	void Render()const;
	void Input(SDL_Event &rSDL_Event);
	void Update();

	// UI
	void EnableScreen(std::string screenname);
	void DisableScreen(std::string screenname);
	void FrontScreen(std::string screenname);
	void ClearScreen();

	Direction GetDirection() const { return mDirection; }
	void SetDirection(Direction val) { mDirection = val; }
	int GetRandom(){return rand();}
	int GetSteps()const{return mStage.GetSteps();}

	bool IsPaused()const{return mbPaused;}
protected:
private:
	Game();
	Game( const Game& other ){};
	Game& operator=( const Game& rhs ){};

	bool mbPaused;

	// UI
	void LoadScreens();
	bool mbGameScreenActive;
	std::vector<Screen*> mActiveScreens;
	std::map<std::string,Screen*> mScreens;

	// Stage
	Stage mStage;

	// Actor
	Actor mActor;

	// direction
	Direction mDirection;

};

#endif