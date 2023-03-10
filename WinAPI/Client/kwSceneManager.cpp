#include "kwSceneManager.h"
#include "kwPlayScene.h"
#include "kwTitleScene.h"
#include "kwEndingScene.h"
#include "kwCollisionManager.h"
#include "kwCamera.h"

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

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}

		mActiveScene = mScenes[(UINT)eSceneType::Title];
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		Camera::Clear();

		mActiveScene->OnExit();
		CollisionManager::Clear();
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();
	}

}
