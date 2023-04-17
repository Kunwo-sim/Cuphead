#pragma once
#include "kwScene.h"

namespace kw
{
	class Cuphead;

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

	private:
		class Image* mBackGround;
		class Image* mBackGround2;
		class Image* mBackGround3;
		class Image* mBackGround1;
		class Sound* mFloralFuryBGM;
		
		class Carnation* mCarnation;
		Cuphead* mPlayer;
	};
}
