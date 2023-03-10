#include "kwTitleCharacter.h"
#include "kwTransform.h"
#include "kwTime.h"

namespace kw
{
	TitleCharacter::TitleCharacter()
	{

	}

	TitleCharacter::~TitleCharacter()
	{

	}

	void TitleCharacter::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(640.0f, 720.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Title\\Character", Vector2::Zero, 0.05f);
		mAnimator->Play(L"TitleCharacter", true);

		GameObject::Initialize();
	}

	void TitleCharacter::Update()
	{
		GameObject::Update();
	}

	void TitleCharacter::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void TitleCharacter::Release()
	{
		GameObject::Release();
	}
}