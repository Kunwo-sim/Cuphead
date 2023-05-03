#pragma once
#include "kwGameObject.h"

namespace kw
{
	class FlowerPlatform : public GameObject
	{
	public:
		enum class PlatformType
		{
			A,
			B,
			C
		};

		FlowerPlatform();
		virtual ~FlowerPlatform();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlatformType(PlatformType type) { mPlatformType = type; };
		void PlayPlatformAnim();

	private:
		class Transform* mTransform;
		class Collider* mCollider;
		class Animator* mAnimator;
		class Ground* mGround;
		PlatformType mPlatformType;

		GameObject* mPropellor;
		Vector2 mPropllerOffset;
	};
}
