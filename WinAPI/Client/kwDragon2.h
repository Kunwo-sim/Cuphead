#pragma once
#include "kwBossMonster.h"

namespace kw
{
	class Dragon2 : public BossMonster
	{
	public:
		enum class eDragon2State
		{
			Intro,
			Idle,
			Die,
			End,
		};

		Dragon2();
		~Dragon2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		virtual void Die() override;

		void Intro();

	private:
		void intro();
		void idle();
		void idleCallback();

		eDragon2State mState;
		class Sound* mSFX;

		double mTime;
		float mSpeed;
		int mCnt;
	};
}