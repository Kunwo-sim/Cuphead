#include "kwBaseBullet.h"
#include "kwTransform.h"
#include "kwTime.h"
#include "kwObject.h"
#include "kwCollider.h"

namespace kw
{
	BaseBullet::BaseBullet()
		: mTime(0.0f)
		, mSpeed(1500.0f)
	{

	}

	BaseBullet::~BaseBullet()
	{

	}

	void BaseBullet::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		//mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\Create", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\LoopLeft", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\LoopRight", Vector2::Zero, 0.08f);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(40, 20));

		GameObject::Initialize();
	}

	void BaseBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (GetDirection() == eDirection::Left)
		{
			pos.x -= mSpeed * Time::DeltaTime();
			mAnimator->Play(L"BulletLoopLeft", true);
		}
		else if (GetDirection() == eDirection::Right)
		{
			pos.x += mSpeed * Time::DeltaTime();
			mAnimator->Play(L"BulletLoopRight", false);
		}

		tr->SetPos(pos);

		mTime += Time::DeltaTime();
		if (mTime > 5.0f)
		{
			object::Destory(this);
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
		object::Destory(this);
	}
}