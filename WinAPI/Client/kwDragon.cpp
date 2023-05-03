#include "kwDragon.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwInput.h"
#include "kwMath.h"
#include "kwSound.h"

#include "kwResources.h"
#include "kwTime.h"

#include "kwObject.h"
#include "kwBaseBullet.h"

#include "kwRing.h"
#include "kwMeteor.h"
#include "kwBossExplosion.h"
#include "kwCuphead.h"

namespace kw
{
	Dragon::Dragon()
		: mState(eDragonState::Intro)
		, mTime(0.0f)
		, mLoopCount(0)
		, mSFX(nullptr)
		, mPrevPatternType(99)
		, mRingDir(Vector2::Zero)
		, mRingStartPos(Vector2(950, 200))
		, mRingCount(0)
	{
		SetHp(5.0f);
	}

	Dragon::~Dragon()
	{

	}

	void Dragon::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Intro", Vector2(0, -100.0), 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Idle", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\MeteorAttack\\Start", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\MeteorAttack\\Loop", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\MeteorAttack\\End", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Peashot\\Start", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Peashot\\Loop", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Peashot\\End", Vector2::Zero, 0.08f);

		mAnimator->GetCompleteEvent(L"FirstPhaseIntro") = std::bind(&Dragon::idleCallback, this);
		mAnimator->GetCompleteEvent(L"MeteorAttackStart") = std::bind(&Dragon::meteorStartCallback, this);
		mAnimator->GetCompleteEvent(L"MeteorAttackLoop") = std::bind(&Dragon::meteorLoopCallback, this);
		mAnimator->GetCompleteEvent(L"MeteorAttackEnd") = std::bind(&Dragon::idleCallback, this);
		mAnimator->GetCompleteEvent(L"PeashotStart") = std::bind(&Dragon::peashotStartCallback, this);
		mAnimator->GetCompleteEvent(L"PeashotLoop") = std::bind(&Dragon::peashotLoopCallback, this);
		mAnimator->GetCompleteEvent(L"PeashotEnd") = std::bind(&Dragon::idleCallback, this);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(200, 600));

		BossMonster::Initialize();
	}
	void Dragon::Update()
	{
		switch (mState)
		{
		case kw::Dragon::eDragonState::Intro:
			break;
		case kw::Dragon::eDragonState::Idle:
			idle();
			break;
		case kw::Dragon::eDragonState::MeteorAttack:
			break;
		case kw::Dragon::eDragonState::Peashot:
			peashot();
			break;
		case kw::Dragon::eDragonState::Die:
			Die();
			break;
		case kw::Dragon::eDragonState::End:
			break;
		default:
			break;
		}
		BossMonster::Update();
	}

	void Dragon::Render(HDC hdc)
	{
		BossMonster::Render(hdc);
	}

	void Dragon::Release()
	{
		BossMonster::Release();
	}

	void Dragon::Die()
	{
		if (mState == eDragonState::Die)
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
			mState = eDragonState::Die;
			//mAnimator->Play(L"CarnationDeath", true);
			mCollider->SetSize(Vector2::Zero);
			BossMonster::Die();
		}
	}

	void Dragon::Intro()
	{
		mState = eDragonState::Intro;
		mAnimator->Play(L"FirstPhaseIntro", true);
	}

	void Dragon::idle()
	{
		mTime += Time::DeltaTime();

		if (mTime > 2.0)
		{
			int type = math::GetRandomNumber(1, 1);
			mTime = 0.0;

			switch (type)
			{
			case 0:
				mState = eDragonState::MeteorAttack;
				mAnimator->Play(L"MeteorAttackStart", true);
				break;
			case 1:
				mState = eDragonState::Peashot;
				mAnimator->Play(L"PeashotStart", true);
				break;
			default:
				break;
			}
		}
	}

	void Dragon::peashot()
	{
		mTime += Time::DeltaTime();

		if (mTime > 1.5)
		{
			mTime = 1.3;

			if (mRingDir == Vector2::Zero)
			{
				Vector2 playerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPos();
				mRingDir = math::Direction(mRingStartPos, playerPos);
			}

			if (mRingCount < 4)
			{
				Ring* ring = object::Instantiate<Ring>(eLayerType::AttackObject, mRingStartPos);
				ring->SetDir(mRingDir);
				mRingCount++;
			}
		}
	}

	void Dragon::idleCallback()
	{
		mTime = 0.0;
		mRingDir = Vector2::Zero;
		mRingCount = 0;

		mState = eDragonState::Idle;
		mAnimator->Play(L"FirstPhaseIdle", true);
	}

	void Dragon::meteorStartCallback()
	{
		mAnimator->Play(L"MeteorAttackLoop", true);
	}

	void Dragon::meteorLoopCallback()
	{
		object::Instantiate<Meteor>(eLayerType::AttackObject, Vector2(mTransform->GetPos().x, mTransform->GetPos().y - 300));
		mAnimator->Play(L"MeteorAttackEnd", true);
	}

	void Dragon::peashotStartCallback()
	{
		mState = eDragonState::Peashot;
		mAnimator->Play(L"PeashotLoop", true);
	}

	void Dragon::peashotLoopCallback()
	{
		if (mLoopCount < 2)
		{
			mAnimator->Play(L"PeashotLoop", true);
		}
		else
		{
			mAnimator->Play(L"PeashotEnd", true);	
			mLoopCount = 0;

			return;
		}
		
		mLoopCount++;
	}
}