#pragma once
#include "kwGameObject.h"

namespace kw
{
	class HpBar : public GameObject
	{
	public:
		HpBar();
		virtual ~HpBar();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		int mPrevHp;
	};
}
