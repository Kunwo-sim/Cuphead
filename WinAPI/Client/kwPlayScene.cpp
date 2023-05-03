#include "kwPlayScene.h"
#include "kwSceneManager.h"
#include "kwCollisionManager.h"
#include "kwInput.h"
#include "kwCamera.h"

#include "kwResources.h"
#include "kwImage.h"
#include "kwObject.h"
#include "kwGameObject.h"
#include "kwSound.h"

#include "kwGround.h"

#include "kwHpBar.h"
#include "kwCuphead.h"
#include "kwCarnation.h"
#include "kwFlowerPlatform.h"
#include "kwReadyWallop.h"

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

		object::Instantiate<HpBar>(eLayerType::UI, Vector2(60, 700));
		object::Instantiate<ReadyWallop>(eLayerType::Effect, Vector2::Center);		

		mReadySound = Resources::Load<Sound>(L"ReadySound", L"..\\Resources\\Sound\\SFX\\ReadySound.wav");
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
		Scene::Render(hdc);
	}

	void PlayScene::Release()
	{
		Scene::Release();
	}

	void PlayScene::OnEnter()
	{
		Camera::SceneEnterEffect();

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::AttackObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);

		mBGM->Play(true);
		mReadySound->Play(false);
	}

	void PlayScene::OnExit()
	{
		mBGM->Stop(true);
	}
}
