#include "kwSlime.h"
#include "kwCuphead.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwResources.h"

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
		mImage = Resources::Load<Image>(L"Slime", L"..\\Resources\\Slime_Idle.bmp");
		mPos.x = 800;
		mPos.y = 450;

		GameObject::Initialize();
	}
	void Slime::Update()
	{
		GameObject::Update();
	}
	void Slime::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, mPos.x, mPos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}
	void Slime::Release()
	{
		GameObject::Release();
	}

}