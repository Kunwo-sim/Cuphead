#include "kwCuphead.h"

#include "kwInput.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwResources.h"
#include "kwSound.h"

#include "kwObject.h"

#include "kwBaseBullet.h"
#include "kwSpreadShot.h"
#include "kwBulletFireEffect.h"

#include "kwParryObject.h"
#include "kwTimeStopObject.h"

namespace kw
{
	Cuphead::Cuphead()
		: mState(eCupheadState::Idle)
		, mBulletType(eBulletType::PeaShot)
		, mSpeed(500.0f)
		, mBulletOffset(Vector2(50.0f, -80.0f))
		, mAttackCoolTime(0.2f)
		, mAttackCoolChecker(0.0f)
		, mBulletSound(nullptr)
		, mSpreadSound(nullptr)
		, mHitBlinkCoolTime(0.1f)
		, mHitBlinkCoolChecker(mHitBlinkCoolTime)
		, mIsBlink(false)
	{
		mHp = (int)3;
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

		mBulletSound = Resources::Load<Sound>(L"BulletFire", L"..\\Resources\\Sound\\SFX\\Cuphead\\Cuphead_BulletFire.wav");
		mSpreadSound = Resources::Load<Sound>(L"SpreadFire", L"..\\Resources\\Sound\\SFX\\Cuphead\\Cuphead_SpreadShot.wav");

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		mAttackCoolChecker -= Time::DeltaTime();

		if (Input::GetKeyDown(eKeyCode::X) && mState != eCupheadState::Hit)
		{
			dash();
		}

		if (Input::GetKeyDown(eKeyCode::TAB))
		{
			if (mBulletType == eBulletType::PeaShot)
			{
				mBulletType = eBulletType::SpreadShot;
			}
			else
			{
				mBulletType = eBulletType::PeaShot;
			}

			if (Input::GetKey(eKeyCode::K))
			{
				stopBulletSound();
				playBulletSound();
			}
		}

		if (mState != eCupheadState::Hit)
		{
			mIsBlink = false;
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

		Vector2 pos = mTransform->GetPos();
		if (pos.x < 30)
		{
			mTransform->SetPos(Vector2(30.0f, pos.y));
		}
		else if (pos.x > 1250)
		{
			mTransform->SetPos(Vector2(1250.0f, pos.y));
		}

		GameObject::Update();
	}

	void Cuphead::Render(HDC hdc)
	{
		if (mIsBlink == false)
		{
			GameObject::Render(hdc);
		}
	}

	void Cuphead::Release()
	{
		GameObject::Release();
	}

	void Cuphead::OnCollisionStay(Collider* other)
	{
		// ÆÐ¸®
		ParryObject* parryObject = dynamic_cast<ParryObject*>(other->GetOwner());
		if (parryObject != nullptr)
		{
			if (Input::GetKeyDown(eKeyCode::SPACE) && mState != eCupheadState::Hit)
			{
 				Vector2 parryPos = mTransform->GetPos();
				parryPos.y -= 50.0f;

				GameObject* Effect = object::Instantiate<GameObject>(eLayerType::Effect, Vector2(parryPos));
				Effect->AddComponent<Animator>()->CreateAnimations(L"..\\Resources\\Stage\\StageCuphead\\Effect\\Spark", Vector2::Zero, 0.05f);
				Effect->GetComponent<Animator>()->Play(L"EffectSpark", false);

				mSFX = Resources::Load<Sound>(L"Cuphead_Parry", L"..\\Resources\\Sound\\SFX\\Cuphead\\Cuphead_Parry.wav");
				mSFX->Play(false);

				object::Destory(parryObject->GetOwner());
				object::Destory(other->GetOwner());
				object::Instantiate<TimeStopObject>(eLayerType::SceneEffect)->SetStopTime(0.4f);
			}
		}		
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
			playBulletSound();
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
			playBulletSound();
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
			stopBulletSound();
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

			stopBulletSound();
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
		mCollider->SetSize(Vector2(100, 65));

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mCollider->SetSize(Vector2(100, 130));
			mState = eCupheadState::Idle;
			playCupheadAnim(L"Idle");
		}
		else if (Input::GetKey(eKeyCode::K))
		{
			mState = eCupheadState::DuckShoot;
			playCupheadAnim(L"DuckShoot");
			playBulletSound();
			duckShoot();
			return;
		}
	}

