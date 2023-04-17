#include "kwCharacter.h"

namespace kw
{
	Character::Character()
		: mHp(100.0f)
		, mIsDead(false)
	{

	}

	Character::~Character()
	{

	}

	void Character::Initialize()
	{
		GameObject::Initialize();
	}

	void Character::Update()
	{
		GameObject::Update();
	}

	void Character::ReceiveDamage(float value)
	{
		mHp -= value;

		if (mHp <= 0)
		{
			mHp = 0;
			Die();
		}
	}

	void Character::Die()
	{
		mIsDead = true;
	}
}
