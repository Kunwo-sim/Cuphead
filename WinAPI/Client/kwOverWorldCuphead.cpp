#include "kwOverWorldCuphead.h"
#include "kwResources.h"
#include "kwCamera.h"
#include "kwInput.h"
#include "kwTime.h"
#include "kwPixelMap.h"

namespace kw
{
	OverWorldCuphead::OverWorldCuphead()
		: mAnimator(nullptr)
		, mTransform(nullptr)
		, mCollider(nullptr)
		, mRigidbody(nullptr)
		, mSheetImage(nullptr)
		, mState(eOverWorldCupheadState::Idle)
		, mPixelMap(nullptr)
		, mSpeed(200.0f)
	{

	}

	OverWorldCuphead::~OverWorldCuphead()
	{

	}

	void OverWorldCuphead::Initialize()
	{
		SetPivot(ePivot::LowCenter);
		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		mSheetImage = Resources::Load<Image>(L"OverWorldCuphead", L"..\\Resources\\OverWorldCuphead.bmp");
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleUp", mSheetImage, Vector2(0.0f, 0.0f), 16, 8, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunUp", mSheetImage, Vector2(103.0f * 4.0f, 0.0f), 16, 8, 12, Vector2::Zero, 0.07f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleUpDiagnal", mSheetImage, Vector2(0.0f, 113.0f * 1.0f), 16, 8, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunUpDiagnal", mSheetImage, Vector2(103.0f * 4.0f, 113.0f * 1.0f), 16, 8, 10, Vector2::Zero, 0.07f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleSide", mSheetImage, Vector2(0.0f, 113.0f * 2.0f), 16, 8, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunSide", mSheetImage, Vector2(103.0f * 4.0f, 113.0f * 3.0f), 16, 8, 10, Vector2::Zero, 0.07f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleDownDiagnal", mSheetImage, Vector2(0.0f, 113.0f * 4.0f), 16, 8, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunDownDiagnal", mSheetImage, Vector2(103.0f * 4.0f, 113.0f * 4.0f), 16, 8, 12, Vector2::Zero, 0.07f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleDown", mSheetImage, Vector2(0.0f, 113.0f * 5.0f), 16, 8, 9, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunDown", mSheetImage, Vector2(0.0f, 113.0f * 6.0f), 16, 8, 13, Vector2::Zero, 0.07f);
		
		SetDirection(eDirection::Down);
		mAnimator->Play(L"OverWorldCupheadIdleDown", true);
		GameObject::Initialize();
	}

	void OverWorldCuphead::Update()
	{		
		switch (mState)
		{
		case kw::OverWorldCuphead::eOverWorldCupheadState::Idle:
			idle();
			break;
		case kw::OverWorldCuphead::eOverWorldCupheadState::Run:
			run();
			break;
		default:
			break;
		}
		
		Camera::SetLookPosition(mTransform->GetPos());
		GameObject::Update();
	}

	void OverWorldCuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void OverWorldCuphead::Release()
	{
		GameObject::Release();
	}

	void OverWorldCuphead::idle()
	{
		if (Input::GetKey(eKeyCode::W) || Input::GetKey(eKeyCode::A) || Input::GetKey(eKeyCode::S) || Input::GetKey(eKeyCode::D))
		{
			run();
			mState = eOverWorldCupheadState::Run;
			return;
		}
	}

	void OverWorldCuphead::run()
	{
		Vector2 addPos = Vector2::Zero;

		if (Input::GetKey(eKeyCode::W))
		{
			addPos.y -= mSpeed;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			addPos.x -= mSpeed;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			addPos.y += mSpeed;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			addPos.x += mSpeed;
		}

		if (addPos.x < 0.0f)
			SetFlipX(true);
		else if (addPos.x > 0.0f)
			SetFlipX(false);
		else if (addPos.y != 0.0f)
			SetFlipX(false);

		if (addPos.y > 0.0f)
		{
			// 하단
			if (addPos.x == 0.0f)
			{
				if (GetDirection() != eDirection::Down || mState != eOverWorldCupheadState::Run)
				{
					SetDirection(eDirection::Down);
					mAnimator->Play(L"OverWorldCupheadRunDown", true);
				}
			}
			else
			{
				if (GetDirection() != eDirection::DownDiagnal || mState != eOverWorldCupheadState::Run)
				{
					SetDirection(eDirection::DownDiagnal);
					mAnimator->Play(L"OverWorldCupheadRunDownDiagnal", true);
				}
			}
		}
		else if (addPos.y < 0.0f)
		{
			// 상단
			if (addPos.x == 0.0f)
			{
				if (GetDirection() != eDirection::Up || mState != eOverWorldCupheadState::Run)
				{
					SetDirection(eDirection::Up);
					mAnimator->Play(L"OverWorldCupheadRunUp", true);
				}
			}
			else
			{
				if (GetDirection() != eDirection::UpDiagnal || mState != eOverWorldCupheadState::Run)
				{
					SetDirection(eDirection::UpDiagnal);
					mAnimator->Play(L"OverWorldCupheadRunUpDiagnal", true);
				}
			}
		}
		else
		{
			// 이동없음
			if (addPos.x == 0.0f)
			{
				// 달리다가 멈추면 Idle 재생
				mState = eOverWorldCupheadState::Idle;

				if (GetDirection() == eDirection::Up)
				{
					mAnimator->Play(L"OverWorldCupheadIdleUp", true);
				}
				else if (GetDirection() == eDirection::UpDiagnal)
				{
					mAnimator->Play(L"OverWorldCupheadIdleUpDiagnal", true);
				}
				else if (GetDirection() == eDirection::Side)
				{
					mAnimator->Play(L"OverWorldCupheadIdleSide", true);
				}
				else if (GetDirection() == eDirection::Down)
				{
					mAnimator->Play(L"OverWorldCupheadIdleDown", true);
				}
				else if (GetDirection() == eDirection::DownDiagnal)
				{
					mAnimator->Play(L"OverWorldCupheadIdleDownDiagnal", true);
				}
			}
			// 양옆
			else
			{
				if (GetDirection() != eDirection::Side || mState != eOverWorldCupheadState::Run)
				{
					SetDirection(eDirection::Side);
					mAnimator->Play(L"OverWorldCupheadRunSide", true);
				}
			}
		}

		addPos = addPos.Normalize() * mSpeed * Time::DeltaTime();

		Vector2 pixelOffset = Vector2::Zero;

		if (addPos.y > 0.0f)
			pixelOffset.y += 0.0f;
		else if (addPos.y < 0.0f)
			pixelOffset.y -= 40.0f;

		if (addPos.x > 0.0f)
			pixelOffset.x += 10.0f;
		else if (addPos.x < 0.0f)
			pixelOffset.x -= 10.0f;

		Vector2 nextPos = mTransform->GetPos() + addPos + pixelOffset;

		if (mPixelMap->PixelMovableCheck(nextPos))
		{
			mTransform->AddPos(addPos);
		}
	}
}