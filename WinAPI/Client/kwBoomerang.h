#pragma once
#include "kwAttackObject.h"

namespace kw
{
	class Boomerang : public AttackObject
	{
	public:
		Boomerang();
		virtual ~Boomerang();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		float mSpawnTime;
		float mSpeed;
	};
}
