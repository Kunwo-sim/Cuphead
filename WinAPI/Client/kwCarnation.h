#pragma once
#include "kwMonster.h"

namespace kw
{
	class Carnation : public Monster
	{
	public:
		enum class eCarnationState
		{
			Intro,
			Idle,
			FaceAttack,
			Creating,
			Firing,
			Die,
			End,
		};

		Carnation();
		~Carnation();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		virtual void Die() override;

		void Intro();

	private:
		void idle();
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
		int mPrevPatternType;
	};
}