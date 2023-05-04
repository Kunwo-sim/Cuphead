#pragma once
#include "kwGameObject.h"

namespace kw
{
	class ParryObject : public GameObject
	{
	public:
		ParryObject();
		virtual ~ParryObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner);
		void SetColliderSize(Vector2 size);

	private:
		GameObject* mOwner;
	};
}
