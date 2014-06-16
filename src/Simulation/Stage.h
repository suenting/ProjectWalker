#ifndef STAGE_H
#define STAGE_H

#include "..\Math\Vector2f.h"
#include "..\pch.h"
#include "..\Core\Sprite.h"

enum TileDirection
{
	TD_UP,
	TD_LEFT,
	TD_RIGHT
};
enum TileType
{
	TT_PLAIN,
	TT_DIRT,
	TT_WOOD,
	TT_GRASS,
	TT_STONE,
	TT_WALL
};
struct Tile 
{
	TileDirection mDirection;
	TileType mType;
	Math::Vector2f mPosition;
};
class Stage
{
public:
	Stage();
	~Stage();
	void Render()const;
	void Update();
	void Init();

	Math::Vector2f GetNextTilePos()const;
	bool IsOnStage()const;
	void IncrementRate();
	void IncrementTileType();
	int GetSteps()const;
protected:
private:
	std::vector<Sprite*> mStageSprites;
	std::vector<Tile> mTiles;
	Math::Vector2f mShift;
	Sprite* mBackgroundSprite;
	int mCurrentTile;
	float mRate;
};

#endif