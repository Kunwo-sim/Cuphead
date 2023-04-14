#pragma once
#include "kwEngine.h"

namespace kw
{
	class GameObject;
	class Camera
	{
	public:
		enum class eCameraEffectType
		{
			None,
			FadeIn,
			FadeOut,
			//Shake,
			End,
		};

		static void Initiailize();
		static void Update();
		static void Render(HDC hdc);
		static void Clear();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static void SetLookPosition(Vector2 pos) { mLookPosition = pos; }
		static Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }
		static Vector2 GetCameraCenter();
		static void SceneEnterEffect();
		static void SceneExitEffect();

	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;

		static eCameraEffectType mType;
		static class Image* mCutton;
		static float mCuttonAlpha;
		static float mAlphaTime;
		static float mEndTime;
	};
}

