#pragma once
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwAnimator.h"
#include "kwTransform.h"
#include "kwRigidbody.h"
#include "kwPixelMap.h"
#include "kwSpriteRenderer.h"

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

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
		void SetPixelMap(PixelMap* pixelMap) { mPixelMap = pixelMap; };

	private:
		void idle();
		void run();

		eOverWorldCupheadState mState;

		Image* mSheetImage;
		Image* mEnterBoxImage;
		PixelMap* mPixelMap;
		class OverWorldEntrance* mEntrance;

		float mSpeed;
		bool mIsOverlapEntrance;
	};
}

