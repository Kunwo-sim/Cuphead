#include "kwMeteor.h"

#include "kwTime.h"
#include "kwObject.h"

#include "kwCuphead.h"


namespace kw
{
	Meteor::Meteor()
		: mSpeed(400.0f)
		, mTime(0)
		, mDirection(0)
	{

	}

	Meteor::~Meteor()
	{

	}

	void Meteor::Initialize()
	{
		SetPivot(ePivot::MiddleCenter);

		mTransform = GetComponent<Transform>();

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Object\\Meteor", Vector2::Zero, 0.06f);
		mAnimator->Play(L"ObjectMeteor", true);

		mCollider = AddComponent<Collider>();

		GameObject::Initialize();
	}

	void Meteor::Update()
	{
		Vector2 pos = mTransform->GetPos();
		pos.x += Time::DeltaTime() * -mSpeed;
		if (mDirection == 0)
		{
			pos.y = sin(pos.x / 140) * 250 + 350;
		}
		else
		{
			pos.y = sin(pos.x / 140) * 250 + 350;
		}
		
		mTransform->SetPos(Vector2(pos.x, pos.y));

		if (mTransform->GetPos().x < -300.0f)
		{
			object::Destory(this);
		}

		mTime += Time::DeltaTime();

		if (mTime > 0.2)
		{
			mTime = 0;
			GameObject* SmokeEffect = object::Instantiate<GameObject>(eLayerType::MeteorEffect, Vector2(mTransform->GetPos()));
			Animator* SmokeAnimator = SmokeEffect->AddComponent<Animator>();
			SmokeAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Object\\MeteorSmoke", Vector2(0.0f, 0.0f), 0.04f);
			SmokeAnimator->Play(L"ObjectMeteorSmoke", false);
		}

		GameObject::Update();
	}

	void Meteor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Meteor::Release()
	{

	}

	void Meteor::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		cuphead->Hit();
	}

	void Meteor::OnCollisionStay(Collider* other)
	{

	}

	void Meteor::OnCollisionExit(Collider* other)
	{

	}
}
