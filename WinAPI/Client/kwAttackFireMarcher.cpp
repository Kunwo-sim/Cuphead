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
		, mAttackStartTime(0.0f)
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

		int randomAttackTime = math::GetRandomNumber(10, 20);
		mAttackStartTime = randomAttackTime / 10.0f;

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

		if (mTime > mAttackStartTime)
		{
			mState = eAttackFireMarcherState::Charge;
			mAnimator->Play(L"AttackCharge", true);

			mSFX = Resources::Load<Sound>(L"DragonFire_Charge", L"..\\Resources\\Sound\\SFX\\Dragon\\DragonFire_Charge.wav");
			mSFX->Play(false);

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

			mSFX = Resources::Load<Sound>(L"DragonFire_Jump", L"..\\Resources\\Sound\\SFX\\Dragon\\DragonFire_Jump.wav");
			mSFX->Play(false);
		}

	}

	void AttackFireMarcher::Jump()
	{
		float pos = mSpeed * 2 * Time::DeltaTime();
		Vector2 addPos = Vector2(pos, -pos);
		mTransform->AddPos(addPos);
	}
}
