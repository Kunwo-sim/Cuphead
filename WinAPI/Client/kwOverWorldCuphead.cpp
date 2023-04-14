#include "kwOverWorldCuphead.h"
#include "kwResources.h"
#include "kwCamera.h"
#include "kwInput.h"
#include "kwTime.h"
#include "kwPixelMap.h"
#include "kwCollider.h"
#include "kwOverWorldEntrance.h"

namespace kw
{
	OverWorldCuphead::OverWorldCuphead()
		: mSheetImage(nullptr)
		, mState(eOverWorldCupheadState::Idle)
		, mPixelMap(nullptr)
		, mSpeed(220.0f)
		, mIsOverlapEntrance(false)
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

		mSheetImage = Resources::Load<Image>(L"OverWorldCuphead", L"..\\Resources\\OverWorld\\OverWorldCuphead.bmp");
		mEnterBoxImage = Resources::Load<Image>(L"BossEnterBox", L"..\\Resources\\OverWorld\\EnterBox\\BossEnterBox.bmp");

		mAnimator = AddComponent<Animator>();
		Vector2 animOffeset = Vector2(0.0f, 12.0f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleUp", mSheetImage, Vector2(0.0f, 0.0f), 16, 8, 4, animOffeset, 0.075f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunUp", mSheetImage, Vector2(103.0f * 4.0f, 0.0f), 16, 8, 12, animOffeset, 0.05f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleUpDiagnal", mSheetImage, Vector2(0.0f, 113.0f * 1.0f), 16, 8, 3, animOffeset, 0.075f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunUpDiagnal", mSheetImage, Vector2(103.0f * 4.0f, 113.0f * 1.0f), 16, 8, 10, animOffeset, 0.05f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleSide", mSheetImage, Vector2(0.0f, 113.0f * 2.0f), 16, 8, 4, animOffeset, 0.075f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunSide", mSheetImage, Vector2(103.0f * 4.0f, 113.0f * 3.0f), 16, 8, 10, animOffeset, 0.05f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleDownDiagnal", mSheetImage, Vector2(0.0f, 113.0f * 4.0f), 16, 8, 4, animOffeset, 0.075f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunDownDiagnal", mSheetImage, Vector2(103.0f * 4.0f, 113.0f * 4.0f), 16, 8, 12, animOffeset, 0.05f);
		mAnimator->CreateAnimation(L"OverWorldCupheadIdleDown", mSheetImage, Vector2(0.0f, 113.0f * 5.0f), 16, 8, 9, animOffeset, 0.075f);
		mAnimator->CreateAnimation(L"OverWorldCupheadRunDown", mSheetImage, Vector2(0.0f, 113.0f * 6.0f), 16, 8, 13, animOffeset, 0.05f);
		
		SetDirection(eDirection::Down);
		mAnimator->Play(L"OverWorldCupheadIdleDown", true);
		GameObject::Initialize();
	}

	void OverWorldCuphead::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Z) && mEntrance != nullptr)
		{
			mEntrance->EnterBossMap();
		}

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
		// 카메라 경계값
		if (CameraPos.x < 640.0f)	CameraPos.x = 640.0f;
		if (CameraPos.x > 2940.0f)	CameraPos.x = 2940.0f;
		if (CameraPos.y < 360.0f)	CameraPos.y = 360.0f;
		if (CameraPos.y > 1640.0f)	CameraPos.y = 1640.0f;
		Camera::SetLookPosition(CameraPos);

		GameObject::Update();
	}

	void OverWorldCuphead::Render(HDC hdc)
	{
		if (mIsOverlapEntrance)
		{
			Vector2 boxOffset = Vector2(-23.0f, -150.0f);
			Vector2 pos = mTransform->GetPos() + boxOffset;
			pos = Camera::CalculatePos(pos);

			TransparentBlt(hdc
				, pos.x
				, pos.y
				, mEnterBoxImage->GetWidth()
				, mEnterBoxImage->GetHeight()
				, mEnterBoxImage->GetHdc()
				, 0
				, 0
				, mEnterBoxImage->GetWidth()
				, mEnterBoxImage->GetHeight()
				, RGB(255, 0, 255)
			);
		}

		GameObject::Render(hdc);
	}

	void OverWorldCuphead::Release()
	{
		GameObject::Release();
	}

	void OverWorldCuphead::OnCollisionEnter(Collider* other)
	{
		OverWorldEntrance* entrance = dynamic_cast<OverWorldEntrance*>(other->GetOwner());
		if (entrance != nullptr)
		{
			mIsOverlapEntrance = true;
			mEntrance = entrance;
		}
	}

	void OverWorldCuphead::OnCollisionExit(Collider* other)
	{
		OverWorldEntrance* entrance = dynamic_cast<OverWorldEntrance*>(other->GetOwner());
		if (entrance != nullptr)
		{
			mIsOverlapEntrance = false;
			mEntrance = nullptr;
		}
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