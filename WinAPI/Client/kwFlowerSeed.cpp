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

		mTransform = AddComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\Vine\\LongStart", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\Vine\\LongEnd", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\Vine\\ShortStart", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\Vine\\ShortEnd", Vector2::Zero, 0.08f);
		mAnimator->GetCompleteEvent(L"VineLongStart") = std::bind(&FlowerSeed::PlayLongVineEndAnim, this);
		mAnimator->GetCompleteEvent(L"VineShortStart") = std::bind(&FlowerSeed::PlayShortVineEndAnim, this);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(50, 50));

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
		mCollider->SetSize(Vector2::Zero);
		mState = eSeedState::Vine;
		mAnimator->Play(L"VineLongStart", true);
	}

	void FlowerSeed::PlayLongVineEndAnim()
	{
		mAnimator->Play(L"VineLongEnd", false);
	}

	void FlowerSeed::PlayShortVineEndAnim()
	{
		mAnimator->Play(L"VineShortEnd", false);
	}
}
