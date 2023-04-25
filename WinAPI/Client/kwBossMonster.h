#pragma once
#include "kwMonster.h"

namespace kw
{
	class BossMonster : public Monster
	{
	public:
		BossMonster();
		virtual ~BossMonster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Die() override;

	private:
		class Sound* mKnoctOutSound;
	};
}


