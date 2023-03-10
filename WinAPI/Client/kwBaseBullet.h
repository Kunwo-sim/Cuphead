#pragma once
#include "kwGameObject.h"
#include "kwAnimator.h"

namespace kw
{
	class BaseBullet : public GameObject
	{
	public:
		BaseBullet();
		~BaseBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		//virtual void OnCollisionStay(class Collider* other);
		//virtual void OnCollisionExit(class Collider* other);

	private:
		Animator* mAnimator;

		float mTime;
		float mSpeed;
	};
};