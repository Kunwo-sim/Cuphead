#pragma once
#include "kwGameObject.h"

namespace kw
{
	class Ring : public GameObject
	{
	public:
		Ring();
		virtual ~Ring();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetDir(Vector2 dir) { mDirection = dir; };

	private:
		float mSpeed;
		Vector2 mDirection;
	};
}
