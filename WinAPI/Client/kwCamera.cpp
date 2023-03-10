#include "kwCamera.h"
#include "kwApplication.h"
#include "kwGameObject.h"
#include "kwTransform.h"
#include "kwInput.h"
#include "kwTime.h"

extern kw::Application application;

namespace kw
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initiailize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
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

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Clear()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
	}
}