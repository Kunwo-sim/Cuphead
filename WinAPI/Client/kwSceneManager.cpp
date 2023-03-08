#include "kwSceneManager.h"
#include "kwPlayScene.h"
#include "kwTitleScene.h"
#include "kwEndingScene.h"
#include "kwCollisionManager.h"

namespace kw
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::Max);

		// 새로운 씬 추가하려면 아래에 작성 및 헤더 추가
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
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Release();
			delete scene;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		// 현재 씬 Exit 호출
		mActiveScene->OnExit();
		CollisionManager::Clear();
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();
	}

}
