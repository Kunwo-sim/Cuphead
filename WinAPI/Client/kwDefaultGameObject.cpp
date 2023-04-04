#include "kwDefaultGameObject.h"

namespace kw
{
	DefaultGameObject::DefaultGameObject()
	{
	}

	DefaultGameObject::~DefaultGameObject()
	{
	}

	void DefaultGameObject::Initialize()
	{
		GameObject::Initialize();
	}

	void DefaultGameObject::Update()
	{
		GameObject::Update();
	}

	void DefaultGameObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DefaultGameObject::Release()
	{

	}

	void DefaultGameObject::OnCollisionEnter(Collider* other)
	{

	}

	void DefaultGameObject::OnCollisionStay(Collider* other)
	{

	}

	void DefaultGameObject::OnCollisionExit(Collider* other)
	{

	}
}
