#include "Toggle.h"
#include "..\Core\ResourceManager.h"
#include "..\Math\Rect2f.h"

namespace
{
	static bool IsClick(int x, int y, int sx,int sy,int sw,int sh)
	{
		Math::Rect2f rect;
		rect.x = ResourceManager::Instance().ScaleTextureWidth(sx);
		rect.y = ResourceManager::Instance().ScaleTextureHeight(sy);
		rect.w = ResourceManager::Instance().ScaleTextureWidth(sw);
		rect.h = ResourceManager::Instance().ScaleTextureHeight(sh);
		if(rect.Intersect(x,y))
		{
			return true;
		}
		return false;
	}
	static const int INTERP_SPEED = 30.f;
}

Toggle::Toggle(std::string path, std::string pathSelected)
{
	mpSpriteUp = new Sprite(path);
	mpSpriteDown = new Sprite(pathSelected);
	mbIsDown = false;
}

Toggle::~Toggle()
{
	delete mpSpriteUp;
	delete mpSpriteDown;
}

void Toggle::Render()const
{
	int x = static_cast<int>(m_position.x);
	int y = static_cast<int>(m_position.y);
	if(IsDown())
	{
		mpSpriteDown->Render(x,y);
	}
	else
	{
		mpSpriteUp->Render(x,y);
	}
}

bool Toggle::Input( SDL_Event &rSDL_Event )
{
	if((SDL_MOUSEBUTTONUP == rSDL_Event.type))
	{
		int idx = 0;
		int x = static_cast<int>(m_position.x);
		int y = static_cast<int>(m_position.y);
		int w = 0;
		int h = 0;
		int px = rSDL_Event.motion.x;
		int py = rSDL_Event.motion.y;
		if(IsDown())
		{
			w = (mpSpriteDown->GetWidth());
			h = (mpSpriteDown->GetHeight());
		}
		else
		{
			w = (mpSpriteUp->GetWidth());
			h = (mpSpriteUp->GetHeight());
		}
		if(IsClick(px,py,x,y,w,h))
		{
			return true;
		}
	}
	return false;
}

void Toggle::Update()
{
	if(m_position.SquaredDistance(mDesiredPosition)< (INTERP_SPEED*INTERP_SPEED))
	{
		m_position = mDesiredPosition;
		return;
	}
	Math::Vector2f dir = mDesiredPosition-m_position;
	dir = dir.NormalizeSelf();
	dir *= INTERP_SPEED;
	m_position = m_position+dir;
}