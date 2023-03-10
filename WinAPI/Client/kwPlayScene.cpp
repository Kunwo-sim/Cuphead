#include "kwPlayScene.h"
#include "kwCuphead.h"
#include "kwInput.h"
#include "kwSceneManager.h"
#include "kwCarnation.h"
#include "kwResources.h"
#include "kwCollisionManager.h"
#include "kwObject.h"

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

		//mBackGround = Resources::Load<Image>(L"Slime_BackGroud", L"..\\Resources\\Slime_BackGroud.bmp");
		mBackGround1 = Resources::Load<Image>(L"Carnation_Back_01", L"..\\Resources\\Stage\\Carnation\\BackGround\\Carnation_Back_01.bmp");
		mBackGround2 = Resources::Load<Image>(L"Carnation_Back_02", L"..\\Resources\\Stage\\Carnation\\BackGround\\Carnation_Back_02.bmp");
		mBackGround3 = Resources::Load<Image>(L"Carnation_Back_03", L"..\\Resources\\Stage\\Carnation\\BackGround\\Carnation_Back_03.bmp");

		object::Instantiate<Cuphead>(eLayerType::Player, Vector2(400, 650));
		object::Instantiate<Carnation>(eLayerType::Monster, Vector2(1050, 650));
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
		// BitBlt(hdc, 0, 0, mBackGround->GetWidth(), mBackGround->GetHeight(), mBackGround->GetHdc(), 0, 0, SRCCOPY);

		TransparentBlt(hdc, 0, 0
			, mBackGround1->GetWidth()
			, mBackGround1->GetHeight()
			, mBackGround1->GetHdc()
			, 0
			, 0
			, mBackGround1->GetWidth()
			, mBackGround1->GetHeight()
			, RGB(255, 0, 255));

		TransparentBlt(hdc, 0, 0
			, mBackGround2->GetWidth()
			, mBackGround2->GetHeight()
			, mBackGround2->GetHdc()
			, 0
			, 0
			, mBackGround2->GetWidth()
			, mBackGround2->GetHeight()
			, RGB(255, 0, 255));

		TransparentBlt(hdc, 0, 0
			, mBackGround3->GetWidth()
			, mBackGround3->GetHeight()
			, mBackGround3->GetHdc()
			, 0
			, 0
			, mBackGround3->GetWidth()
			, mBackGround3->GetHeight()
			, RGB(255, 0, 255));

		Scene::Render(hdc);
	}

	void PlayScene::Release()
	{
		Scene::Release();
	}

	void PlayScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::Monster, true);
	}

	void PlayScene::OnExit()
	{

	}
}
