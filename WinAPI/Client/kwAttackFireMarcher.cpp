#include "kwAttackFireMarcher.h"

#include "kwObject.h"
#include "kwTime.h"
#include "kwResources.h"
#include "kwSound.h"

namespace kw
{
	AttackFireMarcher::AttackFireMarcher()
		: mTime(0.0)
		, mSpeed(300.0f)
		, mState(eAttackFireMarcherState::Idle)
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
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Fire\\Attack\\Idle", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Fire\\Attack\\Charge", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Fire\\Attack\\Jump", Vector2::Zero, 0.06f);

		mAnimator->Play(L"AttackIdle", true);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(75, 75));

		AttackObject::Initialize();
	}

	void AttackFireMarcher::Update()
	{
		switch (mState)
		{
		case eAttackFireMarcherState::Idle:
			Idle();
			break;
		case eAttackFireMarcherState::Charge:
			Charge();
			break;
		case eAttackFireMarcherState::Jump:
			Jump();
			break;
		}
		
		if (mTransform->GetPos().x > 1500.0f)
		{
			object::Destory(this);
		}

		AttackObject::Update();
	}

	void AttackFireMarcher::Render(HDC hdc)
	{
		AttackObject::Render(hdc);
	}

	void AttackFireMarcher::Release()
	{

	}

	void AttackFireMarcher::Idle()
	{
		mTime += Time::DeltaTime();

		mTransform->AddPos(Vector2(mSpeed * Time::DeltaTime(), 0.0f));

		if (mTime > 1.5f)
		{
			mState = eAttackFireMarcherState::Charge;
			mAnimator->Play(L"AttackCharge", true);
			mTime = 0.0f;
		}
	}

	void AttackFireMarcher::Charge()
	{
		mTime += Time::DeltaTime();

		if (mTime > 0.7f)
		{
			mState = eAttackFireMarcherState::Jump;
			mAnimator->Play(L"AttackJump", true);
		}

	}

	void AttackFireMarcher::Jump()
	{
		float pos = mSpeed * 2 * Time::DeltaTime();
		Vector2 addPos = Vector2(pos, -pos);
		mTransform->AddPos(addPos);
	}
}
