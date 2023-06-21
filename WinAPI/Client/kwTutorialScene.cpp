#include "kwTutorialScene.h"
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
	TutorialScene::TutorialScene()
	{
	}

	TutorialScene::~TutorialScene()
	{
	}

	void TutorialScene::Initialize()
	{
		Scene::Initialize();

		mPlayer = object::Instantiate<Cuphead>(eLayerType::Player, Vector2(300, 600));

		object::Instantiate<Ground>(eLayerType::Ground, Vector2(640, 720))->SetColliderSize(Vector2(1600.0f, 120.0f));
		object::Instantiate<HpBar>(eLayerType::UI, Vector2(60, 700));

		mBGM = Resources::Load<Sound>(L"TutorialBGM", L"..\\Resources\\Sound\\BGM\\TutorialBGM.wav");
	}

	void TutorialScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::OverWorld);
		}

		Scene::Update();
	}

	void TutorialScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void TutorialScene::Release()
	{
		Scene::Release();
	}

	void TutorialScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::AttackObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::ParryObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);

		mBGM->Play(true);
	}

	void TutorialScene::OnExit()
	{
		mBGM->Stop(true);
	}
}
