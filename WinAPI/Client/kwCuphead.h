#pragma once
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwAnimator.h"
#include "kwTransform.h"
#include "kwRigidbody.h"

namespace kw
{
	class Cuphead : public GameObject
	{
	public:
		enum class eCupheadState
		{
			Idle,
			Shoot,
			Run,
			RunShoot,
			Duck,
			DuckShoot,
			Jump,
			JumpShoot,
			Death,
		};

		Cuphead();
		~Cuphead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void idle();
		void shoot();
		void run();
		void runShoot();
		void duck();
		void duckShoot();
		void jump();
		void death();
		
		void playCupheadAnim(std::wstring State, bool loop = true);
		void CupheadMove();
		void CreateBullet();
		void SetStateJump();

		Vector2 DirectionToVector2(eDirection direction);

		eCupheadState mState;
		Transform* mTransform;
		Collider* mCollider;
		Rigidbody* mRigidbody;
		Animator* mAnimator;

		Vector2 mBulletOffset;

		float mSpeed;
		float mAttackCoolTime;
		float mAttackCoolChecker;
	};
}

