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
#include "kwDragon2.h"

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
		SetHp(200.0f);
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
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\MeteorAttack\\Loop", Vector2(-25, -15), 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\MeteorAttack\\End", Vector2(-25, -15), 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Peashot\\Start", Vector2(30, -10), 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Peashot\\Loop", Vector2(30, -10), 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Dragon\\FirstPhase\\Peashot\\End", Vector2(30, -10), 0.06f);

		mAnimator->GetCompleteEvent(L"FirstPhaseIntro") = std::bind(&Dragon::idleCallback, this);
		mAnimator->GetCompleteEvent(L"MeteorAttackStart") = std::bind(&Dragon::meteorStartCallback, this);
		mAnimator->GetCompleteEvent(L"MeteorAttackLoop") = std::bind(&Dragon::meteorLoopCallback, this);
		mAnimator->GetCompleteEvent(L"MeteorAttackEnd") = std::bind(&Dragon::idleCallback, this);
		mAnimator->GetCompleteEvent(L"PeashotStart") = std::bind(&Dragon::peashotStartCallback, this);
		mAnimator->GetCompleteEvent(L"PeashotLoop") = std::bind(&Dragon::peashotLoopCallback, this);
		mAnimator->GetCompleteEvent(L"PeashotEnd") = std::bind(&Dragon::idleCallback, this);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(200, 1200));

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
			mTransform->AddPos(Vector2(Time::DeltaTime() * 200.0f, 0.0f));

			if (mTransform->GetPos().x > 1500.0f)
			{
				object::Instantiate<Dragon2>(eLayerType::Monster, Vector2(-100.0f, 720.0f));
				object::Destory(this);
			}
		}
		else
		{
			mState = eDragonState::Die;
			mAnimator->Play(L"FirstPhaseIdle", true);
			mCollider->SetSize(Vector2::Zero);
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
			int type = math::GetRandomNumber(0, 1);
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
				playerPos.y -= 100;
				mRingDir = math::Direction(mRingStartPos, playerPos);
			}

			if (mRingCount < 4)
			{
				Ring* ring = object::Instantiate<Ring>(eLayerType::AttackObject, mRingStartPos);
				ring->SetDir(mRingDir);

				if (mRingCount == 3)
				{
					ring->SetPinkRing();
				}

				mRingCount++;

				mSFX = Resources::Load<Sound>(L"Peashot_Shoot", L"..\\Resources\\Sound\\SFX\\Dragon\\Peashot_Shoot.wav");
				mSFX->Play(false);
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
		mSFX = Resources::Load<Sound>(L"Meteor_Start", L"..\\Resources\\Sound\\SFX\\Dragon\\Meteor_Start.wav");
		mSFX->Play(false);
	}

	void Dragon::meteorLoopCallback()
	{
		object::Instantiate<Meteor>(eLayerType::AttackObject, Vector2(mTransform->GetPos().x - 200, mTransform->GetPos().y));
		object::Instantiate<Meteor>(eLayerType::AttackObject, Vector2(mTransform->GetPos().x - 200, mTransform->GetPos().y))->SetDirection(1);
		mAnimator->Play(L"MeteorAttackEnd", true);

		mSFX = Resources::Load<Sound>(L"Meteor_Attack", L"..\\Resources\\Sound\\SFX\\Dragon\\Meteor_Attack.wav");
		mSFX->Play(false);
	}

	void Dragon::peashotStartCallback()
	{
		mState = eDragonState::Peashot;
		mAnimator->Play(L"PeashotLoop", true);

		mSFX = Resources::Load<Sound>(L"Peashot_In", L"..\\Resources\\Sound\\SFX\\Dragon\\Peashot_In.wav");
		mSFX->Play(false);
	}

	void Dragon::peashotLoopCallback()
	{
		if (mLoopCount < 2)
		{
			mAnimator->Play(L"PeashotLoop", true);
		}
		else
		{
			mSFX = Resources::Load<Sound>(L"Peashot_Out", L"..\\Resources\\Sound\\SFX\\Dragon\\Peashot_Out.wav");
			mSFX->Play(false);
			mAnimator->Play(L"PeashotEnd", true);	
			mLoopCount = 0;

			return;
		}
		
		mLoopCount++;
	}
}