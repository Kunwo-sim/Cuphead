#pragma once
#include "kwCharacter.h"

namespace kw
{
	class Cuphead : public Character
	{
	public:
		enum class eCupheadState
		{
			Intro,
			Idle,
			Shoot,
			Run,
			RunShoot,
			Duck,
			DuckShoot,
			Jump,
			Dash,
			Hit,
			Death,
		};

		Cuphead();
		~Cuphead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void Hit();
		void GroundExit();
		void CreateBullet();
		void SetStateJump();
		void IdleCallback();

	private:
		void idle();
		void shoot();
		void run();
		void runShoot();
		void duck();
		void duckShoot();
		void jump();
		void dash();
		void death();
		void move();
		void playCupheadAnim(std::wstring State, bool loop = true);
		

		eCupheadState mState;
		class Sound* mBulletSound;

		Vector2 mBulletOffset;

		float mSpeed;
		float mAttackCoolTime;
		float mAttackCoolChecker;
		float mHitBlinkCoolTime;
		float mHitBlinkCoolChecker;
		bool mIsBlink;
	};
}

