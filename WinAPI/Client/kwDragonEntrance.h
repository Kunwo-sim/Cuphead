#pragma once
#include "kwGameObject.h"
#include "kwOverWorldEntrance.h"

namespace kw
{
	class DragonEntrance : public OverWorldEntrance
	{
	public:
		DragonEntrance();
		virtual ~DragonEntrance();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void EnterBossMap();

	private:
	};
}
