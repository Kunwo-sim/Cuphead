#pragma once
#include "kwGameObject.h"
#include "kwImage.h"

namespace kw
{
	class Cuphead : public GameObject
	{
	public:
		Cuphead();
		~Cuphead();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Image* mLeft;
		Image* mRight;
		Image* mUp;
		Image* mDown;
	};
}

