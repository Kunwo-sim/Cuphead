#pragma once
#include "kwAttackObject.h"

namespace kw
{
	class Chomper : public AttackObject
	{
	public:
		Chomper();
		virtual ~Chomper();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
	};
}
