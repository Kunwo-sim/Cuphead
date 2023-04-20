#include "kwBossExplosion.h"

#include "kwTime.h"
#include "kwObject.h"

namespace kw
{
	BossExplosion::BossExplosion()
	{

	}

	BossExplosion::~BossExplosion()
	{

	}

	void BossExplosion::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\BossExplosion", Vector2(0.0f, -200.0f), 0.05f);
		mAnimator->Play(L"StageBossExplosion", false);

		GameObject::Initialize();
	}

	void BossExplosion::Update()
	{
		GameObject::Update();
	}
	void BossExplosion::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BossExplosion::Release()
	{
		GameObject::Release();
	}
}