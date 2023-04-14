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

namespace kw
{
	Carnation::Carnation()
		: mState(eCarnationState::Intro)
		, mTime(0.0f)
		, mLoopCount(0)
		, mSFX(nullptr)
	{

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

		mAnimator->GetCompleteEvent(L"CarnationIntro") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"FaceAttackHighStart") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"FaceAttackLowStart") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationFiringStart") = std::bind(&Carnation::firingStartCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationFiringLoop") = std::bind(&Carnation::firingLoopCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationFiringEnd") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationCreatingStart") = std::bind(&Carnation::creatingStartCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationCreatingEnd") = std::bind(&Carnation::idleCallback, this);

		mAnimator->Play(L"CarnationIntro", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(200, 600));

		GameObject::Initialize();
	}
	void Carnation::Update()
	{
		switch (mState)
		{
		case kw::Carnation::eCarnationState::Idle:
			idle();
			break;
		default:
			break;
		}

		GameObject::Update();
	}

	void Carnation::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Carnation::Release()
	{
		GameObject::Release();
	}

	void Carnation::idle()
	{
		mTime += Time::DeltaTime();

		if (mTime > 3.0f)
		{
			mTime = 0.0f;
			firing();
			//int type = math::GetRandomNumber(0, 2);
			//switch (type)
			//{
			//	case 0:
			//		faceAttack();
			//		break;
			//	case 1:
			//		firing();
			//		break;
			//	case 2:
			//		creating();
			//		break;
			//default:
			//	break;
			//}
		}
	}

	void Carnation::intro()
	{

	}

	void Carnation::faceAttack()
	{
		mState = eCarnationState::FaceAttack;

		int type = math::GetRandomNumber(0, 1);

		if (type == 0)
			mAnimator->Play(L"FaceAttackHighStart", true);
		else
			mAnimator->Play(L"FaceAttackLowStart", true);
		
		 mSFX = Resources::Load<Sound>(L"FaceAttack", L"..\\Resources\\Sound\\SFX\\FaceAttack.wav");
		 mSFX->Play(false);
	}

	void Carnation::firing()
	{
		mState = eCarnationState::Firing;
		mAnimator->Play(L"CarnationFiringStart", true);
	}

	void Carnation::creating()
	{
		mState = eCarnationState::Creating;
		mAnimator->Play(L"CarnationCreatingStart", true);
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
	}
	void Carnation::firingLoopCallback()
	{
		mLoopCount++;

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

		if (mLoopCount >= 8)
		{
			mLoopCount = 0;
			mAnimator->Play(L"CarnationFiringEnd", true);
		}
		else
		{
			mAnimator->Play(L"CarnationFiringLoop", true);
		}
	}
}