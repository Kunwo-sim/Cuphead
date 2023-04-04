#include "kwDefaultGameObject.h"

namespace kw
{
	Default::Default()
	{
	}

	Default::~Default()
	{
	}

	void Default::Initialize()
	{
		GameObject::Initialize();
	}

	void Default::Update()
	{
		GameObject::Update();
	}

	void Default::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Default::Release()
	{

	}

	void Default::OnCollisionEnter(Collider* other)
	{

	}

	void Default::OnCollisionStay(Collider* other)
	{

	}

	void Default::OnCollisionExit(Collider* other)
	{

	}
}
