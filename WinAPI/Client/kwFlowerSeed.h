#pragma once
#include "kwAttackObject.h"

namespace kw
{
	class FlowerSeed : public AttackObject
	{
		enum class eSeedState
		{
			Fall,
			Grow,
			Vine,
		};

	public:
		FlowerSeed();
		virtual ~FlowerSeed();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void PlayFallAnim();
		virtual void PlayGrowAnim();
		virtual void CreateVine();
		virtual void PlayLongVineEndAnim();
		virtual void PlayShortVineEndAnim();

	protected:
		eSeedState mState;
		float mSpeed;
		

	};
}
