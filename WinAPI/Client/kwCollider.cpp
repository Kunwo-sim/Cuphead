#include "kwCollider.h"
#include "kwTransform.h"
#include "kwGameObject.h"
#include "kwCamera.h"

namespace kw
{
	UINT Collider::ColliderNumber = 0;

	Collider::Collider()
		: Component(eComponentType::Collider)
		, mID(ColliderNumber++)
		, mTransform(nullptr)
		, mCenter(Vector2::Zero)
		, mOffset(Vector2::Zero)
		, mSize(100, 100)
		, mScale(Vector2::One)
		, mPos(Vector2::Zero)
	{

	}

	Collider::~Collider()
	{

	}

	void Collider::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}

	void Collider::Update()
	{
		mCenter = Camera::CalculatePos(mTransform->GetPos() + mOffset);

		if (GetOwner()->GetPivot() == GameObject::ePivot::LowCenter)
		{
			mCenter.y -= (mSize.y / 2.0f);
		}
	}

	void Collider::Render(HDC hdc)
	{
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		Vector2 LT = Vector2(mCenter.x - (mSize.x / 2.0f), mCenter.y - (mSize.y / 2.0f));
		Vector2 RB = Vector2(mCenter.x + (mSize.x / 2.0f), mCenter.y + (mSize.y / 2.0f));
		Rectangle(hdc, LT.x, LT.y, RB.x, RB.y);
		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(pen);
		DeleteObject(brush);
	}

	void Collider::Release()
	{

	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		GetOwner()->OnCollisionExit(other);
	}
}
