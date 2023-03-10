#pragma once
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwAnimator.h"

namespace kw
{
	class TitleCharacter : public GameObject
	{
	public:
		TitleCharacter();
		~TitleCharacter();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Animator* mAnimator;
	};
};