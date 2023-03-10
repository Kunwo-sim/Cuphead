#include "kwEndingScene.h"
#include "kwCuphead.h"
#include "kwInput.h"
#include "kwSceneManager.h"
#include "kwSlime.h"
#include "kwResources.h"

namespace kw
{
	EndingScene::EndingScene()
	{
	}

	EndingScene::~EndingScene()
	{
	}

	void EndingScene::Initialize()
	{
		mBackGround = Resources::Load<Image>(L"Ending_BackGround", L"..\\Resources\\Ending_BackGround.bmp");

		Scene::Initialize();
	}

	void EndingScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
	}

	void EndingScene::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, mBackGround->GetWidth(), mBackGround->GetHeight(), mBackGround->GetHdc(), 0, 0, SRCCOPY);
		Scene::Render(hdc);
	}

	void EndingScene::Release()
	{
		Scene::Release();
	}
}