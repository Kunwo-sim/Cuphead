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

		SetPivot(ePivot::LowCenter);

		mAnimator->CreateAnimations(L"..\\Resources\\OverWorld\\DragonEntrance", Vector2::Zero, 0.1f);
		mAnimator->Play(L"OverWorldDragonEntrance", true);
		mCollider->SetSize(Vector2(80.0f, 140.0f));
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
