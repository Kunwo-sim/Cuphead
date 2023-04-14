#pragma once
#include "kwFlowerSeed.h"

namespace kw
{
	class BlueFlowerSeed : public FlowerSeed
	{
	public:
		BlueFlowerSeed();
		virtual ~BlueFlowerSeed();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void PlayFallAnim() override;
		virtual void PlayGrowAnim() override;
		virtual void CreateVine() override;

	private:

	};
}
