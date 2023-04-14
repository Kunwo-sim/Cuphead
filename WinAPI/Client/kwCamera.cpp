#include "kwCamera.h"
#include "kwApplication.h"
#include "kwGameObject.h"
#include "kwTransform.h"
#include "kwInput.h"
#include "kwTime.h"
#include "kwImage.h"
#include "kwResources.h"
#include "kwObject.h"
#include "kwAnimator.h"

extern kw::Application application;

namespace kw
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	Camera::eCameraEffectType Camera::mType = Camera::eCameraEffectType::None;
	class Image* Camera::mCutton = nullptr;
	float Camera::mCuttonAlpha = 1.0f;
	float Camera::mAlphaTime = 0.0f;
	float Camera::mEndTime = 5.0f;

	void Camera::Initiailize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);

		mType = eCameraEffectType::FadeIn;
		//mCutton = Resources::Load<Image>(L"CarmeraImage", L"..\\Resources\\ScreenEffect\\Exit\\tile0001.bmp");
	}

	void Camera::Update()
	{		
		if (Input::GetKey(eKeyCode::LEFT))
			mLookPosition.x -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::RIGHT))
			mLookPosition.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::UP))
			mLookPosition.y -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::DOWN))
			mLookPosition.y += 100.0f * Time::DeltaTime();


		if (mTarget != nullptr)
		{
			mLookPosition
				= mTarget->GetComponent<Transform>()->GetPos();
		}

		if (mAlphaTime < mEndTime)
		{
			//255 - > 1
			mAlphaTime += Time::DeltaTime();
			float ratio = (mAlphaTime / mEndTime);

			if (mType == eCameraEffectType::FadeIn)
			{
				mCuttonAlpha = 1.0f;
			}
			else if (mType == eCameraEffectType::FadeOut)
			{
				mCuttonAlpha = ratio;
			}
			else
			{

			}
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Render(HDC hdc)
	{
		//if (mAlphaTime < mEndTime
		//	&& mType == eCameraEffectType::FadeIn)
		//{
		//	BLENDFUNCTION func = {};
		//	func.BlendOp = AC_SRC_OVER;
		//	func.BlendFlags = 0;
		//	func.AlphaFormat = AC_SRC_ALPHA;
		//	func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

		//	AlphaBlend(hdc, 0, 0
		//		, mResolution.x, mResolution.y
		//		, mCutton->GetHdc()
		//		, 0, 0
		//		, mCutton->GetWidth(), mCutton->GetHeight()
		//		, func);
		//}
	}

	void Camera::Clear()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
	}

	Vector2 Camera::GetCameraCenter()
	{
		Vector2 pos = Vector2::Zero;
		pos.x = mResolution.x / 2.0f;
		pos.y = mResolution.y / 2.0f;

		return pos;
	}

	void Camera::SceneEnterEffect()
	{
		GameObject* effect = object::Instantiate<GameObject>(eLayerType::SceneEffect);
		effect->SetIsUI(true);
		Animator* animator = effect->AddComponent<Animator>();
		animator->CreateAnimations(L"..\\Resources\\ScreenEffect\\Enter", GetCameraCenter(), 0.03f);
		animator->Play(L"ScreenEffectEnter", false);
	
	}

	void Camera::SceneExitEffect()
	{
		GameObject* effect = object::Instantiate<GameObject>(eLayerType::SceneEffect);
		effect->SetIsUI(true);
		Animator* animator = effect->AddComponent<Animator>();
		animator->CreateAnimations(L"..\\Resources\\ScreenEffect\\Exit", GetCameraCenter(), 0.04f);
		animator->Play(L"ScreenEffectExit", false);
	}
}