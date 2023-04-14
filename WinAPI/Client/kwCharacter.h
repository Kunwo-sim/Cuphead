#pragma once
#include "kwGameObject.h"

namespace kw
{
	class Character : public GameObject
	{
	public:
		Character();
		virtual ~Character();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		float mHp;
		bool mIsDead;
	};
}
