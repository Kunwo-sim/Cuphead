#pragma once
#include "kwGameObject.h"

namespace kw
{
	class DragonPlatform : public GameObject
	{
	public:
		enum class PlatformType
		{
			A,
			B,
			C
		};

		DragonPlatform();
		virtual ~DragonPlatform();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlatformType(PlatformType type);

	private:
		class Ground* mGround;
		Vector2 mAddPos;
		PlatformType mPlatformType;
		float mSpeed;
	};
}
