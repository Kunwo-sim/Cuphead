#include "kwCarnationScene.h"
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

#include "kwCuphead.h"
#include "kwCarnation.h"
#include "kwFlowerPlatform.h"

namespace kw
{
	CarnationScene::CarnationScene()
	{
	}

	CarnationScene::~CarnationScene()
	{
	}

	void CarnationScene::Initialize()
	{
		PlayScene::Initialize();

		mBackGround1 = Resources::Load<Image>(L"Carnation_Back_01", L"..\\Resources\\Stage\\Carnation\\BackGround\\Carnation_Back_01.bmp");
		mBackGround2 = Resources::Load<Image>(L"Carnation_Back_02", L"..\\Resources\\Stage\\Carnation\\BackGround\\Carnation_Back_02.bmp");
		mBackGround3 = Resources::Load<Image>(L"Carnation_Back_03", L"..\\Resources\\Stage\\Carnation\\BackGround\\Carnation_Back_03.bmp");

		object::Instantiate<Ground>(eLayerType::Ground, Vector2(640, 720))->SetColliderSize(Vector2(1600.0f, 120.0f));

		mPlayer = object::Instantiate<Cuphead>(eLayerType::Player, Vector2(300, 600));
		mCarnation = object::Instantiate<Carnation>(eLayerType::Monster, Vector2(1050, 680));

		FlowerPlatform* platformA = object::Instantiate<FlowerPlatform>(eLayerType::Ground, Vector2(150, 400));
		platformA->SetPlatformType(FlowerPlatform::PlatformType::A);
		platformA->PlayPlatformAnim();

		FlowerPlatform* platformB = object::Instantiate<FlowerPlatform>(eLayerType::Ground, Vector2(400, 400));
		platformB->SetPlatformType(FlowerPlatform::PlatformType::B);
		platformB->PlayPlatformAnim();

		FlowerPlatform* platformC = object::Instantiate<FlowerPlatform>(eLayerType::Ground, Vector2(650, 400));
		platformC->SetPlatformType(FlowerPlatform::PlatformType::C);
		platformC->PlayPlatformAnim();

		mBGM = Resources::Load<Sound>(L"FlowerFuryBGM", L"..\\Resources\\Sound\\BGM\\FloralFuryBGM.wav");
	}

	void CarnationScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}

		PlayScene::Update();
	}

	void CarnationScene::Render(HDC hdc)
	{
		TransparentBlt(hdc, -50, 0
			, mBackGround1->GetWidth()
			, mBackGround1->GetHeight()
			, mBackGround1->GetHdc()
			, 0
			, 0
			, mBackGround1->GetWidth()
			, mBackGround1->GetHeight()
			, RGB(255, 0, 255));

		TransparentBlt(hdc, -50, 0
			, mBackGround2->GetWidth()
			, mBackGround2->GetHeight()
			, mBackGround2->GetHdc()
			, 0
			, 0
			, mBackGround2->GetWidth()
			, mBackGround2->GetHeight()
			, RGB(255, 0, 255));

		TransparentBlt(hdc, -50, -50
			, mBackGround3->GetWidth()
			, mBackGround3->GetHeight()
			, mBackGround3->GetHdc()
			, 0
			, 0
			, mBackGround3->GetWidth()
			, mBackGround3->GetHeight()
			, RGB(255, 0, 255));

		PlayScene::Render(hdc);
	}

	void CarnationScene::Release()
	{
		PlayScene::Release();
	}

	void CarnationScene::OnEnter()
	{
		PlayScene::OnEnter();

		mCarnation->Intro();
	}

	void CarnationScene::OnExit()
	{
		PlayScene::OnExit();
	}
}
