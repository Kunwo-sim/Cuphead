#pragma once
#include "kwComponent.h"

namespace kw
{
	class Image;

	struct Sprite
	{
		Image* image;
		Vector2 leftTop;
		bool isTransParent;

		Sprite()
			: image(nullptr)
			, leftTop(Vector2::Zero)
			, isTransParent(false)
		{

		}

		Sprite(Image* image, Vector2 leftTop, bool isTransParent)
			: image(image)
			, leftTop(leftTop)
			, isTransParent(isTransParent)
		{

		}
	};

	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void AddSprite(Image* image, Vector2 leftTop, bool isTransParent);

	private:
		std::vector<Sprite> mSprites;
	};
}
