#include "kwOverWorldScene.h"
#include "kwSceneManager.h"
#include "kwResources.h"
#include "kwInput.h"
#include "kwResources.h"
#include "kwCollisionManager.h"
#include "kwGameObject.h"
#include "kwGround.h"
#include "kwCamera.h"
#include "kwObject.h"
#include "kwOverWorldCuphead.h"
#include "kwImage.h"
#include "kwPixelMap.h"
#include "kwSpriteRenderer.h"
#include "kwSound.h"

namespace kw
{
	OverWorldScene::OverWorldScene()
		: mOverWorldBGM(nullptr)
		, mPlayerStartPos(Vector2(650.0f, 800.0f))
	{

	}

	OverWorldScene::~OverWorldScene()
	{

	}

	void OverWorldScene::Initialize()
	{
		Scene::Initialize();

		mOverWorldBGM = Resources::Load<Sound>(L"OverWorldBGM", L"..\\Resources\\Sound\\BGM\\OverWorldBGM.wav");

		PixelMap* pixelMap = object::Instantiate<PixelMap>(eLayerType::PixelMap);

		GameObject* frontBG = object::Instantiate<GameObject>(eLayerType::FrontBG);
		Image* backFrontImage = Resources::Load<Image>(L"Stage1FrontMap", L"..\\Resources\\OverWorld\\Stage1FrontMap.bmp");
		SpriteRenderer* sr2 = frontBG->AddComponent<SpriteRenderer>();
		sr2->AddSprite(backFrontImage, Vector2(398.0f, 380.0f), true);

		GameObject* backGround = object::Instantiate<GameObject>(eLayerType::BG);
		Image* backGroundImage = Resources::Load<Image>(L"Stage1BackGround", L"..\\Resources\\OverWorld\\Stage1BackGround.bmp");
		SpriteRenderer* sr = backGround->AddComponent<SpriteRenderer>();
		sr->AddSprite(backGroundImage, Vector2(0.0f, 0.0f), false);
		
		OverWorldCuphead* player = object::Instantiate<OverWorldCuphead>(eLayerType::Player, mPlayerStartPos);
		player->SetPixelMap(pixelMap);
	}

	void OverWorldScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
	}

	void OverWorldScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void OverWorldScene::Release()
	{
		Scene::Release();
	}

	void OverWorldScene::OnEnter()
	{
		Camera::SetLookPosition(mPlayerStartPos);
		mOverWorldBGM->Play(true);
	}

	void OverWorldScene::OnExit()
	{
		mOverWorldBGM->Stop(true);
	}
}
