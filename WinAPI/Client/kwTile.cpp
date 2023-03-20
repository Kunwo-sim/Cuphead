#include "kwTile.h"
#include "kwTransform.h"
#include "kwCamera.h"

namespace kw
{
	Tile::Tile()
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(-1)
		, mY(-1)
	{
	}

	Tile::Tile(Vector2 pos)
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(-1)
		, mY(-1)
	{
		GetComponent<Transform>()->SetPos(pos);
	}

	Tile::~Tile()
	{
	}

	void Tile::InitializeTile(Image* atlas, int index)
	{
		mIndex = index;
		if (atlas == nullptr || index < 0)
			return;

		mAtlas = atlas;
		SetIndex(index);
	}

	void Tile::SetIndex(int index)
	{
		int maxCol = mAtlas->GetWidth() / TILE_SIZE_X;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE_Y;

		mY = index / maxCol;
		mX = index % maxCol;
	}

	void Tile::Update()
	{
	}

	void Tile::Render(HDC hdc)
	{
		if (mAtlas == nullptr || mIndex < 0)
			return;

		Transform* tr = GetComponent<Transform>();

		Vector2 renderPos = Camera::CalculatePos(tr->GetPos());

		TransparentBlt(hdc
			, renderPos.x, renderPos.y
			, TILE_SIZE_X, TILE_SIZE_Y
			, mAtlas->GetHdc()
			, TILE_SIZE_X * mX, TILE_SIZE_Y * mY
			, TILE_SIZE_X, TILE_SIZE_X
			, RGB(255, 0, 255));
	}

}
