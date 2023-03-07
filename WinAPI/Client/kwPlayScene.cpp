#include "kwPlayScene.h"
#include "kwCuphead.h"
#include "kwInput.h"
#include "kwSceneManager.h"
#include "kwSlime.h"
#include "kwResources.h"
#include "kwCollisionManager.h"

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
		mBackGround = Resources::Load<Image>(L"Slime_BackGroud", L"..\\Resources\\Slime_BackGroud.bmp");

		Cuphead* cuphead = new Cuphead();
		cuphead->SetName(L"Player");
		AddGameObeject(cuphead, eLayerType::Player);

		Slime* slime = new Slime();
		slime->SetName(L"Slime");
		AddGameObeject(slime, eLayerType::Monster);

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, mBackGround->GetWidth(), mBackGround->GetHeight(), mBackGround->GetHdc(), 0, 0, SRCCOPY);
		Scene::Render(hdc);
	}

	void PlayScene::Release()
	{
		Scene::Release();
	}
}
