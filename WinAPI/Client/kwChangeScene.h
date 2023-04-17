#pragma once
#include "kwScene.h"

namespace kw
{
	class ChangeScene : public Scene
	{
	public:
		ChangeScene();
		~ChangeScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
		void SetLoadScene(eSceneType type) { mLoadScene = type; };

	private:
		eSceneType mLoadScene;
		float mTime;
	};
}
