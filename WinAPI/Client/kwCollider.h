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

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetCenter(Vector2 center) { mCenter = center; };
		void SetSize(Vector2 size) { mSize = size; };
		void SetScale(Vector2 scale) { mSize = scale; };
		Vector2 GetPos() { return mPos; }
		Vector2 GetSize() { return mSize; }
		UINT GetID() { return mID; }

	private:
		static UINT ColliderNumber;
		UINT mID;
		Vector2 mCenter;
		Vector2 mSize;
		Vector2 mScale;
		Vector2 mPos;
	};
}


