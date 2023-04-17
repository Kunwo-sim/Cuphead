#include "kwChomper.h"

#include "kwTransform.h"
#include "kwCollider.h"
#include "kwAnimator.h"

namespace kw
{
	Chomper::Chomper()
	{
		SetHp(3.0f);
	}

	Chomper::~Chomper()
	{

	}

	void Chomper::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\PurpleSeed\\Chomper\\Idle", Vector2::Zero, 0.04f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\PurpleSeed\\Chomper\\Die", Vector2::Zero, 0.04f);
		mAnimator->Play(L"ChomperIdle", true);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(50.0f, 80.0f));

		Monster::Initialize();
	}

	void Chomper::Update()
	{
		Monster::Update();
	}

	void Chomper::Die()
	{		
		mCollider->SetSize(Vector2::Zero);
		mAnimator->Play(L"ChomperDie", false);
		Monster::Die();
	}
}
