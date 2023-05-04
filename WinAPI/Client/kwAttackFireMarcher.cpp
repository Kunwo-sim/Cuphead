#include "kwAttackFireMarcher.h"

#include "kwObject.h"
#include "kwTime.h"
#include "kwResources.h"
#include "kwSound.h"

namespace kw
{
	AttackFireMarcher::AttackFireMarcher()
	{

	}

	AttackFireMarcher::~AttackFireMarcher()
	{

	}

	void AttackFireMarcher::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Fire\\A", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Fire\\B", Vector2::Zero, 0.06f);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(75, 75));

		FireMarcher::Initialize();
	}

	void AttackFireMarcher::Update()
	{
		mTransform->AddPos(Vector2(mSpeed * Time::DeltaTime(), 0.0f));

		if (mTransform->GetPos().x > 1500.0f)
		{
			object::Destory(this);

		}

		FireMarcher::Update();
	}

	void AttackFireMarcher::Render(HDC hdc)
	{
		FireMarcher::Render(hdc);
	}

	void AttackFireMarcher::Release()
	{

	}
}
