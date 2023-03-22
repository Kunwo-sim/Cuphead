#pragma once
#include "kwTile.h"
#include "kwImage.h"
#include "kwObject.h"

namespace kw
{
	class TilePalette
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render(HDC hdc);

		static void CreateTile(int index, Vector2 pos);
		static void CreateTiles(int index, UINT width, UINT height);
		static void Save();
		static void Load();

		static Vector2 GetTilePos(Vector2 mousePos);
		static void SetIndex(UINT index) { mIndex = index; }
		static UINT GetIndex() { return mIndex; }

	private:
		static std::unordered_map<UINT64, Tile*> mTiles;
		static Image* mImage;
		static UINT mIndex;

	};
}