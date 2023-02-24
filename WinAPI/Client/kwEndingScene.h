#pragma once
#include "kwScene.h"
#include "kwTitleScene.h"
#include "kwInput.h"
#include "kwSceneManager.h"
#include "kwResources.h"
#include "kwImage.h"

namespace kw
{
	class EndingScene : public Scene
	{
	public:
		EndingScene();
		~EndingScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mBackGround;
	};
}


