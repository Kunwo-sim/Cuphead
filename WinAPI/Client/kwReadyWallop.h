#pragma once
#include "kwGameObject.h"

namespace kw
{
	class ReadyWallop : public GameObject
	{
	public:
		ReadyWallop();
		virtual ~ReadyWallop();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
	};
}
