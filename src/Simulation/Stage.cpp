#include "Stage.h"
#include "Game.h"
#include "..\Math\Rect2f.h"

namespace
{
	static size_t tick=0;
	//static float rate= 0.5f;
	//static float mRate= 5.f;

	static const int TILE_WIDTH=100*2;
	static const int TILE_HEIGHT=70*2;
	static const int ADJ_TILE_LEFT = 50*2;
	static const int ADJ_TILE_UP = 35*2;
	static int SWITCH = 0;
	static const int SWITCH_RATE = 2;

	static int SAME_DIR_COUNT = 0;
	static const int MAX_SWITCH_RATE = 4;
	static int LAST_DIR=1;
	static const int INITIAL_TILE=8;

	static int SWITCH_TILE_TYPE_RATE = 30;
	static TileType CURRENT_TILE_TYPE= TT_PLAIN;
}

Stage::Stage()
{
	// load sprites
	mStageSprites.push_back(new Sprite("plain.png"));
	mStageSprites.push_back(new Sprite("dirt.png"));
	mStageSprites.push_back(new Sprite("wood.png"));
	mStageSprites.push_back(new Sprite("grass.png"));
	mStageSprites.push_back(new Sprite("stone.png"));
	mStageSprites.push_back(new Sprite("wall.png"));
	mTiles.resize(32);
	mBackgroundSprite = new Sprite("water.png");
}

Stage::~Stage()
{
	delete mBackgroundSprite;
	for(std::vector<Sprite*>::iterator it = mStageSprites.begin(); it != mStageSprites.end();++it)
	{
		delete *it;
	}
}

void Stage::Init()
{
	mCurrentTile = INITIAL_TILE;
	int x = 270;
	int y = 400+16*70;
	for(std::vector<Tile>::iterator it = mTiles.begin(); it != mTiles.end();++it)
	{
		it->mPosition.x=x;
		it->mPosition.y=y;
		it->mType = TT_PLAIN;
		it->mDirection = TD_UP;
		y-=TILE_HEIGHT;
	}

	// generate tiles 5x after start.
	for(int it = mCurrentTile+5; it<32;++it)
	{
		{
			int next = it;
			int last = it-1;
			mTiles[next].mPosition = mTiles[last].mPosition;
			int nextDir = LAST_DIR;
			if( 0 == (SWITCH%SWITCH_RATE))
			{
				if( 0==(SAME_DIR_COUNT % MAX_SWITCH_RATE))
				{
					switch(mTiles[last].mDirection)
					{
					case TD_LEFT:
					case TD_RIGHT:
						nextDir = 1;
						break;
					case TD_UP:
						nextDir = Game::Instance().GetRandom()%2;
						if(1==nextDir){nextDir = 2;}
						break;
					}
				}
				else
				{
					switch(mTiles[last].mDirection)
					{
					case TD_LEFT:
						nextDir = Game::Instance().GetRandom()%2;
						break;
					case TD_UP:
						nextDir = Game::Instance().GetRandom()%3;
						break;
					case TD_RIGHT:
						nextDir = Game::Instance().GetRandom()%2+1;
						break;
					}
				}

			}
			LAST_DIR = nextDir;
			if(nextDir==LAST_DIR)
			{
				++SAME_DIR_COUNT;
			}
			else
			{
				SAME_DIR_COUNT=1;
			}
			++SWITCH;

			switch(nextDir)
			{
			case 0:
				mTiles[next].mPosition.x-=TILE_WIDTH;
				mTiles[next].mDirection=TD_LEFT;
				break;
			case 1:
				mTiles[next].mPosition.y-=TILE_HEIGHT;
				mTiles[next].mDirection=TD_UP;
				break;
			case 2:
				mTiles[next].mPosition.x+=TILE_WIDTH;
				mTiles[next].mDirection=TD_RIGHT;
				break;
			}
		}
	}

	mShift.x = 0;
	mShift.y = 0;
	mRate = 5.f;
}

void Stage::Render() const
{
	mBackgroundSprite->Render(0,0);
	int it = (mCurrentTile+32-INITIAL_TILE)-1;
	int et = it-32;
	for(;it!=et;--it)
	{
		int idx = it % 32;
		mStageSprites[mTiles[idx].mType]->RenderCenter(static_cast<int>(mTiles[idx].mPosition.x+mShift.x), static_cast<int>(mTiles[idx].mPosition.y+mShift.y));
	}
}

