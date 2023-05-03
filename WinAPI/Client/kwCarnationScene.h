#pragma once
#include "kwPlayScene.h"

namespace kw
{
	class CarnationScene : public PlayScene
	{
	public:
		CarnationScene();
		virtual ~CarnationScene() override;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		class Image* mBackGround1;
		class Image* mBackGround2;
		class Image* mBackGround3;
		class Carnation* mCarnation;
	};
}
