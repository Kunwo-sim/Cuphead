#include "kwFadeOutEffect.h"

#include "kwSceneManager.h"
#include "kwCamera.h"
#include "kwTime.h"
#include "kwResources.h"
#include "kwImage.h"
#include "kwObject.h"

namespace kw
{
	FadeOutEffect::FadeOutEffect()
		: mCutton(nullptr)
		, mResolution(Vector2::Zero)
		, mCuttonAlpha(0.0f)
		, mAlphaTime(0.0f)
		, mEndTime(5.0f)
	{
	}

	FadeOutEffect::~FadeOutEffect()
	{
	}

	void FadeOutEffect::Initialize()
	{
		mResolution = Camera::GetResolution();
		mCutton = Image::Create(L"FadeOut", 1280, 720, RGB(0, 0, 0));

		GameObject::Initialize();
	}

	void FadeOutEffect::Update()
	{
		if (mAlphaTime < mEndTime)
		{
			//255 - > 1
			mAlphaTime += Time::DeltaTime();
			float ratio = (mAlphaTime / mEndTime);

			mCuttonAlpha = ratio;
		}
		else
		{
			mCuttonAlpha = 1.0f;
			object::Destory(this);
			SceneManager::LoadScene(eSceneType::OverWorld);
		}

		GameObject::Update();
	}

	void FadeOutEffect::Render(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

		AlphaBlend(hdc, 0, 0
			, mResolution.x, mResolution.y
			, mCutton->GetHdc()
			, 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, func);

		GameObject::Render(hdc);
	}
}
