#pragma once
#include "kwMonster.h"

namespace kw
{
	class Venus : public Monster
	{
	public:

		enum class eVenusState
		{
			Create,
			Idle,
			Die,
		};

		Venus();
		virtual ~Venus();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		virtual void Die();

	private:
		void playIdleAnim();
		float mSpeed;
		eVenusState mState;
	};
}
