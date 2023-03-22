#include "kwTilePalette.h"
#include "kwResources.h"
#include "kwInput.h"

namespace kw
{
	Image* TilePalette::mImage = nullptr;
	std::unordered_map<UINT64, Tile*> TilePalette::mTiles = {};
	UINT TilePalette::mIndex = -1;

	void TilePalette::Initiailize()
	{
		mImage = Resources::Find<Image>(L"TileAtlas");
	}

	void TilePalette::Update()
	{
	}

	void TilePalette::Render(HDC hdc)
	{
	}

	void TilePalette::CreateTile(int index, Vector2 pos)
	{
		Tile* test = object::Instantiate<Tile>(eLayerType::Tile);
		test->InitializeTile(mImage, index);


		Vector2 tilePos(pos.x * TILE_SIZE_X, pos.y * TILE_SIZE_Y);
		test->GetComponent<Transform>()->SetPos(tilePos);

	}

	void TilePalette::CreateTiles(int index, UINT width, UINT height)
	{

	}

	void TilePalette::Save()
	{
	}

	void TilePalette::Load()
	{
	}

	Vector2 TilePalette::GetTilePos(Vector2 mousePos)
	{
		int indexY = mousePos.y / TILE_SIZE_Y;
		int indexX = mousePos.x / TILE_SIZE_X;

		return Vector2(indexX, indexY);
	}

}
