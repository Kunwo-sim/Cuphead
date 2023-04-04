#include "kwOverWorldCuphead.h"
#include "kwResources.h"
#include "kwCamera.h"
#include "kwInput.h"
#include "kwTime.h"
#include "kwPixelMap.h"
#include "kwCollider.h"

namespace kw
{
	OverWorldCuphead::OverWorldCuphead()
		: mAnimator(nullptr)
		, mTransform(nullptr)
		, mCollider(nullptr)
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
		
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(70.0f, 90.0f));

		mAnimator = AddComponent<Animator>();
		mSheetImage = Resources::Load<Image>(L"OverWorldCuphead", L"..\\Resources\\OverWorld\\OverWorldCuphead.bmp");
		Vector2 animOffeset = Vector2(0.0f, 12.0f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleUp", mSheetImage, Vector2(0.0f, 0.0f), 16, 8, 4, animOffeset, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunUp", mSheetImage, Vector2(103.0f * 4.0f, 0.0f), 16, 8, 12, animOffeset, 0.07f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleUpDiagnal", mSheetImage, Vector2(0.0f, 113.0f * 1.0f), 16, 8, 3, animOffeset, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunUpDiagnal", mSheetImage, Vector2(103.0f * 4.0f, 113.0f * 1.0f), 16, 8, 10, animOffeset, 0.07f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleSide", mSheetImage, Vector2(0.0f, 113.0f * 2.0f), 16, 8, 4, animOffeset, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunSide", mSheetImage, Vector2(103.0f * 4.0f, 113.0f * 3.0f), 16, 8, 10, animOffeset, 0.07f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleDownDiagnal", mSheetImage, Vector2(0.0f, 113.0f * 4.0f), 16, 8, 4, animOffeset, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunDownDiagnal", mSheetImage, Vector2(103.0f * 4.0f, 113.0f * 4.0f), 16, 8, 12, animOffeset, 0.07f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleDown", mSheetImage, Vector2(0.0f, 113.0f * 5.0f), 16, 8, 9, animOffeset, 0.1f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunDown", mSheetImage, Vector2(0.0f, 113.0f * 6.0f), 16, 8, 13, animOffeset, 0.07f);
		
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
		
		Vector2 CameraPos = mTransform->GetPos();
		// ī�޶� ��谪
		if (CameraPos.x < 640.0f)	CameraPos.x = 640.0f;
		if (CameraPos.x > 2940.0f)	CameraPos.x = 2940.0f;
		if (CameraPos.y < 360.0f)	CameraPos.y = 360.0f;
		if (CameraPos.y > 1640.0f)	CameraPos.y = 1640.0f;
		Camera::SetLookPosition(CameraPos);

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
			// �ϴ�
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
			// ���
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
			// �̵�����
			if (addPos.x == 0.0f)
			{
				// �޸��ٰ� ���߸� Idle ���
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
			// �翷
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

		Vector2 pixelOffset = Vector2(0.0f, -15.0f);

		if (addPos.y > 0.0f)
			pixelOffset.y += 20.0f;
		else if (addPos.y < 0.0f)
			pixelOffset.y -= 10.0f;

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