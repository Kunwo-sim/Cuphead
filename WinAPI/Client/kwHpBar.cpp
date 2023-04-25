#include "kwHpBar.h"

#include "kwSceneManager.h"

#include "kwCuphead.h"

namespace kw
{
	HpBar::HpBar()
		: mPrevHp(3)
	{
	}

	HpBar::~HpBar()
	{
	}

	void HpBar::Initialize()
	{
		SetPivot(ePivot::LowCenter);

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Hp\\1", Vector2::Zero, 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Hp\\2", Vector2::Zero, 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Hp\\3", Vector2::Zero, 0.2f);
		mAnimator->Play(L"Hp3", true);

		GameObject::Initialize();
	}

	void HpBar::Update()
	{
		int hp = SceneManager::GetPlayer()->GetHp();
		if (mPrevHp != hp)
		{
			switch (hp)
			{
			case 3:
				mAnimator->Play(L"Hp3", true);
				break;
			case 2:
				mAnimator->Play(L"Hp2", true);
				break;
			case 1:
				mAnimator->Play(L"Hp1", true);
				break;
			default:
				break;
			}

			mPrevHp = hp;
		}

		GameObject::Update();
	}

	void HpBar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
