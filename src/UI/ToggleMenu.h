#ifndef TOGGLEMENU_H
#define TOGGLEMENU_H
#include "Widget.h"
#include "Toggle.h"
#include "..\pch.h"


class ToggleMenu : public Widget
{
public:
	ToggleMenu();
	virtual ~ToggleMenu();
	virtual void Render()const;
	virtual bool Input(SDL_Event &rSDL_Event);
	virtual void Update();
	virtual void Init();
	void SelectToggle(size_t idx);
	void AddToggle(Toggle* pToggle);
	void InitKeys();
protected:
private:
	std::vector<Math::Vector2f> mInitialPositions;
	std::vector<Math::Vector2f> mCurrentPositions;
	std::vector<Toggle*> mToggleList;
};

#endif