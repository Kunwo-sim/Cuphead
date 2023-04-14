#include "kwCuphead.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwInput.h"
#include "kwResources.h"
#include "kwTransform.h"
#include "kwCollider.h"
#include "kwBaseBullet.h"
#include "kwObject.h"
#include "kwBulletFireEffect.h"

namespace kw
{
	Cuphead::Cuphead()
		: mState(eCupheadState::Idle)
		, mSpeed(500.0f)
		, mBulletOffset(Vector2(50.0f, -80.0f))
		, mAttackCoolTime(0.2f)
		, mAttackCoolChecker(0.0f)
		, mRigidbody(nullptr)
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
		mRigidbody = AddComponent<Rigidbody>();
		mCollider = AddComponent<Collider>();

		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Intro", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Idle", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Idle", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Shoot", Vector2(10.0f, 0.0f), 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Run", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\RunShoot", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Duck", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\DuckShoot", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Jump", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Parry", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Dash", Vector2::Zero, 0.045f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Hit", Vector2::Zero, 0.05f);

		mAnimator->GetCompleteEvent(L"StageCupheadIntro") = std::bind(&Cuphead::IdleCallback, this);
		mAnimator->GetCompleteEvent(L"StageCupheadDash") = std::bind(&Cuphead::IdleCallback, this);
		mAnimator->GetCompleteEvent(L"StageCupheadHit") = std::bind(&Cuphead::IdleCallback, this);
		
		SetDirection(eDirection::Right);
		mState = eCupheadState::Intro;
		mCollider->SetSize(Vector2(100, 130));
		mRigidbody->SetGround(false);
		playCupheadAnim(L"Intro");

		GameObject* Effect = object::Instantiate<GameObject>(eLayerType::Effect, Vector2(400, 400));
		Effect->AddComponent<Animator>()->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Effect\\Spark", Vector2::Zero, 0.05f);
		Effect->GetComponent<Animator>()->Play(L"EffectSpark", false);

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		mAttackCoolChecker -= Time::DeltaTime();

		if (Input::GetKeyDown(eKeyCode::X) && mState != eCupheadState::Hit)
		{
			dash();
		}

		switch (mState)
		{
		case kw::Cuphead::eCupheadState::Idle:
			idle();
			break;
		case kw::Cuphead::eCupheadState::Shoot:
			shoot();
			break;
		case kw::Cuphead::eCupheadState::Run:
			run();
			break;
		case kw::Cuphead::eCupheadState::RunShoot:
			runShoot();
			break;
		case kw::Cuphead::eCupheadState::Duck:
			duck();
			break;
		case kw::Cuphead::eCupheadState::DuckShoot:
			duckShoot();
			break;
		case kw::Cuphead::eCupheadState::Jump:
			jump();
			break;
		case kw::Cuphead::eCupheadState::Dash:
			dash();
			break;
		case kw::Cuphead::eCupheadState::Hit:
			Hit();
			break;
		case kw::Cuphead::eCupheadState::Death:
			death();
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

	void Cuphead::idle()
	{
		if (mRigidbody->GetGround() == false)
		{
			mState = eCupheadState::Jump;
			playCupheadAnim(L"Jump");
			jump();
			return;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			SetStateJump();
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			SetFlipX(true);
			mState = eCupheadState::Run;
			playCupheadAnim(L"Run");
		}
		else if(Input::GetKey(eKeyCode::D))
		{
			SetFlipX(false);
			mState = eCupheadState::Run;
			playCupheadAnim(L"Run");
		}
		else if (Input::GetKey(eKeyCode::K))
		{
			mState = eCupheadState::Shoot;
			playCupheadAnim(L"Shoot");
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			mState = eCupheadState::Duck;
			playCupheadAnim(L"Duck");
		}
	}

	void Cuphead::run()
	{
		if (Input::GetKeyDown(eKeyCode::W))
		{
			SetStateJump();
			return;
		}
		else if (Input::GetKey(eKeyCode::K))
		{
			mState = eCupheadState::RunShoot;
			playCupheadAnim(L"RunShoot");
			runShoot();
			return;
		}

		move();
	}
	void Cuphead::shoot()
	{
		if (Input::GetKeyDown(eKeyCode::W))
		{
			SetStateJump();
			return;
		}
		else if (Input::GetKeyUp(eKeyCode::K))
		{
			mState = eCupheadState::Idle;
			playCupheadAnim(L"Idle");
			idle();
			return;
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			mState = eCupheadState::DuckShoot;
			playCupheadAnim(L"DuckShoot");
			duckShoot();
			return;
		}

		CreateBullet();

		if (Input::GetKey(eKeyCode::A))
		{
			SetFlipX(true);
			mState = eCupheadState::RunShoot;
			playCupheadAnim(L"RunShoot");
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			SetFlipX(false);
			mState = eCupheadState::RunShoot;
			playCupheadAnim(L"RunShoot");
		}
	}

	void Cuphead::runShoot()
	{
		if (Input::GetKeyDown(eKeyCode::W))
		{
			SetStateJump();
			return;
		}
		else if (Input::GetKeyUp(eKeyCode::K))
		{
			if (!Input::GetKey(eKeyCode::A) && !Input::GetKey(eKeyCode::D))
			{
				playCupheadAnim(L"Idle");
			}
			else
			{
				mState = eCupheadState::Run;
				playCupheadAnim(L"Run");
			}
			return;
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			mState = eCupheadState::DuckShoot;
			playCupheadAnim(L"DuckShoot");
			duckShoot();
			return;
		}

		CreateBullet();

		move();

		if (Input::GetKey(eKeyCode::A))
		{
			if (GetFlipX() == false)
			{
				playCupheadAnim(L"RunShoot");
			}
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			if (GetFlipX() == true)
			{
				playCupheadAnim(L"RunShoot");
			}
		}
		else
		{
			mState = eCupheadState::Shoot;
			playCupheadAnim(L"Shoot");
		}
	}

	void Cuphead::duck()
	{
		if (Input::GetKeyUp(eKeyCode::S))
		{
			mState = eCupheadState::Idle;
			playCupheadAnim(L"Idle");
		}
		else if (Input::GetKey(eKeyCode::K))
		{
			mState = eCupheadState::DuckShoot;
			playCupheadAnim(L"DuckShoot");
			duckShoot();
			return;
		}
	}

	void Cuphead::duckShoot()
	{
		if (Input::GetKeyUp(eKeyCode::S))
		{
			mState = eCupheadState::Shoot;
			playCupheadAnim(L"Shoot");
		}
		else if (Input::GetKeyUp(eKeyCode::K))
		{
			mState = eCupheadState::Duck;
			playCupheadAnim(L"Duck");
			duck();
			return;
		}

		CreateBullet();
	}

	void Cuphead::jump()
	{
		if (mRigidbody->GetGround() == true)
		{
			mState = eCupheadState::Idle;
			playCupheadAnim(L"Idle");
			idle();
			return;
		}

		if (Input::GetKey(eKeyCode::K))
		{
			CreateBullet();
		}

		move();
	}

	void Cuphead::dash()
	{
		Vector2 pos = Vector2::Zero;

		if (GetFlipX())
		{
			pos.x -= (mSpeed * Time::DeltaTime());
		}
		else
		{
			pos.x += (mSpeed * Time::DeltaTime());
		}

		mTransform->AddPos(pos);

		if (mState == eCupheadState::Dash)
			return;

		playCupheadAnim(L"Dash", true);
		mState = eCupheadState::Dash;
		mSpeed = 1000.0f;
		mRigidbody->SetGround(true);
	}

	void Cuphead::death()
	{

	}

	void Cuphead::playCupheadAnim(std::wstring State, bool loop)
	{
		std::wstring playAnimName = L"StageCuphead" + State;
		mAnimator->Play(playAnimName, loop);
	}

	void Cuphead::move()
	{
		Vector2 pos = mTransform->GetPos();

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= mSpeed * Time::DeltaTime();
			if (GetFlipX() == false);
			{
				SetFlipX(true);
			}
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += mSpeed * Time::DeltaTime();
			if (GetFlipX() == true)
			{
				SetFlipX(false);
			}
		}
		else
		{
			if (mState != eCupheadState::Jump && mState != eCupheadState::Hit)
			{
				mState = eCupheadState::Idle;
				playCupheadAnim(L"Idle", true);
			}
		}

		mTransform->SetPos(pos);
	}

	void Cuphead::Hit()
	{
		move();

		if (Input::GetKeyDown(eKeyCode::W))
		{
			SetStateJump();
		}

		if (mState == eCupheadState::Hit)
			return;

		mState = eCupheadState::Hit;
		playCupheadAnim(L"Hit");
	}

	void Cuphead::GroundExit()
	{
		if (mState == eCupheadState::Dash)
			return;

		mState = eCupheadState::Jump;
		playCupheadAnim(L"Jump");

		mRigidbody->SetGround(false);
	}

	void Cuphead::CreateBullet()
	{
		if (Input::GetKey(eKeyCode::K) && mAttackCoolChecker <= 0.0f)
		{
			mAttackCoolChecker = mAttackCoolTime;
			Vector2 bulletPos = mTransform->GetPos();

			if (GetFlipX() == true)
			{
				bulletPos.x -= mBulletOffset.x;
				bulletPos.y += mBulletOffset.y;
			}
			else if (GetFlipX() == false)
			{
				bulletPos.x += mBulletOffset.x;
				bulletPos.y += mBulletOffset.y;
			}

			BaseBullet* Bullet = object::Instantiate<BaseBullet>(eLayerType::Bullet, bulletPos);
			Bullet->SetFlipX(GetFlipX());
			BulletFireEffect* FireEffect = object::Instantiate<BulletFireEffect>(eLayerType::Effect, bulletPos);
		}
	}

	void Cuphead::SetStateJump()
	{
		mState = eCupheadState::Jump;
		playCupheadAnim(L"Jump");

		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.y -= 1800.0f;

		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);
	}

	void Cuphead::IdleCallback()
	{
		mSpeed = 500.0f;

		mRigidbody->SetGround(false);
		mState = eCupheadState::Idle;
		playCupheadAnim(L"Idle");
	}
}
