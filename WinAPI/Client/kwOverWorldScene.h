#pragma once
#include "kwScene.h"

namespace kw
{
	class OverWorldScene : public Scene
	{
	public:
		OverWorldScene();
		~OverWorldScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		class Image* mBackGround;
		class Sound* mOverWorldBGM;

		Vector2 mStartPos;
	};
}
