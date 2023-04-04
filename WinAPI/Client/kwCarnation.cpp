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

#include "kwBaseBullet.h"
#include "kwObject.h"

namespace kw
{
	Carnation::Carnation()
		: mState(eCarnationState::Idle)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mTime(0.0f)
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

		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Idle", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\FaceAttack\\High", Vector2(-400.0f, 0.0f), 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\FaceAttack\\Low", Vector2(-400.0f, 0.0f), 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Firing", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Creating", Vector2::Zero, 0.08f);
		mAnimator->GetCompleteEvent(L"FaceAttackHigh") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"FaceAttackLow") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationFiring") = std::bind(&Carnation::idleCallback, this);
		mAnimator->GetCompleteEvent(L"CarnationCreating") = std::bind(&Carnation::idleCallback, this);

		mAnimator->Play(L"CarnationIdle", true);

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

			int type = math::GetRandomNumber(0, 2);
			switch (type)
			{
				case 0:
					faceAttack();
					break;
				case 1:
					firing();
					break;
				case 2:
					creating();
					break;
			default:
				break;
			}
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
			mAnimator->Play(L"FaceAttackHigh", true);
		else
			mAnimator->Play(L"FaceAttackLow", true);
		
		 mSFX = Resources::Load<Sound>(L"FaceAttack", L"..\\Resources\\Sound\\SFX\\FaceAttack.wav");
		 mSFX->Play(false);
	}

	void Carnation::firing()
	{
		mState = eCarnationState::Firing;
		mAnimator->Play(L"CarnationFiring", true);
	}

	void Carnation::creating()
	{
		mState = eCarnationState::Creating;
		mAnimator->Play(L"CarnationCreating", true);
	}

	void Carnation::idleCallback()
	{
		mState = eCarnationState::Idle();
		mAnimator->Play(L"CarnationIdle", true);
	}
}