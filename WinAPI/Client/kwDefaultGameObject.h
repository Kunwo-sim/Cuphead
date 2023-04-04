#pragma once
#include "kwGameObject.h"

namespace kw
{
	class DefaultGameObject : public GameObject
	{
	public:
		DefaultGameObject();
		virtual ~DefaultGameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		class Transform* mTransform;
		class Collider* mCollider;
		class Animator* mAnimator;
	};
}
