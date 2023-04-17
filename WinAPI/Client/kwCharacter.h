#pragma once
#include "kwGameObject.h"

namespace kw
{
	class Character : public GameObject
	{
	public:
		Character();
		virtual ~Character();

		virtual void Initialize();
		virtual void Update();
		virtual void ReceiveDamage(float value);
		virtual void Die();

		float GetHp() { return mHp; };
		void SetHp(float value) { mHp = value; };

	private:
		float mHp;
		bool mIsDead;
	};
}
