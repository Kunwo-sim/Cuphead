#include "kwDragonEntrance.h"
#include "kwSceneManager.h"

namespace kw
{
	DragonEntrance::DragonEntrance()
	{
	}

	DragonEntrance::~DragonEntrance()
	{
	}

	void DragonEntrance::Initialize()
	{
		OverWorldEntrance::Initialize();

		mAnimator->CreateAnimations(L"..\\Resources\\OverWorld\\CarnationEntrance", Vector2::Zero, 0.1f);
		mAnimator->Play(L"OverWorldCarnationEntrance", true);
		mCollider->SetSize(Vector2(130.0f, 100.0f));
	}

	void DragonEntrance::Update()
	{
		OverWorldEntrance::Update();
	}

	void DragonEntrance::Render(HDC hdc)
	{
		OverWorldEntrance::Render(hdc);
	}

	void DragonEntrance::Release()
	{

	}

	void DragonEntrance::EnterBossMap()
	{
		OverWorldEntrance::EnterBossMap();
		SceneManager::LoadScene(eSceneType::Change, 0.6f);
		SceneManager::GetChangeScene()->SetLoadScene(eSceneType::Dragon);
	}
}
