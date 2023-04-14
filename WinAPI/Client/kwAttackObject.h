#pragma once
#include "kwGameObject.h"

namespace kw
{
	class AttackObject : public GameObject
	{
	public:
		AttackObject();
		virtual ~AttackObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	};
}
