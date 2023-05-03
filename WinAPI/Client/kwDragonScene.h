#pragma once
#include "kwPlayScene.h"

namespace kw
{
	class DragonScene : public PlayScene
	{
	public:
		DragonScene();
		virtual ~DragonScene() override;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		class Image* mBackGround;
		class Dragon* mDragon;
		double mTime;
		int mPrevPlatformYpos;
	};
}
