#pragma once
#include "kwScene.h"
#include "kwImage.h"

namespace kw
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene() override;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mBackGround;
	};
}
