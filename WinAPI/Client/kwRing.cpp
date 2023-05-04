#include "kwRing.h"

#include "kwSceneManager.h"
#include "kwTime.h"
#include "kwObject.h"
#include "kwParryObject.h"

#include "kwCuphead.h"

namespace kw
{
	Ring::Ring()
		: mSpeed(600.0f)
		, mDirection(Vector2::Zero)
		, mParryObject(nullptr)
	{

	}

	Ring::~Ring()
	{

	}

	void Ring::Initialize()
	{
		SetPivot(ePivot::MiddleCenter);

		mTransform = GetComponent<Transform>();

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Object\\GreenRing", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Object\\PinkRing", Vector2::Zero, 0.06f);
		mAnimator->Play(L"ObjectGreenRing", true);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(70, 100));

		GameObject::Initialize();
	}

	void Ring::Update()
	{
		Vector2 pos = mTransform->GetPos();
		pos.x += mDirection.x * Time::DeltaTime() * mSpeed;
		pos.y += mDirection.y * Time::DeltaTime() * mSpeed;
		mTransform->SetPos(pos);

		if (pos.x < -400.0f)
		{
			object::Destory(this);
			if (mParryObject != nullptr)
			{
				object::Destory(mParryObject);
			}
		}

		GameObject::Update();
	}

	void Ring::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ring::Release()
	{

	}

	void Ring::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		cuphead->Hit();
	}

	void Ring::SetPinkRing()
	{
		mAnimator->Play(L"ObjectPinkRing", true);
		mParryObject = object::Instantiate<ParryObject>(eLayerType::ParryObject, mTransform->GetPos());
		mParryObject->SetOwner(this);
		mParryObject->SetColliderSize(Vector2(200.0f, 300.0f));
	}
}
