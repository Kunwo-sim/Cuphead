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
#include "kwSound.h"

namespace kw
{
	OverWorldScene::OverWorldScene()
		: mBackGround(nullptr)
		, mStartPos(Vector2(1000.0f, 1000.0f))
	{

	}

	OverWorldScene::~OverWorldScene()
	{

	}

	void OverWorldScene::Initialize()
	{
		Scene::Initialize();

		mOverWorldBGM = Resources::Load<Sound>(L"OverWorldBGM", L"..\\Resources\\Sound\\BGM\\OverWorldBGM.wav");
		mBackGround = Resources::Load<Image>(L"Stage1BackGround", L"..\\Resources\\Stage1BackGround.bmp");
		PixelMap* pixelMap = object::Instantiate<PixelMap>(eLayerType::PixelMap);
		OverWorldCuphead* player = object::Instantiate<OverWorldCuphead>(eLayerType::Player, mStartPos);
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
		Vector2 pos = Vector2::Zero;
		pos = Camera::CalculatePos(pos);
		BitBlt(hdc, pos.x, pos.y, mBackGround->GetWidth(), mBackGround->GetHeight(), mBackGround->GetHdc(), 0, 0, SRCCOPY);
		Scene::Render(hdc);
	}

	void OverWorldScene::Release()
	{
		Scene::Release();
	}

	void OverWorldScene::OnEnter()
	{
		Camera::SetLookPosition(mStartPos);
		mOverWorldBGM->Play(true);
	}

	void OverWorldScene::OnExit()
	{
		mOverWorldBGM->Stop(true);
	}
}
