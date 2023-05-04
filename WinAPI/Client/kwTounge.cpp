#include "kwTounge.h"

#include "kwObject.h"

namespace kw
{
	Tounge::Tounge()
	{

	}

	Tounge::~Tounge()
	{

	}

	void Tounge::Initialize()
	{
		SetPivot(ePivot::MiddleCenter);

		mTransform = GetComponent<Transform>();

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Tounge\\Intro", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Tounge\\Idle", Vector2::Zero, 0.06f);
		mAnimator->Play(L"ToungeIntro", true);

		mAnimator->GetCompleteEvent(L"ToungeIntro") = std::bind(&Tounge::IdleCallback, this);

		GameObject::Initialize();
	}

	void Tounge::Update()
	{
		GameObject::Update();
	}

	void Tounge::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Tounge::Release()
	{

	}

	void Tounge::IdleCallback()
	{
		mAnimator->Play(L"ToungeIdle", true);
	}
}
