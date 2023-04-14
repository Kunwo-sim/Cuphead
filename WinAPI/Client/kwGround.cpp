#include "kwGround.h"
#include "kwCollider.h"
#include "kwCuphead.h"
#include "kwRigidbody.h"
#include "kwTransform.h"
#include "kwResources.h"
#include "kwImage.h"
#include "kwCuphead.h"

namespace kw
{
	Ground::Ground()
		: mCollider(nullptr)
		, mPlayer(nullptr)
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		SetPivot(GameObject::ePivot::LowCenter);
		mCollider = AddComponent<Collider>();

		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();
	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::Release()
	{

	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();

		Vector2 cupheadPos = cuphead->GetComponent<Transform>()->GetPos();
		Collider* cupheadCol = cuphead->GetComponent<Collider>();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = this->GetComponent<Transform>()->GetPos();

		if (cupheadPos.y < groundCol->GetCenter().y && rb->GetVelocity().y > 0.0f)
		{
			// ÄÅÇìµå ¹Ù´Ú À§Ä¡¸¦ ¶¥ À§·Î Á¶Á¤
			cupheadPos.y = (groundCol->GetCenter().y - groundCol->GetSize().y / 2.0f) + 1;
			cuphead->GetComponent<Transform>()->SetPos(cupheadPos);
			rb->SetGround(true);
		}
	}

	void Ground::OnCollisionStay(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();

		Vector2 cupheadPos = cuphead->GetComponent<Transform>()->GetPos();
		Collider* groundCol = this->GetComponent<Collider>();

		if (cupheadPos.y < groundCol->GetCenter().y && rb->GetVelocity().y > 0.0f)
		{
			// ÄÅÇìµå ¹Ù´Ú À§Ä¡¸¦ ¶¥ À§·Î Á¶Á¤
			cupheadPos.y = groundCol->GetCenter().y - groundCol->GetSize().y / 2.0f + 1;
			cuphead->GetComponent<Transform>()->SetPos(cupheadPos);
			rb->SetGround(true);
		}
	}

	void Ground::OnCollisionExit(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		cuphead->GroundExit();
	}

	void Ground::SetColliderSize(Vector2 size)
	{
		mCollider->SetSize(size);
	}
}
