#include "kwTitleScene.h"
#include "kwInput.h"
#include "kwSceneManager.h"
#include "kwResources.h"
#include "kwTitleCharacter.h"
#include "kwObject.h"
#include "kwCollisionManager.h"

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
		Scene::Initialize();

		mBackGround = Resources::Load<Image>(L"Tilte_BackGroud", L"..\\Resources\\Title_BackGroud.bmp");
		object::Instantiate<TitleCharacter>(eLayerType::UI, Vector2(640.0f, 720.0f));
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}

	void TitleScene::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, mBackGround->GetWidth(), mBackGround->GetHeight(), mBackGround->GetHdc(), 0, 0, SRCCOPY);
		Scene::Render(hdc);
	}

	void TitleScene::Release()
	{
		Scene::Release();
	}

	void TitleScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
	}

	void TitleScene::OnExit()
	{
		//mCuphead->SetPos(Vector2{ 0.0f, 0.0f });
	}
}
