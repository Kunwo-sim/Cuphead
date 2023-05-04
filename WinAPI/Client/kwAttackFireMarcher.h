#pragma once
#include "kwFireMarcher.h"

namespace kw
{
	class AttackFireMarcher : public FireMarcher
	{
	public:
		enum class eAttackFireMarcherState
		{
			Idle,
			Charge,
			Jump
		};

		AttackFireMarcher();
		virtual ~AttackFireMarcher();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void Idle();
		void Charge();
		void Jump();

	protected:
		eAttackFireMarcherState mState;
		float mTime;
		float mSpeed;		
	};
}
