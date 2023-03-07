#include "kwCuphead.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwInput.h"
#include "kwResources.h"
#include "kwTransform.h"
#include "kwCollider.h"
#include "kwBaseBullet.h"

namespace kw
{
	Cuphead::Cuphead()
	{
	}
	Cuphead::~Cuphead()
	{
	}
	void Cuphead::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(400.0f, 400.0f));

		Image* mImage = Resources::Load<Image>(L"Cuphead", L"..\\Resources\\Cuphead_Stage.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"FowardRun", mImage, Vector2::Zero, 16, 8, 16, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"FowardRight", mImage, Vector2(0.0f, 113.0f), 16, 8, 15, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Idle", mImage, Vector2(0.0f, 113.0f * 5), 16, 8, 9, Vector2(-50.0f, -50.0f), 0.1);
		mAnimator->CreateAnimations(L"..\\Resources\\Chalise\\Idle", Vector2::Zero, 0.1f);

		mAnimator->Play(L"ChaliseIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-60.0f, -80.0f));

		mState = eCupheadState::Idle;

		GameObject::Initialize();
	}
	void Cuphead::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case kw::Cuphead::eCupheadState::Move:
			move();
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
	}
	void Cuphead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Cuphead::Release()
	{
		GameObject::Release();
	}
	void Cuphead::move()
	{
		if (Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::D)
			|| Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::W))
		{
			mState = eCupheadState::Idle;
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
			pos.x -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::D))
			pos.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::W))
			pos.y -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::S))
			pos.y += 100.0f * Time::DeltaTime();

		tr->SetPos(pos);
	}
	void Cuphead::shoot()
	{
		Transform* tr = GetComponent<Transform>();
		if (Input::GetKey(eKeyCode::K))
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BaseBullet* bullet = new BaseBullet();
			bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
			curScene->AddGameObeject(bullet, eLayerType::Bullet);
		}
	}
	void Cuphead::death()
	{
	}
	void Cuphead::idle()
	{
		if (Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::W))
		{
			mState = eCupheadState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			mState = eCupheadState::Shoot;
			//mAnimator->Play(L"AimStraight", true);
		}
	}
}
