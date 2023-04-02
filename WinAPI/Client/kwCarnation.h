#pragma once
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwAnimator.h"
#include "kwTransform.h"

namespace kw
{
	class Carnation : public GameObject
	{
	public:
		enum class eCarnationState
		{
			Idle,
			Intro,
			FaceAttack,
			FiringSeed,

			// Acorn, ºÎ¸Þ¶û
			SpawnSeed,
		};

		Carnation();
		~Carnation();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void idle();
		void intro();
		void faceAttack();
		void firingSeed();
		void SpawnSeed();

		eCarnationState mState;
		Animator* mAnimator;
		Transform* mTransform;
	};
}

