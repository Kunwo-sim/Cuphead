#include "kwCarnation.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwInput.h"
#include "kwMath.h"
#include "kwSound.h"

#include "kwResources.h"
#include "kwTransform.h"
#include "kwAnimator.h"
#include "kwCollider.h"

#include "kwObject.h"
#include "kwBaseBullet.h"
#include "kwBoomerang.h"
#include "kwBlueFlowerSeed.h"
#include "kwPurpleFlowerSeed.h"
#include "kwBossExplosion.h"

namespace kw
{
	Carnation::Carnation()
		: mState(eCarnationState::Intro)
		, mTime(0.0f)
		, mLoopCount(0)
		, mSFX(nullptr)
		, mPrevPatternType(99)
	{
		SetHp(5.0f);
	}

	Carnation::~Carnation()
	{

	}

	void Carnation::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Intro", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Idle", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\FaceAttack\\HighStart", Vector2(-400.0f, 0.0f), 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\FaceAttack\\LowStart", Vector2(-400.0f, 0.0f), 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\FiringStart", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\FiringLoop", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\FiringEnd", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\CreatingStart", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\CreatingEnd", Vector2::Zero, 0.06f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Death", Vector2::Zero, 0.06f);

		mAnimator->GetCompleteEvent(L"CarnationIntro") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"FaceAttackHighStart") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"FaceAttackLowStart") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationFiringStart") = std::bind(&Carnation::firingStartCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationFiringLoop") = std::bind(&Carnation::firingLoopCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationFiringEnd") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationCreatingStart") = std::bind(&Carnation::creatingStartCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationCreatingEnd") = std::bind(&Carnation::idleCallback, this);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(200, 600));

		BossMonster::Initialize();
	}
	void Carnation::Update()
	{
		switch (mState)
		{
		case kw::Carnation::eCarnationState::Idle:
			idle();
			break;
		case kw::Carnation::eCarnationState::Die:
			Die();
		default:
			break;
		}

		BossMonster::Update();
	}

	void Carnation::Render(HDC hdc)
	{
		BossMonster::Render(hdc);
	}

	void Carnation::Release()
	{
		BossMonster::Release();
	}

	void Carnation::Die()
	{
		if (mState == eCarnationState::Die)
		{
			mTime += Time::DeltaTime();
			if (mTime > 0.4f)
			{
				mTime = 0.0f;
				Vector2 effectPos = Vector2::Zero;
				Vector2 bossPos =  mTransform->GetPos();
				effectPos.x = math::GetRandomNumber(bossPos.x - 200, bossPos.x + 200);
				effectPos.y = math::GetRandomNumber(bossPos.y - 200, bossPos.y + 200);
				object::Instantiate<BossExplosion>(eLayerType::Effect, effectPos);
			}
		}
		else
		{
			mState = eCarnationState::Die;
			mAnimator->Play(L"CarnationDeath", true);
			mCollider->SetSize(Vector2::Zero);
			BossMonster::Die();
		}
	}

	void Carnation::idle()
	{
		mTime += Time::DeltaTime();

		if (mTime > 3.0f)
		{
			mTime = 0.0f;
			int type = math::GetRandomNumber((int)eCarnationState::FaceAttack, (int)eCarnationState::End - 1);
			while (type == mPrevPatternType)
			{
				type = math::GetRandomNumber((int)eCarnationState::FaceAttack, (int)eCarnationState::End - 1);
			}

			switch (type)
			{
			case (int)eCarnationState::FaceAttack:
					faceAttack();
					break;
			case (int)eCarnationState::Firing:
					firing();
					break;
			case (int)eCarnationState::Creating:
					creating();
					break;
			default:
				break;
			}
		}
	}

	void Carnation::Intro()
	{
		mAnimator->Play(L"CarnationIntro", true);

		mSFX = Resources::Load<Sound>(L"Carnation_Intro", L"..\\Resources\\Sound\\SFX\\Carnation\\Intro.wav");
		mSFX->Play(false);
	}

	void Carnation::faceAttack()
	{
		mState = eCarnationState::FaceAttack;
		mPrevPatternType = (int)eCarnationState::FaceAttack;

		int type = math::GetRandomNumber(0, 1);

		if (type == 0)
			mAnimator->Play(L"FaceAttackHighStart", true);
		else
			mAnimator->Play(L"FaceAttackLowStart", true);
		
		 mSFX = Resources::Load<Sound>(L"Carnation_FaceAttack", L"..\\Resources\\Sound\\SFX\\Carnation\\FaceAttack.wav");
		 mSFX->Play(false);
	}

	void Carnation::firing()
	{
		mState = eCarnationState::Firing;
		mPrevPatternType = (int)eCarnationState::Firing;
		mAnimator->Play(L"CarnationFiringStart", true);

		mSFX = Resources::Load<Sound>(L"Carnation_Gattling_Start", L"..\\Resources\\Sound\\SFX\\Carnation\\Gattling_Start.wav");
		mSFX->Play(false);
	}

	void Carnation::creating()
	{
		mState = eCarnationState::Creating;
		mPrevPatternType = (int)eCarnationState::Creating;
		mAnimator->Play(L"CarnationCreatingStart", true);

		mSFX = Resources::Load<Sound>(L"Carnation_Creating", L"..\\Resources\\Sound\\SFX\\Carnation\\Creating.wav");
		mSFX->Play(false);
	}

	void Carnation::idleCallback()
	{
		mState = eCarnationState::Idle;
		mAnimator->Play(L"CarnationIdle", true);
	}

	void Carnation::creatingStartCallback()
	{
		object::Instantiate<Boomerang>(eLayerType::AttackObject);
		mAnimator->Play(L"CarnationCreatingEnd", true);
	}

	void Carnation::firingStartCallback()
	{
		mAnimator->Play(L"CarnationFiringLoop", true);

		mSFX = Resources::Load<Sound>(L"Carnation_Gattling_Loop", L"..\\Resources\\Sound\\SFX\\Carnation\\Gattling_Loop.wav");
		mSFX->Play(true);
	}

	void Carnation::firingLoopCallback()
	{
		if (mLoopCount >= 8)
		{
			mLoopCount = 0;
			mAnimator->Play(L"CarnationFiringEnd", true);

			mSFX->Stop(true);
			mSFX = Resources::Load<Sound>(L"Carnation_Gattling_End", L"..\\Resources\\Sound\\SFX\\Carnation\\Gattling_End.wav");
			mSFX->Play(false);

			return;
		}
		else
		{
			mAnimator->Play(L"CarnationFiringLoop", true);
		}

		if (mLoopCount % 2 == 0)
		{
			int seedType = math::GetRandomNumber(0, 1);
			GameObject* seed = nullptr;
			switch (seedType)
			{
			case 0:
				seed = object::Instantiate<BlueFlowerSeed>(eLayerType::AttackObject);
				break;
			case 1:
				seed = object::Instantiate<PurpleFlowerSeed>(eLayerType::AttackObject);
			default:
				break;
			}

			int xPos = math::GetRandomNumber(100, 800);
			seed->GetComponent<Transform>()->SetPos(Vector2(xPos, 0));
		}		

		mLoopCount++;
	}
}