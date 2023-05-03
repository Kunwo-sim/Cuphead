#include "kwBulletFireEffect.h"

#include "kwSceneManager.h"
#include "kwObject.h"

#include "kwCuphead.h"

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
		SetPivot(ePivot::MiddleCenter);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Bullet\\Spawn", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\SpreadShot\\Spawn", Vector2::Zero, 0.05f);

		Cuphead::eBulletType bulletType = SceneManager::GetPlayer()->GetBulletType();
		switch (bulletType)
		{
			case Cuphead::eBulletType::PeaShot:
				mAnimator->Play(L"BulletSpawn", false);
				break;
			case Cuphead::eBulletType::SpreadShot:
				mAnimator->Play(L"SpreadShotSpawn", false);
				break;
		}

		GameObject::Initialize();
	}

	void BulletFireEffect::Update()
	{
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
}