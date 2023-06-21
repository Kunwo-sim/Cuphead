#pragma once
#include "kwScene.h"

namespace kw
{
	class TutorialScene : public Scene
	{
	public:
		TutorialScene();
		virtual ~TutorialScene() override;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual Cuphead* GetPlayer() override { return mPlayer; };

	protected:
		class Cuphead* mPlayer;
	};
}
