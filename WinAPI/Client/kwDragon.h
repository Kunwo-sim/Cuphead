#pragma once
#include "kwBossMonster.h"

namespace kw
{
	class Dragon : public BossMonster
	{
	public:
		enum class eDragonState
		{
			Intro,
			Idle,
			MeteorAttack,
			Peashot,
			Die,
			End,
		};

		Dragon();
		~Dragon();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		virtual void Die() override;

		void Intro();

	private:
		void idle();
		void peashot();

		void idleCallback();
		void meteorStartCallback();
		void meteorLoopCallback();
		void peashotStartCallback();
		void peashotLoopCallback();

		eDragonState mState;
		class Sound* mSFX;

		int mLoopCount;
		double mTime;
		int mPrevPatternType;

		Vector2 mRingDir;
		Vector2 mRingStartPos;
		int mRingCount;
	};
}