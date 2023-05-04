#include "kwReadyWallop.h"

namespace kw
{
	ReadyWallop::ReadyWallop()
	{
	}

	ReadyWallop::~ReadyWallop()
	{
	}

	void ReadyWallop::Initialize()
	{
		SetPivot(ePivot::MiddleCenter);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\ReadyWallop", Vector2::Zero, 0.06f);
		mAnimator->Play(L"UIReadyWallop", false);

		GameObject::Initialize();
	}

	void ReadyWallop::Update()
	{
		GameObject::Update();
	}

	void ReadyWallop::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
