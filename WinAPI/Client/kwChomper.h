#pragma once
#include "kwMonster.h"

namespace kw
{
	class Chomper : public Monster
	{
	public:
		Chomper();
		virtual ~Chomper();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Die() override;

	private:
	};
}
