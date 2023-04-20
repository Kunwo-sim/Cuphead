#pragma once
#include "kwGameObject.h"

namespace kw
{
	class BossExplosion : public GameObject
	{
	public:
		BossExplosion();
		~BossExplosion();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
	};
};