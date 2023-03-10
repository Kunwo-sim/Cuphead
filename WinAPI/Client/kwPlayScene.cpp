#include "kwPlayScene.h"
#include "kwCuphead.h"
#include "kwInput.h"
#include "kwSceneManager.h"
#include "kwCarnation.h"
#include "kwResources.h"
#include "kwCollisionManager.h"
#include "kwObject.h"

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
		Scene::Initialize();

		mBackGround = Resources::Load<Image>(L"Slime_BackGroud", L"..\\Resources\\Slime_BackGroud.bmp");

		object::Instantiate<Cuphead>(eLayerType::Player, Vector2(400, 650));
		object::Instantiate<Carnation>(eLayerType::Monster, Vector2(1050, 650));
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}

		Scene::Update();
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

	void PlayScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);
	}

	void PlayScene::OnExit()
	{

	}
}
