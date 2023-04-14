#include "kwCarnationEntrance.h"
#include "kwSceneManager.h"

namespace kw
{
	CarnationEntrance::CarnationEntrance()
	{
	}

	CarnationEntrance::~CarnationEntrance()
	{
	}

	void CarnationEntrance::Initialize()
	{
		OverWorldEntrance::Initialize();

		mAnimator->CreateAnimations(L"..\\Resources\\OverWorld\\CarnationEntrance", Vector2::Zero, 0.1f);
		mAnimator->Play(L"OverWorldCarnationEntrance", true);
		mCollider->SetSize(Vector2(130.0f, 100.0f));
	}

	void CarnationEntrance::Update()
	{
		OverWorldEntrance::Update();
	}

	void CarnationEntrance::Render(HDC hdc)
	{
		OverWorldEntrance::Render(hdc);
	}

	void CarnationEntrance::Release()
	{

	}

	void CarnationEntrance::EnterBossMap()
	{
		SceneManager::LoadScene(eSceneType::Play);
	}
}
