#include "kwTitleScene.h"
#include "kwInput.h"
#include "kwSceneManager.h"
#include "kwResources.h"

namespace kw
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		mBackGround = Resources::Load<Image>(L"Tilte_BackGroud", L"..\\Resources\\Title_BackGroud.bmp");
		//mBackCharacter = Resources::Load<Image>(L"BackCharacter", L"..\\Resources\\Title_Character.png");
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, mBackGround->GetWidth(), mBackGround->GetHeight(), mBackGround->GetHdc(), 0, 0, SRCCOPY);
		//BitBlt(hdc, 0, 0, mBackCharacter->GetWidth(), mBackCharacter->GetHeight(), mBackCharacter->GetHdc(), 0, 0, SRCCOPY);
	}

	void TitleScene::Release()
	{

	}
}
