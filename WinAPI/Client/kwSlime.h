#pragma once

#include "kwGameObject.h"
#include "kwImage.h"

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
		Image* mImage;
	};
}