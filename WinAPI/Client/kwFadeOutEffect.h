#pragma once
#include "kwGameObject.h"

namespace kw
{
	class FadeOutEffect : public GameObject
	{
	public:
		FadeOutEffect();
		virtual ~FadeOutEffect();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Image* mCutton;
		Vector2 mResolution;
		float mAlphaTime;
		float mCuttonAlpha;
		float mEndTime;
	};
}
