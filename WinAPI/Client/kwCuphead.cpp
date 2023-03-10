#include "kwCuphead.h"
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
	Cuphead::Cuphead()
		: mState(eCupheadState::Idle)
		, mSpeed(500.0f)
		, mBulletOffset(Vector2(50.0f, -80.0f))
		, mAttackCoolTime(0.1f)
		, mAttackCoolChecker(0.0f)
	{

	}

	Cuphead::~Cuphead()
	{

	}

	void Cuphead::Initialize()
	{
		SetPivot(ePivot::LowCenter);
		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();

		Image* mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\Cuphead_Stage.bmp");
		mAnimator->CreateAnimation(L"FowardRun", mImage, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"FowardRight", mImage, Vector2(0.0f, 113.0f), 16, 8, 15, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Idle", mImage, Vector2(0.0f, 113.0f * 5), 16, 8, 9, Vector2(0.0f, 0.0f), 0.1);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\IdleLeft", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\IdleRight", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\RunLeft", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\RunRight", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\ShootLeft", Vector2(-14.0f, 0.0f), 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\ShootRight", Vector2(14.0f, 0.0f), 0.07f);

		mState = eCupheadState::Idle;
		mAnimator->Play(L"StageCupheadIdleRight", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(100, 130));

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		switch (mState)
		{
		case kw::Cuphead::eCupheadState::Run:
			run();
			break;
		case kw::Cuphead::eCupheadState::Shoot:
			shoot();
			break;
		case kw::Cuphead::eCupheadState::Death:
			death();
			break;
		case kw::Cuphead::eCupheadState::Idle:
			idle();
			break;
		default:
			break;
		}

		GameObject::Update();
	}

	void Cuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Cuphead::Release()
	{
		GameObject::Release();
	}

	void Cuphead::run()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= mSpeed * Time::DeltaTime();
			mAnimator->Play(L"StageCupheadRunLeft", true);
			SetDirection(eDirection::Left);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += mSpeed * Time::DeltaTime();
			SetDirection(eDirection::Right);
			mAnimator->Play(L"StageCupheadRunRight", true);
		}
		else
		{
			mState = eCupheadState::Idle;
		}

		tr->SetPos(pos);
	}
	void Cuphead::shoot()
	{
		if (Input::GetKeyUp(eKeyCode::K))
		{
			mState = eCupheadState::Idle;
			return;
		}

		mAttackCoolChecker -= Time::DeltaTime();

		if (Input::GetKey(eKeyCode::K) && mAttackCoolChecker <= 0.0f)
		{
			mAttackCoolChecker = mAttackCoolTime;
			BaseBullet* bullet = object::Instantiate<BaseBullet>(eLayerType::Bullet, mTransform->GetPos());
			Vector2 bulletPos = mTransform->GetPos();

			if (GetDirection() == eDirection::Left)
			{
				mAnimator->Play(L"StageCupheadShootLeft", true);
				bullet->SetDirection(eDirection::Left);
				bulletPos.x -= mBulletOffset.x;
				bulletPos.y += mBulletOffset.y;
			}
			else if (GetDirection() == eDirection::Right)
			{
				mAnimator->Play(L"StageCupheadShootRight", true);
				bullet->SetDirection(eDirection::Right);
				bulletPos.x += mBulletOffset.x;
				bulletPos.y += mBulletOffset.y;
			}

			bullet->GetComponent<Transform>()->SetPos(bulletPos);
		}

		

		

		Transform* tr = GetComponent<Transform>();


	}

	void Cuphead::death()
	{

	}

	void Cuphead::idle()
	{
		if (GetDirection() == eDirection::Left)
		{
			mAnimator->Play(L"StageCupheadIdleLeft", true);
		}
		else if (GetDirection() == eDirection::Right)
		{
			mAnimator->Play(L"StageCupheadIdleRight", true);
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			mState = eCupheadState::Run;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = eCupheadState::Shoot;
		}
	}

	Vector2 Cuphead::DirectionToVector2(eDirection direction)
	{
		Vector2 vec = Vector2::Zero;
		if (direction == eDirection::Right)
			vec = Vector2(1.0f, 0.0f);
		else
			vec = Vector2(-1.0f, 0.0f);

		return vec;
	}
}
