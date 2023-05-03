#include "kwBoomerang.h"
#include "kwTransform.h"
#include "kwAnimator.h"
#include "kwCollider.h"
#include "kwObject.h"
#include "kwTime.h"
#include "kwResources.h"
#include "kwSound.h"

namespace kw
{
	Boomerang::Boomerang()
		: mSpawnTime(0.0f)
		, mSpeed(600.0f)
		, mSFX(nullptr)
	{

	}

	Boomerang::~Boomerang()
	{

	}

	void Boomerang::Initialize()
	{
		SetPivot(ePivot::MiddleCenter);

		mTransform = GetComponent<Transform>();
		mTransform->SetPos(Vector2(900.0f, 300.0f));
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\Boomerang", Vector2::Zero, 0.04f);
		mAnimator->Play(L"ObjectBoomerang", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(200, 100));

		AttackObject::Initialize();
	}

	void Boomerang::Update()
	{
		mSpawnTime += Time::DeltaTime();
		Vector2 pos = mTransform->GetPos();

		// 0.5 4.5 
		if (mSpawnTime > 8.0f)
		{
			object::Destory(this);
		}
		else if (mSpawnTime > 2.7f)
		{
			if (mSFX == nullptr)
			{
				mSFX = Resources::Load<Sound>(L"Boomerang", L"..\\Resources\\Sound\\SFX\\Carnation\\Boomerang.wav");
				mSFX->Play(false);
			}
			
			pos.x += mSpeed * Time::DeltaTime();
			pos.y = 525.0f;
		}
		else if (mSpawnTime > 2.0f)
		{
			mSFX = nullptr;
			pos.x -= mSpeed * Time::DeltaTime();
			pos.y = 300.0f;
		}
		else if (mSpawnTime > 0.7f)
		{
			if (mSFX == nullptr)
			{
				mSFX = Resources::Load<Sound>(L"Boomerang", L"..\\Resources\\Sound\\SFX\\Carnation\\Boomerang.wav");
				mSFX->Play(false);
			}

			pos.x -= mSpeed * Time::DeltaTime();
			pos.y = 300.0f;
		}		

		mTransform->SetPos(pos);

		AttackObject::Update();
	}

	void Boomerang::Render(HDC hdc)
	{
		AttackObject::Render(hdc);
	}

	void Boomerang::Release()
	{

	}
}
