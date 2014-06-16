#ifndef TOGGLE_H
#define TOGGLE_H
#include "Widget.h"
#include "..\Core\Sprite.h"

class Toggle : public Widget
{
public:
	Toggle( std::string path, std::string pathSelected );
	virtual ~Toggle();
	virtual void Render()const;
	virtual bool Input(SDL_Event &rSDL_Event);
	virtual void Update();
	bool IsDown() const { return mbIsDown; }
	void IsDown(bool val) { mbIsDown = val; }
	int GetKey() const { return mKey; }
	void SetKey(int val) { mKey = val; }
	int GetWidth()const{return mpSpriteUp->GetWidth();}
	Math::Vector2f GetDesiredPosition() const { return mDesiredPosition; }
	void SetDesiredPosition(Math::Vector2f val) { mDesiredPosition = val; }
protected:
private:
	Toggle(){};
	int GetSelectedToggle()const;
	Sprite *mpSpriteUp;
	Sprite *mpSpriteDown;
	bool mbIsDown;
	int mKey;
	Math::Vector2f mDesiredPosition;


};

#endif