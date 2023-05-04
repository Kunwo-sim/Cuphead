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
		void BulletLoop();
		void BulletDestroy();

	private:
		GameObject* mBulletDestoryEffect;
		class Sound* mSFX;

		float mTime;
		float mSpeed;
		float mAttackPower;
	};
};