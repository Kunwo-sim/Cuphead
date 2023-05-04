#include "kwDragon2.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwInput.h"
#include "kwMath.h"
#include "kwSound.h"

#include "kwResources.h"
#include "kwTime.h"

#include "kwObject.h"

#include "kwCuphead.h"
#include "kwTounge.h"
#include "kwFireMarcher.h"
#include "kwAttackFireMarcher.h"
#include "kwBossExplosion.h"

namespace kw
{
	Dragon2::Dragon2()
		: mState(eDragon2State::Intro)
		, mTime(0.0f)
		, mSFX(nullptr)
		, mSpeed(200.0f)
		, mCnt(0)
	{
		SetHp(200.0f);
	}

	Dragon2::~Dragon2()
	{

	}

	void Dragon2::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Intro", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Idle", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\SecondPhase\\Death", Vector2(-100.0f, 120.0f), 0.06f);

		mAnimator->GetCompleteEvent(L"SecondPhaseIntro") = std::bind(&Dragon2::idleCallback, this);

		mAnimator->Play(L"SecondPhaseIntro", true);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(200, 600));

		BossMonster::Initialize();
	}
	void Dragon2::Update()
	{
		switch (mState)
		{
		case kw::Dragon2::eDragon2State::Intro:
			intro();
			break;
		case kw::Dragon2::eDragon2State::Idle:
			idle();
			break;
		case kw::Dragon2::eDragon2State::Die:
			Die();
			break;
		case kw::Dragon2::eDragon2State::End:
			break;
		default:
			break;
		}
		BossMonster::Update();
	}

	void Dragon2::Render(HDC hdc)
	{
		BossMonster::Render(hdc);
	}

	void Dragon2::Release()
	{
		BossMonster::Release();
	}

	void Dragon2::Die()
	{
		if (mState == eDragon2State::Die)
		{
			mTime += Time::DeltaTime();
			if (mTime > 0.4f)
			{
				mTime = 0.0f;
				Vector2 effectPos = Vector2::Zero;
				Vector2 bossPos = mTransform->GetPos();
				effectPos.x = math::GetRandomNumber(bossPos.x - 200, bossPos.x + 200);
				effectPos.y = math::GetRandomNumber(bossPos.y - 200, bossPos.y + 200);
				object::Instantiate<BossExplosion>(eLayerType::Effect, effectPos);
			}
		}
		else
		{
			mState = eDragon2State::Die;
			mAnimator->Play(L"SecondPhaseDeath", true);
			mCollider->SetSize(Vector2::Zero);
			BossMonster::Die();
		}
	}

	void Dragon2::Intro()
	{
		mState = eDragon2State::Intro;
		mAnimator->Play(L"SecondPhaseIntro", true);
	}

	void Dragon2::intro()
	{
		if (mTransform->GetPos().x < 100.0f)
		{
			float xPos = Time::DeltaTime() * mSpeed;
			mTransform->AddPos(Vector2(xPos, 0.0f));
		}
		else
		{
			mTransform->SetPos(Vector2(100.0f, mTransform->GetPos().y));
		}
	}

	void Dragon2::idle()
	{
		mTime += Time::DeltaTime();

		if (mTime > 0.7f)
		{
			mTime = 0.0f;
			if (mCnt == 3)
			{
				object::Instantiate<AttackFireMarcher>(eLayerType::AttackObject, Vector2(200.0f, 680.0f));
				mCnt = 0;
			}
			else
			{
				object::Instantiate<FireMarcher>(eLayerType::AttackObject, Vector2(200.0f, 680.0f));
				mCnt++;
			}
			
		}
	}

	void Dragon2::idleCallback()
	{
		mState = eDragon2State::Idle;
		mAnimator->Play(L"SecondPhaseIdle", true);

		object::Instantiate<Tounge>(eLayerType::Effect, Vector2(870.0f, 680.0f));
	}
}