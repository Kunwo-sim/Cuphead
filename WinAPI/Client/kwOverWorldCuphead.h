#pragma once
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwAnimator.h"
#include "kwTransform.h"
#include "kwRigidbody.h"
#include "kwPixelMap.h"

namespace kw
{
	class OverWorldCuphead : public GameObject
	{
	public:
		enum class eOverWorldCupheadState
		{
			Idle,
			Run,
		};

		OverWorldCuphead();
		~OverWorldCuphead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetPixelMap(PixelMap* pixelMap) { mPixelMap = pixelMap; };

	private:
		void idle();
		void run();

		eOverWorldCupheadState mState;
		Transform* mTransform;
		Collider* mCollider;
		Animator* mAnimator;
		Image* mSheetImage;
		PixelMap* mPixelMap;

		float mSpeed;		
	};
}

