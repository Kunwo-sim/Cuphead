#pragma once
#include "kwFlowerSeed.h"

namespace kw
{
	class PinkFlowerSeed : public FlowerSeed
	{
	public:
		PinkFlowerSeed();
		virtual ~PinkFlowerSeed();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void PlayFallAnim() override;
		virtual void PlayGrowAnim() override;
		virtual void CreateVine() override;
		virtual void PlayLongVineEndAnim() override;

	private:
		class ParryObject* mParryObject;
	};
}
