#include "kwBaseBullet.h"

#include "kwTime.h"
#include "kwObject.h"
#include "kwResources.h"
#include "kwSound.h"

#include "kwMonster.h"

namespace kw
{
	BaseBullet::BaseBullet()
		: mTime(0.0f)
		, mSpeed(1500.0f)
		, mBulletDestoryEffect(nullptr)
		, mAttackPower(4.0f)
	{

	}

	BaseBullet::~BaseBullet()
	{
		delete mBulletDestoryEffect;
		mBulletDestoryEffect = nullptr;
	}

	void BaseBullet::Initialize()
	{
		SetPivot(ePivot::MiddleCenter);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\Create", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\Loop", Vector2::Zero, 0.06f);

		mAnimator->GetCompleteEvent(L"BulletCreate") = std::bind(&BaseBullet::BulletLoop, this);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(40, 20));

		mAnimator->Play(L"BulletCreate", true);

		GameObject::Initialize();
	}

	void BaseBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 addPos = Vector2::Zero;

		if (GetFlipX() == true)
		{
			addPos.x -= mSpeed * Time::DeltaTime();
		}
		else if (GetFlipX() == false)
		{
			addPos.x += mSpeed * Time::DeltaTime();
		}

		tr->AddPos(addPos);

		mTime += Time::DeltaTime();

		if (mTime > 3.0f)
		{
			BulletDestroy();
		}

		GameObject::Update();
	}
	void BaseBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BaseBullet::Release()
	{
		GameObject::Release();
	}

	void BaseBullet::OnCollisionEnter(Collider* other)
	{
		Monster* monster = dynamic_cast<Monster*>(other->GetOwner());
		if (monster != nullptr)
		{
			monster->ReceiveDamage(mAttackPower);
			mSFX = Resources::Load<Sound>(L"Cuphead_BulletHit", L"..\\Resources\\Sound\\SFX\\Cuphead\\Cuphead_BulletHit.wav");
			mSFX->Play(false);
			BulletDestroy();
		}
	}

	void BaseBullet::BulletLoop()
	{
		mAnimator->Play(L"BulletLoop", true);
	}

	void BaseBullet::BulletDestroy()
	{
		GameObject* destroyEffect = object::Instantiate<GameObject>(eLayerType::Effect, GetComponent<Transform>()->GetPos());
		destroyEffect->SetPivot(ePivot::MiddleCenter);
		destroyEffect->AddComponent<Animator>()->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\End", Vector2::Zero, 0.05f);
		destroyEffect->GetComponent<Animator>()->Play(L"BulletEnd", false);

		object::Destory(this);
	}
}