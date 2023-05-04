#include "kwParryObject.h"

namespace kw
{
	ParryObject::ParryObject()
		: mOwner(nullptr)
	{
	}

	ParryObject::~ParryObject()
	{
	}

	void ParryObject::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(50, 50));
		
		GameObject::Initialize();
	}

	void ParryObject::Update()
	{
		mTransform->SetPos(mOwner->GetComponent<Transform>()->GetPos());

		GameObject::Update();
	}

	void ParryObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ParryObject::Release()
	{

	}

	void ParryObject::SetOwner(GameObject* owner)
	{
		mOwner = owner;

		SetPivot(mOwner->GetPivot());
	}

	void ParryObject::SetColliderSize(Vector2 size)
	{
		mCollider->SetSize(size);
	}
}
