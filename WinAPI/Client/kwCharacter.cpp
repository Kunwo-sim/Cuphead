#include "kwCharacter.h"

namespace kw
{
	Character::Character()
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

	void Character::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Character::Release()
	{

	}
}
