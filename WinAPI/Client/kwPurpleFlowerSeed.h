#pragma once
#include "kwFlowerSeed.h"

namespace kw
{
	class PurpleFlowerSeed : public FlowerSeed
	{
	public:
		PurpleFlowerSeed();
		virtual ~PurpleFlowerSeed();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void PlayFallAnim() override;
		virtual void PlayGrowAnim() override;
		void CreateChomper();
	private:

	};
}
