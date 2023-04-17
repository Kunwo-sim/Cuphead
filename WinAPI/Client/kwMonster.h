#pragma once
#include "kwCharacter.h"

namespace kw
{
	class Monster : public Character
	{
	public:
		Monster();
		virtual ~Monster();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Die() override;
		virtual void OnCollisionEnter(class Collider* other) override;
	private:
	};
}


