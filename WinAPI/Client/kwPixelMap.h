#pragma once
#include "kwGameObject.h"
namespace kw
{
	class PixelMap : public GameObject
	{
	public:
		PixelMap();
		virtual ~PixelMap();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		bool PixelMovableCheck(Vector2 pos);

	private:
		class SpriteRenderer* mSR;
		class Image* mPixelMapImage;
	};
}


