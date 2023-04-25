#include "kwKnockOut.h"

#include "kwResources.h"
#include "kwInput.h"
#include "kwObject.h"
#include "kwTime.h"
#include "kwSound.h"

namespace kw
{
	KnockOut::KnockOut()
		: mExplosionSFX(nullptr)
	{
		mTransform->SetScale(Vector2(2.5f, 2.5f));
		mTimeIndependent = true;
	}

	KnockOut::~KnockOut()
	{
	}

	void KnockOut::Initialize()
	{
		SetPivot(ePivot::MiddleCenter);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\KnockOut", Vector2::Center, 0.06f);
		mAnimator->Play(L"UIKnockOut", true);
		mAnimator->FindEvents(L"UIKnockOut")->mCompleteEvent = std::bind(&KnockOut::KnockOutCallback, this);

		mExplosionSFX = Resources::Load<Sound>(L"ExplosionSFX", L"..\\Resources\\Sound\\SFX\\Stage_End.wav");
		GameObject::Initialize();
	}

	void KnockOut::Update()
	{
		GameObject::Update();
	}

	void KnockOut::KnockOutCallback()
	{
		Time::SetTimeScale(1.0);
		object::Destory(this);
		Input::SetInputEnable(true);
		mExplosionSFX->Play(false);
	}
}
