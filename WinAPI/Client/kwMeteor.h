#pragma once
#include "kwGameObject.h"

namespace kw
{
	class Meteor : public GameObject
	{
	public:
		Meteor();
		virtual ~Meteor();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);

		void SetDirection(int value) { mDirection = value; };

	private:
		float mSpeed;
		double mTime;
		int mDirection;
	};
}
