#include "kwOverWorldEntrance.h"
#include "kwCuphead.h"

namespace kw
{
	OverWorldEntrance::OverWorldEntrance()
	{
	}

	OverWorldEntrance::~OverWorldEntrance()
	{
	}

	void OverWorldEntrance::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mAnimator = AddComponent<Animator>();

		GameObject::Initialize();
	}

	void OverWorldEntrance::Update()
	{
		GameObject::Update();
	}

	void OverWorldEntrance::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void OverWorldEntrance::Release()
	{

	}

	void OverWorldEntrance::OnCollisionEnter(Collider* other)
	{

	}

	void OverWorldEntrance::OnCollisionStay(Collider* other)
	{

	}

	void OverWorldEntrance::OnCollisionExit(Collider* other)
	{

	}
}
