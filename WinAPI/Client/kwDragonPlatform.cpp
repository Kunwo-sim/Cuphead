#include "kwDragonPlatform.h"
#include "kwTransform.h"
#include "kwAnimator.h"

#include "kwTime.h"
#include "kwObject.h"
#include "kwGround.h"

#include "kwCuphead.h"

namespace kw
{
	DragonPlatform::DragonPlatform()
		: mGround(nullptr)
		, mAddPos(Vector2::Zero)
		, mPlatformType(PlatformType::A)
		, mSpeed(200.0f)
	{
	}

	DragonPlatform::~DragonPlatform()
	{
	}

	void DragonPlatform::Initialize()
	{
		SetPivot(GameObject::ePivot::MiddleCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\Platform\\A\\Idle", Vector2(0.0f, 0.0f), 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\Platform\\B\\Idle", Vector2(0.0f, 0.0f), 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\Platform\\C\\Idle", Vector2(0.0f, 0.0f), 0.07f);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(110.0f, 30.0f));

		mGround = object::Instantiate<Ground>(eLayerType::Ground, mTransform->GetPos());
		mGround->SetPivot(GameObject::ePivot::MiddleCenter);
		mGround->SetColliderSize(Vector2(110.0f, 30.0f));

		GameObject::Initialize();
	}

	void DragonPlatform::Update()
	{
		mGround->GetComponent<Transform>()->SetPos(mTransform->GetPos());
		mAddPos = Vector2(-mSpeed * Time::DeltaTime(), 0.0f);
		mTransform->AddPos(mAddPos);

		if (mTransform->GetPos().x < -300.0f)
		{
			object::Destory(this);
		}

		GameObject::Update();
	}

	void DragonPlatform::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DragonPlatform::Release()
	{

	}

	void DragonPlatform::OnCollisionEnter(Collider* other)
	{
		Cuphead* player = dynamic_cast<Cuphead*>(other->GetOwner());
		if (player != nullptr)
		{
			player->GetComponent<Transform>()->AddPos(mAddPos);
		}

		GameObject::OnCollisionEnter(other);
	}

	void DragonPlatform::OnCollisionStay(Collider* other)
	{
		Cuphead* player = dynamic_cast<Cuphead*>(other->GetOwner());
		if (player != nullptr)
		{
			player->GetComponent<Transform>()->AddPos(mAddPos);
		}

		GameObject::OnCollisionStay(other);
	}

	void DragonPlatform::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}

	void DragonPlatform::SetPlatformType(PlatformType type)
	{
		mPlatformType = type;

		switch (mPlatformType)
		{
		case kw::DragonPlatform::PlatformType::A:
			mAnimator->Play(L"AIdle", true);
			break;
		case kw::DragonPlatform::PlatformType::B:
			mAnimator->Play(L"BIdle", true);
			break;
		case kw::DragonPlatform::PlatformType::C:
			mAnimator->Play(L"CIdle", true);
			break;
		default:
			break;
		}
	}
}
