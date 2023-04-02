#include "kwCarnation.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwInput.h"
#include "kwResources.h"
#include "kwTransform.h"
#include "kwCollider.h"
#include "kwBaseBullet.h"
#include "kwObject.h"

namespace kw
{
	Carnation::Carnation()
		: mState(eCarnationState::Idle)
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
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\FaceAttack\\High", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Firing", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Creating", Vector2::Zero, 0.08f);
		mAnimator->Play(L"CarnationIdle", true);
		mAnimator->Play(L"FaceAttackHigh", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(200, 600));

		GameObject::Initialize();
	}
	void Carnation::Update()
	{
		switch (mState)
		{
		case kw::Carnation::eCarnationState::Idle:
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

}