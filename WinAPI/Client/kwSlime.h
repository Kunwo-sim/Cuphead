#pragma once

#include "kwGameObject.h"
#include "kwImage.h"
#include "kwAnimator.h"
#include "kwTransform.h"

namespace kw
{
	class Slime : public GameObject
	{
	public:
		Slime();
		~Slime();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
		Transform* mTransform;
	};
}