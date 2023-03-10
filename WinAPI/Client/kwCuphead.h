#pragma once
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwAnimator.h"
#include "kwTransform.h"

namespace kw
{
	class Cuphead : public GameObject
	{
	public:
		enum class eCupheadState
		{
			Run,
			Shoot,
			Death,
			Idle,
		};

		Cuphead();
		~Cuphead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void run();
		void shoot();
		void death();
		void idle();
		Vector2 DirectionToVector2(eDirection direction);

		eCupheadState mState;
		Animator* mAnimator;
		Transform* mTransform;
		Vector2 mBulletOffset;

		float mSpeed;
		float mAttackCoolTime;
		float mAttackCoolChecker;
	};
}

