#pragma once
#include "CommonInclude.h"

namespace kw
{
	class Time
	{
	public:
		static void Initiailize();
		static void Update();
		static void Render(HDC hdc);

		__forceinline static double DeltaTime() { return mDeltaTime; }
		__forceinline static double IndependentDeltaTime() { return mIndependentDeltaTime; }
		static void SetTimeScale(double scale) { mTimeScale = scale; }

	private:
		static double mDeltaTime;
		static double mIndependentDeltaTime;
		static double mSecond;
		static double mTimeScale;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
	};
}
