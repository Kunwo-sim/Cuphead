#pragma once
#include "kwGameObject.h"
#include "kwOverWorldEntrance.h"

namespace kw
{
	class CarnationEntrance : public OverWorldEntrance
	{
	public:
		CarnationEntrance();
		virtual ~CarnationEntrance();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void EnterBossMap();

	private:
	};
}
