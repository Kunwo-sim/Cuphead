#include "kwFireMarcher.h"

#include "kwObject.h"
#include "kwTime.h"
#include "kwResources.h"
#include "kwSound.h"

namespace kw
{
	FireMarcher::FireMarcher()
		: mState(eFireMarcherState::Idle)
		, mSpeed(300.0f)
		, mSFX(nullptr)
	{

	}

	FireMarcher::~FireMarcher()
	{

	}

	void FireMarcher::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Fire\\A", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Fire\\B", Vector2::Zero, 0.06f);
		mAnimator->Play(L"FireA", true);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(75, 75));

		AttackObject::Initialize();
	}

	void FireMarcher::Update()
	{
		mTransform->AddPos(Vector2(mSpeed * Time::DeltaTime(), 0.0f));

		if (mTransform->GetPos().x > 1500.0f)
		{
			object::Destory(this);

		}
		AttackObject::Update();
	}

	void FireMarcher::Render(HDC hdc)
	{
		AttackObject::Render(hdc);
	}

	void FireMarcher::Release()
	{

	}
}
