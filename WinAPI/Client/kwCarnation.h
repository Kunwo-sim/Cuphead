#pragma once
#include "kwGameObject.h"

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
			Firing,
			// Acorn, ºÎ¸Þ¶û
			Creating,
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
		void firing();
		void creating();
		void idleCallback();

		eCarnationState mState;
		class Animator* mAnimator;
		class Transform* mTransform;
		class Sound* mSFX;

		float mTime;
	};
}

