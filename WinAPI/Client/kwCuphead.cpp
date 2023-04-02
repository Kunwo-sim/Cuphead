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
		, mTransform(nullptr)
		, mCollider(nullptr)
		, mRigidbody(nullptr)
		, mAnimator(nullptr)
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

		/*Image* mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\Cuphead_Stage.bmp");
		mAnimator->CreateAnimation(L"FowardRun", mImage, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"FowardRight", mImage, Vector2(0.0f, 113.0f), 16, 8, 15, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Idle", mImage, Vector2(0.0f, 113.0f * 5), 16, 8, 9, Vector2(0.0f, 0.0f), 0.1);*/
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\IdleLeft", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\IdleRight", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\ShootLeft", Vector2(-14.0f, 0.0f), 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\ShootRight", Vector2(14.0f, 0.0f), 0.07f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\RunLeft", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\RunRight", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\RunShootLeft", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\RunShootRight", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\DuckLeft", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\DuckRight", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\DuckShootLeft", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\DuckShootRight", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\JumpLeft", Vector2::Zero, 0.05f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\JumpRight", Vector2::Zero, 0.05f);
		
		SetDirection(eDirection::Right);
		mState = eCupheadState::Idle;
		mCollider->SetSize(Vector2(100, 130));
		mRigidbody->SetGround(false);
		mAnimator->Play(L"StageCupheadIdleRight", true);

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		mAttackCoolChecker -= Time::DeltaTime();

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
		if (Input::GetKey(eKeyCode::W))
		{
			SetStateJump();
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			SetDirection(eDirection::Left);
			mState = eCupheadState::Run;
			playCupheadAnim(L"Run");
		}
		else if(Input::GetKey(eKeyCode::D))
		{
			SetDirection(eDirection::Right);
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
		if (Input::GetKey(eKeyCode::W))
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

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= mSpeed * Time::DeltaTime();
			if (GetDirection() == eDirection::Right)
			{
				SetDirection(eDirection::Left);
				playCupheadAnim(L"Run");
			}
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += mSpeed * Time::DeltaTime();
			if (GetDirection() == eDirection::Left)
			{
				SetDirection(eDirection::Right);
				playCupheadAnim(L"Run");
			}
		}
		else
		{
			mState = eCupheadState::Idle;
			playCupheadAnim(L"Idle");
		}

		tr->SetPos(pos);
	}
	void Cuphead::shoot()
	{
		if (Input::GetKey(eKeyCode::W))
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
			SetDirection(eDirection::Left);
			mState = eCupheadState::RunShoot;
			playCupheadAnim(L"RunShoot");
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			SetDirection(eDirection::Right);
			mState = eCupheadState::RunShoot;
			playCupheadAnim(L"RunShoot");
		}
	}

	void Cuphead::runShoot()
	{
		if (Input::GetKey(eKeyCode::W))
		{
			SetStateJump();
			return;
		}
		else if (Input::GetKeyUp(eKeyCode::K))
		{
			if (!Input::GetKey(eKeyCode::A) && !Input::GetKey(eKeyCode::D))
			{
				mState = eCupheadState::Idle;
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

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= mSpeed * Time::DeltaTime();
			if (GetDirection() == eDirection::Right)
			{
				SetDirection(eDirection::Left);
				playCupheadAnim(L"RunShoot");
			}
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += mSpeed * Time::DeltaTime();
			if (GetDirection() == eDirection::Left)
			{
				SetDirection(eDirection::Right);
				playCupheadAnim(L"RunShoot");
			}
		}
		else
		{
			mState = eCupheadState::Shoot;
			playCupheadAnim(L"Shoot");
		}

		tr->SetPos(pos);
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
		Vector2 pos = mTransform->GetPos();

		if (mRigidbody->GetGround() == true)
		{
			mState = eCupheadState::Idle;
			playCupheadAnim(L"Idle");
			idle();
			return;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= mSpeed * Time::DeltaTime();
			if (GetDirection() == eDirection::Right)
			{
				SetDirection(eDirection::Left);
				playCupheadAnim(L"Jump");
			}
			
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += mSpeed * Time::DeltaTime();
			if (GetDirection() == eDirection::Left)
			{
				SetDirection(eDirection::Right);
				playCupheadAnim(L"Jump");
			}
		}

		mTransform->SetPos(pos);

		if (Input::GetKey(eKeyCode::K))
		{
			CreateBullet();
		}
	}

	void Cuphead::death()
	{

	}

	void Cuphead::playCupheadAnim(std::wstring State, bool loop)
	{
		std::wstring playAnimName = L"StageCuphead" + State;

		if (GetDirection() == eDirection::Left)
		{
			playAnimName += L"Left";
		}
		else if (GetDirection() == eDirection::Right)
		{
			playAnimName += L"Right";
		}

		mAnimator->Play(playAnimName, loop);
	}

	void Cuphead::CupheadMove()
	{

	}

	void Cuphead::CreateBullet()
	{
		if (Input::GetKey(eKeyCode::K) && mAttackCoolChecker <= 0.0f)
		{
			mAttackCoolChecker = mAttackCoolTime;
			Vector2 bulletPos = mTransform->GetPos();
			eDirection bulletDir = GetDirection();

			if (GetDirection() == eDirection::Left)
			{
				bulletPos.x -= mBulletOffset.x;
				bulletPos.y += mBulletOffset.y;
			}
			else if (GetDirection() == eDirection::Right)
			{
				bulletPos.x += mBulletOffset.x;
				bulletPos.y += mBulletOffset.y;
			}

			BaseBullet* Bullet = object::Instantiate<BaseBullet>(eLayerType::Bullet, bulletPos, bulletDir);
			BulletFireEffect* FireEffect = object::Instantiate<BulletFireEffect>(eLayerType::Effect, bulletPos);
		}
	}

	void Cuphead::SetStateJump()
	{
		mState = eCupheadState::Jump;
		playCupheadAnim(L"Jump");

		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.y -= 800.0f;

		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);
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
