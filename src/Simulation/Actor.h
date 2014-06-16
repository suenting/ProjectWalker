#ifndef ACTOR_H
#define ACTOR_H
#include "..\Core\AnimatedSprite.h"

class Actor
{
public:
	Actor();
	~Actor();
	void Render()const;
	void Update();
	void IncrementRate();
protected:
private:
	AnimatedSprite *mpLeftSprite;
	AnimatedSprite *mpRightSprite;
	AnimatedSprite *mpUpSprite;

	float mFrame;
	float mFrameRate;
};

#endif