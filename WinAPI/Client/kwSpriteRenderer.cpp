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

		for (Image* sprite : mSprites)
		{
			BitBlt(hdc
				, pos.x
				, pos.y
				, sprite->GetWidth()
				, sprite->GetHeight()
				, sprite->GetHdc()
				, 0
				, 0
				, SRCCOPY);

			/*TransparentBlt(hdc
				, pos.x
				, pos.y
				, sprite.GetWidth()
				, sprite.GetHeight()
				, sprite.GetHdc()
				, 0
				, 0
				, sprite.GetWidth()
				, sprite.GetHeight()
				, RGB(255, 0, 255));*/
		}
		
	}

	void SpriteRenderer::Release()
	{

	}
}