void Stage::Update()
{
	++tick;
	
	Direction dir = Game::Instance().GetDirection();
	switch(dir)
	{
	case D_LEFT:
		mShift.x+=mRate;
		break;
	case D_UP:
		mShift.y+=mRate;
		break;
	case D_RIGHT:
		mShift.x-=mRate;
		break;
	}

	float sqDist = GetNextTilePos().SquaredDistance(Math::Vector2f(270,400));
	if(sqDist<20000.f)
	{
		int next = (mCurrentTile + (32-INITIAL_TILE))%32;
		int last = (mCurrentTile + (32-INITIAL_TILE-1))%32;
		mTiles[next].mPosition = mTiles[last].mPosition;
		int nextDir = LAST_DIR;
		if( 0 == (SWITCH%SWITCH_RATE))
		{
			if( 0==(SAME_DIR_COUNT % MAX_SWITCH_RATE))
			{
				switch(mTiles[last].mDirection)
				{
				case TD_LEFT:
				case TD_RIGHT:
					nextDir = 1;
					break;
				case TD_UP:
					nextDir = Game::Instance().GetRandom()%2;
					if(1==nextDir){nextDir = 2;}
					break;
				}
			}
			else
			{
				switch(mTiles[last].mDirection)
				{
				case TD_LEFT:
					nextDir = Game::Instance().GetRandom()%2;
					break;
				case TD_UP:
					nextDir = Game::Instance().GetRandom()%3;
					break;
				case TD_RIGHT:
					nextDir = Game::Instance().GetRandom()%2+1;
					break;
				}
			}

		}
		if(nextDir==LAST_DIR)
		{
			++SAME_DIR_COUNT;
		}
		else
		{
			SAME_DIR_COUNT=1;
		}
		LAST_DIR = nextDir;
		++SWITCH;

		switch(nextDir)
		{
		case 0:
			mTiles[next].mPosition.x-=TILE_WIDTH;
			mTiles[next].mDirection=TD_LEFT;
			break;
		case 1:
			mTiles[next].mPosition.y-=TILE_HEIGHT;
			mTiles[next].mDirection=TD_UP;
			break;
		case 2:
			mTiles[next].mPosition.x+=TILE_WIDTH;
			mTiles[next].mDirection=TD_RIGHT;
			break;
		}
		mTiles[next].mType=CURRENT_TILE_TYPE;
		++mCurrentTile;

		if(0==(mCurrentTile % SWITCH_TILE_TYPE_RATE))
		{
			IncrementTileType();
		}
	}
}

Math::Vector2f Stage::GetNextTilePos() const
{
	int idx = (mCurrentTile+1)%32;
	Math::Vector2f ret = mTiles[idx].mPosition;
	ret.x += mShift.x;
	ret.y += mShift.y;
	return ret;
}

bool Stage::IsOnStage() const
{
	Math::Vector2f pos = Math::Vector2f(270,400);
	Math::Rect2f actor;

	actor.w = 8;
	actor.h = 25;
	actor.x = 270-static_cast<int>(actor.w/2);
	actor.y = 400-static_cast<int>(actor.h/2);
	for(std::vector<Tile>::const_iterator it = mTiles.begin(); it != mTiles.end();++it)
	{
		Math::Rect2f tile;
		tile.x = it->mPosition.x-ADJ_TILE_LEFT+mShift.x;
		tile.y = it->mPosition.y-ADJ_TILE_UP+mShift.y;
		tile.w = TILE_WIDTH;
		tile.h = TILE_HEIGHT;

		if(actor.Intersect(tile))
		{
			return true;
		}
	}
	return false;
}

void Stage::IncrementRate()
{
	mRate += 2.5f;
}

int Stage::GetSteps() const
{
	return mCurrentTile-INITIAL_TILE;
}

void Stage::IncrementTileType()
{
	CURRENT_TILE_TYPE = static_cast<TileType>((static_cast<int>(CURRENT_TILE_TYPE)+1)%6);
}

