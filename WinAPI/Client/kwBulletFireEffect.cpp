#include "kwBulletFireEffect.h"
#include "kwTransform.h"
#include "kwTime.h"
#include "kwObject.h"
#include "kwCollider.h"

namespace kw
{
	BulletFireEffect::BulletFireEffect()
	{

	}

	BulletFireEffect::~BulletFireEffect()
	{

	}

	void BulletFireEffect::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\Spawn", Vector2::Zero, 0.05f);
		mAnimator->GetEndEvent(L"BulletSpawn") = std::bind(&BulletFireEffect::BulletFireEnd, this);
		mAnimator->Play(L"BulletSpawn", true);

		GameObject::Initialize();
	}

	void BulletFireEffect::Update()
	{
		mTime += Time::DeltaTime();
		if (mTime > 0.2f)
		{
			BulletFireEnd();
		}
		GameObject::Update();
	}
	void BulletFireEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BulletFireEffect::Release()
	{
		GameObject::Release();
	}

	void BulletFireEffect::BulletFireEnd()
	{
		object::Destory(this);
	}
}