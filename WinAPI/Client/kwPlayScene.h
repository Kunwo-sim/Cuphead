#pragma once
#include "kwScene.h"

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

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual Cuphead* GetPlayer() override { return mPlayer; };

	protected:
		class Sound* mReadySound;
		class Cuphead* mPlayer;
	};
}
