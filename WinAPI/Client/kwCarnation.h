#pragma once
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwAnimator.h"
#include "kwTransform.h"

namespace kw
{
	class Carnation : public GameObject
	{
	public:
		enum class eCarnationState
		{
			Idle,
		};

		Carnation();
		~Carnation();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		eCarnationState mState;
		Animator* mAnimator;
		Transform* mTransform;
	};
}

