#pragma once
#include "kwGameObject.h"

namespace kw
{
	class Ground : public GameObject
	{
	public:
		Ground();
		virtual ~Ground();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlayer(class Cuphead* player) { mPlayer = player; }

	private:
		class Collider* mCollider;
		class Image* mImage;
		class Cuphead* mPlayer;
	};
}
