#pragma once
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwAnimator.h"

namespace kw
{
	class Cuphead : public GameObject
	{
	public:
		enum class eCupheadState
		{
			Move,
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
		void move();
		void shoot();
		void death();
		void idle();

		eCupheadState mState;
		Animator* mAnimator;
	};
}

