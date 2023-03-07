#pragma once
#include "kwComponent.h"

namespace kw
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetCenter(Vector2 center) { mCenter = center; };
		void SetSize(Vector2 size) { mSize = size; };
		void SetScale(Vector2 scale) { mSize = scale; };
		Vector2 GetPos() { return mPos; }
		Vector2 GetSize() { return mSize; }

	private:
		Vector2 mCenter;
		Vector2 mSize;
		Vector2 mScale;
		Vector2 mPos;
	};
}


