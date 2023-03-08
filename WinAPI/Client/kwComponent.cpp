#include "kwComponent.h"

namespace kw
{
	Component::Component(eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{

	}

	Component::~Component()
	{

	}

	void Component::Initialize()
	{

	}

	void Component::Update()
	{

	}

	void Component::Render(HDC hdc)
	{

	}

	void Component::Release()
	{

	}
}