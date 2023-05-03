#pragma once
#include "kwGameObject.h"
#include "kwAnimator.h"

namespace kw
{
	class SpreadShot : public GameObject
	{
	public:
		SpreadShot();
		~SpreadShot();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		void BulletLoop();
		void BulletDestroy();
		void SetSpreadDirection(int direction);
		void SetDirectionFlip();

	private:
		GameObject* mBulletDestoryEffect;
		GameObject* mBulletHitEffect;

		float mTime;
		float mSpeed;
		float mAttackPower;
		Vector2 mDirection;
	};
};