#include "kwVenus.h"

#include "kwSceneManager.h"

#include "kwTime.h"
#include "kwCuphead.h"

namespace kw
{
	Venus::Venus()
		: mSpeed(100.0f)
		, mState(eVenusState::Create)
	{
		SetHp(1.0f);
	}

	Venus::~Venus()
	{

	}

	void Venus::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\BlueSeed\\Venus\\Create", Vector2::Zero, 0.04f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\BlueSeed\\Venus\\Idle", Vector2::Zero, 0.04f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\BlueSeed\\Venus\\Die", Vector2::Zero, 0.04f);
		mAnimator->GetCompleteEvent(L"VenusCreate") = std::bind(&Venus::playIdleAnim, this);
		mAnimator->Play(L"VenusCreate", true);

		mCollider = AddComponent<Collider>();
		

		Monster::Initialize();
	}

	void Venus::Update()
	{
		if (mState == eVenusState::Idle)
		{
			Cuphead* player = SceneManager::GetPlayer();
			Vector2 playerPos = player->GetComponent<Transform>()->GetPos();
			Vector2 dir = math::Direction(mTransform->GetPos(), playerPos);
			mTransform->AddPos(dir * mSpeed * Time::DeltaTime());

			if (dir.x > 0.0f)
			{
				SetFlipX(true);
			}
			else
			{
				SetFlipX(false);
			}
		}

		Monster::Update();
	}

	void Venus::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void Venus::Release()
	{

	}

	void Venus::Die()
	{
		if (mState == eVenusState::Die)
			return;

		mState = eVenusState::Die;
		mCollider->SetSize(Vector2::Zero);
		mAnimator->Play(L"VenusDie", false);
		Monster::Die();
	}

	void Venus::playIdleAnim()
	{
		mCollider->SetSize(Vector2(50.0f, 50.0f));
		mState = eVenusState::Idle;
		mAnimator->Play(L"VenusIdle", true);
	}
}
