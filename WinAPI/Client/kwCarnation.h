#pragma once
#include "kwGameObject.h"

namespace kw
{
	class Carnation : public GameObject
	{
	public:
		enum class eCarnationState
		{
			Intro,
			Idle,
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
		void creatingStartCallback();
		void firingStartCallback();
		void firingLoopCallback();

		eCarnationState mState;
		class Sound* mSFX;

		int mLoopCount;
		float mTime;
	};
}

