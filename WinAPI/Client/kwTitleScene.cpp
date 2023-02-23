#include "kwTitleScene.h"
#include "kwInput.h"
#include "kwSceneManager.h"

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
		
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
	}

	void TitleScene::Render(HDC hdc)
	{

	}

	void TitleScene::Release()
	{

	}
}
