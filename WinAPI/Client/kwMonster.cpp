#include "kwMonster.h"
#include "kwCuphead.h"

namespace kw
{
	Monster::Monster()
	{

	}

	Monster::~Monster()
	{

	}

	void Monster::Initialize()
	{
		Character::Initialize();
	}

	void Monster::Update()
	{
		Character::Update();
	}

	void Monster::Die()
	{
		Character::Die();
	}

	void Monster::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		cuphead->Hit();
	}
}