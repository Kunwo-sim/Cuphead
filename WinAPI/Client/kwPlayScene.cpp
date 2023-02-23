#include "kwPlayScene.h"
#include "kwCuphead.h"
#include "kwInput.h"
#include "kwSceneManager.h"

namespace kw
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		for (size_t i = 0; i < 100; i++)
		{
			Cuphead* cuphead = new Cuphead();
			cuphead->SetName(L"Player");
			AddGameObeject(cuphead, eLayerType::Player);
		}

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		//Super::Tick();
		Scene::Render(hdc);
	}

	void PlayScene::Release()
	{
		Scene::Release();
	}
}
