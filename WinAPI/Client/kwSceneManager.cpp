#include "kwSceneManager.h"
#include "kwPlayScene.h"
#include "kwTitleScene.h"
#include "kwEndingScene.h"

namespace kw
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::Max);

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Ending] = new EndingScene();

		mActiveScene = mScenes[(UINT)eSceneType::Title];

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}
	}

	void SceneManager::Update()
	{
		for (Scene* scene : mScenes)
		{
			mActiveScene->Update();
		}
	}

	void SceneManager::Render(HDC hdc)
	{
		for (Scene* scene : mScenes)
		{
			mActiveScene->Render(hdc);
		}
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Release();
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		mActiveScene->OnExit();
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();
	}

}
