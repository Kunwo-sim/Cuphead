#include "kwSlime.h"
#include "kwCuphead.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwResources.h"
#include "kwTransform.h"
#include "kwCollider.h"

namespace kw
{
	Slime::Slime()
	{

	}

	Slime::~Slime()
	{

	}

	void Slime::Initialize()
	{
		GameObject::Initialize();
		SetPivot(ePivot::LowCenter);

		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
	}
	void Slime::Update()
	{
		GameObject::Update();
	}

	void Slime::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Slime::Release()
	{
		GameObject::Release();
	}

}