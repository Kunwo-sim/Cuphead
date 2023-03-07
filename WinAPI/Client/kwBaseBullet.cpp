#include "kwBaseBullet.h"
#include "kwTransform.h"
#include "kwTime.h"

namespace kw
{
	BaseBullet::BaseBullet()
	{
	}
	BaseBullet::~BaseBullet()
	{
	}
	void BaseBullet::Initialize()
	{
	}
	void BaseBullet::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 100.0f * Time::DeltaTime();
		tr->SetPos(pos);

	}
	void BaseBullet::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 255));

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		Ellipse(hdc, pos.x, pos.y, pos.x + 50, pos.y + 50);

		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(pen);
	}
	void BaseBullet::Release()
	{
	}
}