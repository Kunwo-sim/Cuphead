#include "kwDragonScene.h"
#include "kwSceneManager.h"
#include "kwCollisionManager.h"
#include "kwInput.h"
#include "kwCamera.h"

#include "kwTime.h"
#include "kwResources.h"
#include "kwImage.h"
#include "kwObject.h"
#include "kwGameObject.h"
#include "kwSpriteRenderer.h"
#include "kwSound.h"

#include "kwGround.h"

#include "kwCuphead.h"
#include "kwDragon.h"
#include "kwDragonPlatform.h"

namespace kw
{
	DragonScene::DragonScene()
		: mTime(0.0f)
		, mPrevPlatformYpos(-500)
	{
	}

	DragonScene::~DragonScene()
	{
	}

	void DragonScene::Initialize()
	{
		PlayScene::Initialize();

		Image* backGroundImage = Resources::Load<Image>(L"Dragon_Background_Sky", L"..\\Resources\\Stage\\Dragon\\BackGround\\dragon_background_sky_0001.bmp");
		Image* tower = Resources::Load<Image>(L"Dragon_Tower", L"..\\Resources\\Stage\\Dragon\\BackGround\\Tower\\dragon_spire_0001.bmp");

		GameObject* backGround = object::Instantiate<GameObject>(eLayerType::BG);
		backGround->AddComponent<SpriteRenderer>();
		SpriteRenderer* sr = backGround->GetComponent<SpriteRenderer>();
		sr->AddSprite(backGroundImage, Vector2(0 ,0), false);
		sr->AddSprite(tower, Vector2(425, -100), true);

		object::Instantiate<Ground>(eLayerType::Ground, Vector2(640, 720))->SetColliderSize(Vector2(1600.0f, 120.0f));

		mPlayer = object::Instantiate<Cuphead>(eLayerType::Player, Vector2(300, 600));
		mDragon = object::Instantiate<Dragon>(eLayerType::Monster, Vector2(1100, 900));

		mBGM = Resources::Load<Sound>(L"DragonBGM", L"..\\Resources\\Sound\\BGM\\DragonBGM.wav");
	}

	void DragonScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}

		mTime += Time::DeltaTime();

		if (mTime > 1.2f)
		{
			mTime = 0.0f;

			int yPos = math::GetRandomNumber(250, 650);

			while (abs(yPos - mPrevPlatformYpos) < 100.0f)
			{
				yPos = math::GetRandomNumber(250, 650);
			}

			mPrevPlatformYpos = yPos;
			int type = math::GetRandomNumber(0, 2);

			object::Instantiate<DragonPlatform>(eLayerType::Ground, Vector2(1400.0, yPos))->SetPlatformType(DragonPlatform::PlatformType(type));
		}

		PlayScene::Update();
	}

	void DragonScene::Render(HDC hdc)
	{
		PlayScene::Render(hdc);
	}

	void DragonScene::Release()
	{
		PlayScene::Release();
	}

	void DragonScene::OnEnter()
	{
		PlayScene::OnEnter();

		object::Instantiate<DragonPlatform>(eLayerType::Ground, Vector2(300.0f, 500.0f))->SetPlatformType(DragonPlatform::PlatformType(DragonPlatform::PlatformType::A));

		mDragon->Intro();
	}

	void DragonScene::OnExit()
	{
		PlayScene::OnExit();
	}
}
