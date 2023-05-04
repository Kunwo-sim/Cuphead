#pragma once
#include "kwAttackObject.h"

namespace kw
{
	class FireMarcher : public AttackObject
	{
	public:
		enum class eFireMarcherState
		{
			Idle,
			Charge,
			Jump
		};

		FireMarcher();
		virtual ~FireMarcher();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	protected:
		eFireMarcherState mState;
		float mSpeed;
		class Sound* mSFX;
	};
}
