#include "Actor.h"
#include "Game.h"

Actor::Actor()
{
mpLeftSprite = new AnimatedSprite();
mpLeftSprite->LoadSprite("tkl%d.png",1,3);
mpRightSprite = new AnimatedSprite();
mpRightSprite->LoadSprite("tkr%d.png",1,3);
mpUpSprite = new AnimatedSprite();
mpUpSprite->LoadSprite("tku%d.png",1,3);
mFrame = 0;
mFrameRate = .25f;
}

Actor::~Actor()
{
	delete mpLeftSprite;
	delete mpRightSprite;
	delete mpUpSprite;
}

void Actor::Render() const
{
	int frame = static_cast<int>(mFrame)%3;
	Direction dir = Game::Instance().GetDirection();
	switch(dir)
	{
	case D_LEFT:
		mpLeftSprite->RenderCentered(270,400,frame);
		break;
	case D_UP:
		mpUpSprite->RenderCentered(270,400,frame);
		break;
	case D_RIGHT:
		mpRightSprite->RenderCentered(270,400,frame);
		break;
	}
}

void Actor::Update()
{
	mFrame +=mFrameRate;
}

void Actor::IncrementRate()
{
	mFrameRate += 0.05f;
}

