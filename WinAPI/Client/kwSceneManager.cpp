#include "kwSceneManager.h"
#include "kwTitleScene.h"
#include "kwOverWorldScene.h"
#include "kwPlayScene.h"
#include "kwEndingScene.h"
#include "kwCollisionManager.h"
#include "kwCamera.h"
#include "kwToolScene.h"

namespace kw
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	bool SceneManager::mIsSceneLoaded = false;
	eSceneType SceneManager::mLoadScene = eSceneType::Title;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::Max);

		// 새로운 씬 추가하려면 아래에 작성 및 헤더 추가
		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::OverWorld] = new OverWorldScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Ending] = new EndingScene();
		mScenes[(UINT)eSceneType::Tool] = new ToolScene();

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}

		mActiveScene = mScenes[(UINT)eSceneType::Title];
		SceneManager::LoadScene(eSceneType::Title);
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
		mIsSceneLoaded = true;
		mLoadScene = type;
	}

	void SceneManager::LateLoadScene()
	{
		if (mIsSceneLoaded)
		{
			Camera::Clear();

			mActiveScene->OnExit();
			CollisionManager::Clear();
			mActiveScene = mScenes[(UINT)mLoadScene];
			mActiveScene->OnEnter();

			mIsSceneLoaded = false;
		}
	}
}
