#pragma once
#include "kwGameObject.h"
#include "kwTransform.h"
#include "kwCollider.h"
#include "kwAnimator.h"

namespace kw
{
	class OverWorldEntrance : public GameObject
	{
	public:
		OverWorldEntrance();
		virtual ~OverWorldEntrance();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
		virtual void EnterBossMap() = 0;

	protected:
		Transform* mTransform;
		Collider* mCollider;
		Animator* mAnimator;
	};
}
