#include "kwChomper.h"

#include "kwTransform.h"
#include "kwCollider.h"
#include "kwAnimator.h"

namespace kw
{
	Chomper::Chomper()
	{

	}

	Chomper::~Chomper()
	{

	}

	void Chomper::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\PurpleSeed\\Chomper\\Idle", Vector2::Zero, 0.04f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\PurpleSeed\\Chomper\\Death", Vector2::Zero, 0.04f);
		mAnimator->Play(L"ChomperIdle", true);

		AttackObject::Initialize();
	}

	void Chomper::Update()
	{
		AttackObject::Update();
	}

	void Chomper::Render(HDC hdc)
	{
		AttackObject::Render(hdc);
	}

	void Chomper::Release()
	{

	}
}
