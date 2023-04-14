#pragma once
#include "kwScene.h"

namespace kw
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Destroy();
		static void Release();

		static Scene* GetActiveScene() { return mActiveScene; }
		static void SetActiveScene(Scene* scene) { mActiveScene = scene; }

		static void LoadScene(eSceneType type);
		static void LateLoadScene();

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static bool mIsSceneLoaded;
		static eSceneType mLoadScene;
	};
}

