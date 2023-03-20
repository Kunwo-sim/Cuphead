#pragma once
#include "kwComponent.h"
#include "kwTransform.h"

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
		void SetOffset(Vector2 offset) { mOffset = offset; };
		void SetSize(Vector2 size) { mSize = size; };
		void SetScale(Vector2 scale) { mSize = scale; };
		
		Vector2 GetCenter() { return mCenter; }
		Vector2 GetOffset() { return mOffset; }
		Vector2 GetPos() { return mPos; }
		Vector2 GetSize() { return mSize; }

		UINT GetID() { return mID; }

	private:
		static UINT ColliderNumber;
		UINT mCollisionCount;
		UINT mID;

		Transform* mTransform;
		Vector2 mCenter;
		Vector2 mOffset;
		Vector2 mSize;
		Vector2 mScale;
		Vector2 mPos;
	};
}


