#pragma once
#include "kwGameObject.h"
#include "kwTransform.h"
#include "kwAnimator.h"

namespace kw
{
	class BulletFireEffect : public GameObject
	{
	public:
		BulletFireEffect();
		~BulletFireEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
	};
};