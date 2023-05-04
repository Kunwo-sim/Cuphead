#pragma once
#include "kwGameObject.h"

namespace kw
{
	class Tounge : public GameObject
	{
	public:
		Tounge();
		virtual ~Tounge();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void IdleCallback();
	};
}
