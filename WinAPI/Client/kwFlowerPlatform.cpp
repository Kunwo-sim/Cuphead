#include "kwFlowerPlatform.h"
#include "kwTransform.h"
#include "kwAnimator.h"

#include "kwObject.h"
#include "kwGround.h"

namespace kw
{
	FlowerPlatform::FlowerPlatform()
		: mTransform(nullptr)
		, mAnimator(nullptr)
		, mCollider(nullptr)
		, mGround(nullptr)
		, mPlatformType(PlatformType::A)
		, mPropellor(nullptr)
		, mPropllerOffset(Vector2(5.0f, 45.0f))
	{
	}

	FlowerPlatform::~FlowerPlatform()
	{
	}

	void FlowerPlatform::Initialize()
	{
		SetPivot(GameObject::ePivot::MiddleCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\ShootLeft", Vector2(-14.0f, 0.0f), 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Platform\\A", Vector2(0.0f, 0.0f), 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Platform\\B", Vector2(0.0f, 0.0f), 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Platform\\C", Vector2(0.0f, 0.0f), 0.07f);

		switch (mPlatformType)
		{
		case kw::FlowerPlatform::PlatformType::A:
			mAnimator->Play(L"PlatformA", true);
			break;
		case kw::FlowerPlatform::PlatformType::B:
			mAnimator->Play(L"PlatformB", true);
			break;
		case kw::FlowerPlatform::PlatformType::C:
			mAnimator->Play(L"PlatformC", true);
			break;
		default:
			break;
		}

		mGround = object::Instantiate<Ground>(eLayerType::Ground, mTransform->GetPos());
		mGround->SetColliderSize(Vector2(60.0f, 65.0f));

		mPropellor = object::Instantiate<GameObject>(eLayerType::Ground, mTransform->GetPos() + mPropllerOffset);
		Animator* PropellorAnim = mPropellor->AddComponent<Animator>();
		PropellorAnim->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Platform\\Propellor", Vector2::Zero, 0.07f);
		PropellorAnim->Play(L"PlatformPropellor", true);

		GameObject::Initialize();
	}

	void FlowerPlatform::Update()
	{
		mPropellor->GetComponent<Transform>()->SetPos(mTransform->GetPos() + mPropllerOffset);
		mGround->GetComponent<Transform>()->SetPos(mTransform->GetPos() + Vector2(0.0f, 50.0f));

		GameObject::Update();
	}

	void FlowerPlatform::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FlowerPlatform::Release()
	{

	}

	void FlowerPlatform::OnCollisionEnter(Collider* other)
	{

	}

	void FlowerPlatform::OnCollisionStay(Collider* other)
	{

	}

	void FlowerPlatform::OnCollisionExit(Collider* other)
	{

	}
}
