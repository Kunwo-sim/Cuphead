#include "kwPixelMap.h"
#include "kwResources.h"
#include "kwImage.h"
#include "kwSpriteRenderer.h"

namespace kw
{
	PixelMap::PixelMap()
	{

	}

	PixelMap::~PixelMap()
	{

	}

	void PixelMap::Initialize()
	{
		mSR = AddComponent<SpriteRenderer>();
		mPixelMapImage = Resources::Load<Image>(L"Stage1PixelMap", L"..\\Resources\\OverWorld\\Stage1PixelMap.bmp");
		mSR->AddSprite(mPixelMapImage, Vector2::Zero, false);

		GameObject::Initialize();
	}

	void PixelMap::Update()
	{
		GameObject::Update();
	}

	void PixelMap::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PixelMap::Release()
	{

	}

	bool PixelMap::PixelMovableCheck(Vector2 pos)
	{
		COLORREF nextPixel = mPixelMapImage->GetPixel(pos.x + 1 , pos.y - 1);
		if (nextPixel == RGB(255, 0, 255))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}