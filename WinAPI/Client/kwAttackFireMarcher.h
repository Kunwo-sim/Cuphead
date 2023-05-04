#pragma once
#include "kwFireMarcher.h"

namespace kw
{
	class AttackFireMarcher : public FireMarcher
	{
	public:
		enum class eFireMarcherState
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

	protected:
	};
}
