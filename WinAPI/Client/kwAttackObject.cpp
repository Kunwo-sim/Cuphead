#include "kwAttackObject.h"

#include "kwCuphead.h"


namespace kw
{
	AttackObject::AttackObject()
	{

	}

	AttackObject::~AttackObject()
	{

	}

	void AttackObject::Initialize()
	{
		GameObject::Initialize();
	}

	void AttackObject::Update()
	{
		GameObject::Update();
	}

	void AttackObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void AttackObject::Release()
	{

	}

	void AttackObject::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;
		
		cuphead->Hit();
	}

	void AttackObject::OnCollisionStay(Collider* other)
	{

	}

	void AttackObject::OnCollisionExit(Collider* other)
	{

	}
}
