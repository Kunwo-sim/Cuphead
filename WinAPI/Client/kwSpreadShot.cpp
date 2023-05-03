#include "kwSpreadShot.h"

#include "kwTime.h"
#include "kwObject.h"

#include "kwMonster.h"

namespace kw
{
	SpreadShot::SpreadShot()
		: mTime(0.0f)
		, mSpeed(1500.0f)
		, mBulletDestoryEffect(nullptr)
		, mBulletHitEffect(nullptr)
		, mAttackPower(1.25f)
		, mDirection(Vector2::Zero)
	{

	}

	SpreadShot::~SpreadShot()
	{
		delete mBulletDestoryEffect;
		delete mBulletHitEffect;
		mBulletDestoryEffect = nullptr;
		mBulletHitEffect = nullptr;
	}

	void SpreadShot::Initialize()
	{
		SetPivot(ePivot::MiddleCenter);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\SpreadShot\\Idle", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\SpreadShot\\IdleUp", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\SpreadShot\\IdleMidUp", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\SpreadShot\\IdleDown", Vector2::Zero, 0.02f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\SpreadShot\\IdleMidDown", Vector2::Zero, 0.02f);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(40, 20));

		mAnimator->Play(L"SpreadShotIdle", true);

		GameObject::Initialize();
	}

	void SpreadShot::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 addPos = mDirection * Time::DeltaTime() * mSpeed;

		tr->AddPos(addPos);

		mTime += Time::DeltaTime();

		if (mTime > 0.2f)
		{
			BulletDestroy();
		}

		GameObject::Update();
	}
	void SpreadShot::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SpreadShot::Release()
	{
		GameObject::Release();
	}

	void SpreadShot::OnCollisionEnter(Collider* other)
	{
		Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
		if (monster != nullptr)
		{
			monster->ReceiveDamage(mAttackPower);
			
			GameObject* destroyHitEffect = object::Instantiate<GameObject>(eLayerType::Effect, GetComponent<Transform>()->GetPos());
			destroyHitEffect->SetPivot(ePivot::MiddleCenter);
			destroyHitEffect->AddComponent<Animator>()->CreateAnimations(L"..\\Resources\\Stage\\SpreadShot\\Hit", Vector2::Zero, 0.05f);
			destroyHitEffect->GetComponent<Animator>()->Play(L"SpreadShotHit", false);

			object::Destory(this);
		}
	}

	void SpreadShot::BulletDestroy()
	{
		GameObject* destroyEffect = object::Instantiate<GameObject>(eLayerType::Effect, GetComponent<Transform>()->GetPos());
		destroyEffect->SetPivot(ePivot::MiddleCenter);
		destroyEffect->AddComponent<Animator>()->CreateAnimations(L"..\\Resources\\Stage\\SpreadShot\\End", Vector2::Zero, 0.05f);
		destroyEffect->GetComponent<Animator>()->Play(L"SpreadShotEnd", false);

		object::Destory(this);
	}

	void SpreadShot::SetSpreadDirection(int direction)
	{
		switch (direction)
		{
		case 0:
			mDirection = Vector2(1, 0);
			mAnimator->Play(L"SpreadShotIdle", true);
			break;
		case 1:
			mDirection = Vector2(100, 58);
			mAnimator->Play(L"SpreadShotIdleDown", true);
			break;
		case 2:
			mDirection = Vector2(100, 27);
			mAnimator->Play(L"SpreadShotIdleMidDown", true);
			break;
		case 3:
			mDirection = Vector2(100, -58);
			mAnimator->Play(L"SpreadShotIdleUp", true);
			break;
		case 4:
			mDirection = Vector2(100, -27);
			mAnimator->Play(L"SpreadShotIdleMidUp", true);
			break;
		default:
			break;
		}

		mDirection.Normalize();
	}

	void SpreadShot::SetDirectionFlip()
	{
		mDirection.x *= -1;
	}
}