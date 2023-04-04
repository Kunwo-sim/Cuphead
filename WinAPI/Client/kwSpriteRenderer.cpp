#include "kwSpriteRenderer.h"
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwTransform.h"
#include "kwCamera.h"

namespace kw
{
	SpriteRenderer::SpriteRenderer()
		:Component(eComponentType::SpriteRenderer)
	{

	}

	SpriteRenderer::~SpriteRenderer()
	{

	}

	void SpriteRenderer::Initialize()
	{

	}

	void SpriteRenderer::Update()
	{

	}

	void SpriteRenderer::Render(HDC hdc)
	{
		Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPos();
		pos = Camera::CalculatePos(pos);

		for (Sprite sprite : mSprites)
		{
			if (sprite.isTransParent)
			{
				TransparentBlt(hdc
					, pos.x + sprite.leftTop.x
					, pos.y + sprite.leftTop.y
					, sprite.image->GetWidth()
					, sprite.image->GetHeight()
					, sprite.image->GetHdc()
					, 0
					, 0
					, sprite.image->GetWidth()
					, sprite.image->GetHeight()
					, RGB(255, 0, 255)
				);
			}
			else
			{
				BitBlt(hdc
					, pos.x + sprite.leftTop.x
					, pos.y + sprite.leftTop.y
					, sprite.image->GetWidth()
					, sprite.image->GetHeight()
					, sprite.image->GetHdc()
					, 0
					, 0
					, SRCCOPY);
			}
		}
	}

	void SpriteRenderer::Release()
	{

	}

	void SpriteRenderer::AddSprite(Image* image, Vector2 leftTop, bool isTransParent)
	{
		mSprites.push_back(Sprite(image, leftTop, isTransParent));
	}
}