	void Cuphead::duckShoot()
	{
		mCollider->SetSize(Vector2(100, 65));

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mCollider->SetSize(Vector2(100, 130));
			mState = eCupheadState::Shoot;
			playCupheadAnim(L"Shoot");
		}
		else if (Input::GetKeyUp(eKeyCode::K))
		{
			mState = eCupheadState::Duck;
			playCupheadAnim(L"Duck");
			stopBulletSound();
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
			mSFX = Resources::Load<Sound>(L"Cuphead_Land", L"..\\Resources\\Sound\\SFX\\Cuphead\\Cuphead_Land.wav");
			mSFX->Play(false);
			return;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			playBulletSound();
		}
		else if (Input::GetKey(eKeyCode::K))
		{
			CreateBullet();
		}
		else
		{
			stopBulletSound();
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

		mSFX = Resources::Load<Sound>(L"Cuphead_Dash", L"..\\Resources\\Sound\\SFX\\Cuphead\\Cuphead_Dash.wav");
		mSFX->Play(false);
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

		mHitBlinkCoolChecker -= Time::DeltaTime();
		if (mHitBlinkCoolChecker < 0.0f)
		{
			mIsBlink = !mIsBlink;
			mHitBlinkCoolChecker = mHitBlinkCoolTime;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			SetStateJump();
		}

		if (mState == eCupheadState::Hit)
			return;

		SetHp((int)GetHp() - 1);
		mState = eCupheadState::Hit;
		playCupheadAnim(L"Hit");

		mSFX = Resources::Load<Sound>(L"Cuphead_Crack", L"..\\Resources\\Sound\\SFX\\Cuphead\\Cuphead_Crack.wav");
		mSFX->Play(false);
		mSFX = Resources::Load<Sound>(L"Cuphead_Hit", L"..\\Resources\\Sound\\SFX\\Cuphead\\Cuphead_Hit.wav");
		mSFX->Play(false);
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
		if (!Input::GetKey(eKeyCode::K) || mAttackCoolChecker > 0.0f)
			return;

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

		if (mState == eCupheadState::DuckShoot)
		{
			bulletPos.y += 30.0f;
		}

		switch (mBulletType)
		{
			case eBulletType::PeaShot:
			{
				BaseBullet* Bullet = object::Instantiate<BaseBullet>(eLayerType::Bullet, bulletPos);
				Bullet->SetFlipX(GetFlipX());
				break;
			}
			case eBulletType::SpreadShot:
			{
				for (int i = 0; i < 5; i++)
				{
					SpreadShot* ss = object::Instantiate<SpreadShot>(eLayerType::Bullet, bulletPos);
					ss->SetSpreadDirection(i);
					if (GetFlipX())
					{
						ss->SetFlipX(true);
						ss->SetDirectionFlip();
					}
				}
				break;
			}
		default:
			break;
		}

		BulletFireEffect* FireEffect = object::Instantiate<BulletFireEffect>(eLayerType::Effect, bulletPos);
	}

	void Cuphead::SetStateJump()
	{
		mState = eCupheadState::Jump;
		playCupheadAnim(L"Jump");

		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.y -= 1800.0f;

		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);

		mSFX = Resources::Load<Sound>(L"Cuphead_Jump", L"..\\Resources\\Sound\\SFX\\Cuphead\\Cuphead_Jump.wav");
		mSFX->Play(false);
	}

	void Cuphead::IdleCallback()
	{
		mSpeed = 500.0f;
		mState = eCupheadState::Idle;
		playCupheadAnim(L"Idle");
		mRigidbody->SetGround(false);
		mIsBlink = false;
	}

	void Cuphead::StageClear()
	{
		mState = eCupheadState::Idle;
		playCupheadAnim(L"Idle");
		mSpeed = 500.0f;
		mIsBlink = false;

		stopBulletSound();
	}

	void Cuphead::playBulletSound()
	{
		switch (mBulletType)
		{
		case eBulletType::PeaShot:
			mBulletSound->Play(true);
			break;
		case eBulletType::SpreadShot:
			mSpreadSound->Play(true);
			break;
		default:
			break;
		}
	}

	void Cuphead::stopBulletSound()
	{
		mBulletSound->Stop(false);
		mSpreadSound->Stop(false);
	}
}
