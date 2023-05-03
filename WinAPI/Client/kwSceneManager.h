#pragma once
#include "kwScene.h"
#include "kwChangeScene.h"

namespace kw
{
	class Cuphead;

	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Destroy();
		static void Release();

		static Scene* GetActiveScene() { return mActiveScene; }
		static class ChangeScene* GetChangeScene();
		static void SetActiveScene(Scene* scene) { mActiveScene = scene; }

		static void LoadScene(eSceneType type);
		static void LoadScene(eSceneType type, float time);
		static void LateLoadScene();
		static Cuphead* GetPlayer();

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static bool mIsSceneLoaded;
		static float mRemainTime;
		static eSceneType mLoadScene;
	};
}

