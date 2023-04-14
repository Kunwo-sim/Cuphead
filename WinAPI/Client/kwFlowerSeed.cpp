#include "kwFlowerSeed.h"

#include "kwTime.h"
#include "kwObject.h"

#include "kwTransform.h"
#include "kwAnimator.h"
#include "kwCollider.h"

namespace kw
{
	FlowerSeed::FlowerSeed()
		: mState(eSeedState::Fall)
		, mSpeed(400.0f)
	{

	}

	FlowerSeed::~FlowerSeed()
	{

	}

	void FlowerSeed::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\Vine\\Long", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\Vine\\Short", Vector2::Zero, 0.08f);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(50, 50));

		AttackObject::Initialize();
	}

	void FlowerSeed::Update()
	{
		Vector2 pos = mTransform->GetPos();
		switch (mState)
		{
		case kw::FlowerSeed::eSeedState::Fall:
			pos.y += mSpeed * Time::DeltaTime();
			mTransform->SetPos(pos);

			if (pos.y > 620.0f)
			{
				mState = eSeedState::Grow;
				PlayGrowAnim();
			}
			break;
		case kw::FlowerSeed::eSeedState::Grow:
			break;
		case kw::FlowerSeed::eSeedState::Vine:
			break;
		default:
			break;
		}

		AttackObject::Update();
	}

	void FlowerSeed::Render(HDC hdc)
	{
		AttackObject::Render(hdc);
	}

	void FlowerSeed::Release()
	{

	}

	void FlowerSeed::PlayFallAnim()
	{

	}

	void FlowerSeed::PlayGrowAnim()
	{

	}

	void FlowerSeed::CreateVine()
	{
		mState = eSeedState::Vine;
		mAnimator->Play(L"VineLong", false);
	}
}
