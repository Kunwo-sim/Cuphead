#include "kwBaseBullet.h"
#include "kwTransform.h"
#include "kwTime.h"
#include "kwObject.h"
#include "kwCollider.h"

namespace kw
{
	BaseBullet::BaseBullet()
		: mTime(0.0f)
		, mAnimator(nullptr)
		, mSpeed(1500.0f)
		, mBulletDestoryEffect(nullptr)
	{

	}

	BaseBullet::~BaseBullet()
	{
		delete mBulletDestoryEffect;
		mBulletDestoryEffect = nullptr;
	}

	void BaseBullet::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\Create", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\Loop", Vector2::Zero, 0.08f);

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
		BulletDestroy();
	}

	void BaseBullet::BulletLoop()
	{
		mAnimator->Play(L"BulletLoop", true);
	}

	void BaseBullet::BulletDestroy()
	{
		GameObject* destroyEffect = object::Instantiate<GameObject>(eLayerType::Effect, GetComponent<Transform>()->GetPos());
		destroyEffect->AddComponent<Animator>()->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\End", Vector2::Zero, 0.05f);
		destroyEffect->GetComponent<Animator>()->Play(L"BulletEnd", false);

		object::Destory(this);
	}
}