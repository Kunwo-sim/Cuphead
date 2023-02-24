#include "kwSlime.h"
#include "kwCuphead.h"
#include "kwTime.h"
#include "kwSceneManager.h"
#include "kwResources.h"
#include "kwTransform.h"

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
		Transform* tr = GetComponent<Transform>();
		tr->SetPos({ 800,450 });
		mImage = Resources::Load<Image>(L"Slime", L"..\\Resources\\Slime_Idle.bmp");

		GameObject::Initialize();
	}
	void Slime::Update()
	{
		GameObject::Update();
	}
	void Slime::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}
	void Slime::Release()
	{
		GameObject::Release();
	}

}