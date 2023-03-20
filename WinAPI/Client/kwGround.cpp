#include "kwGround.h"
#include "kwCollider.h"
#include "kwCuphead.h"
#include "kwRigidbody.h"
#include "kwTransform.h"

namespace kw
{
	Ground::Ground()
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(1600.0f, 100.0f));
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

		if (cupheadPos.y < groundCol->GetCenter().y)
		{
			// ÄÅÇìµå ¹Ù´Ú À§Ä¡¸¦ ¶¥ À§·Î Á¶Á¤
			cupheadPos.y = groundCol->GetCenter().y - groundCol->GetSize().y / 2.0f;
			cuphead->GetComponent<Transform>()->SetPos(cupheadPos);
			rb->SetGround(true);
		}
		
		//float fLen = fabs(cupheadPos.y - groundPos.y);
		//float fSize = (cupheadCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		//if (fLen < fSize)
		//{
		//	Transform* cupTr = cuphead->GetComponent<Transform>();
		//	Transform* grTr = this->GetComponent<Transform>();

		//	Vector2 cupPos = cupTr->GetPos();
		//	Vector2 grPos = grTr->GetPos();

		//	cupPos.x -= (fSize - fLen) - 1.0f;
		//	cupPos.y -= (fSize - fLen) - 1.0f;
		//	cupTr->SetPos(cupPos);
		//}
	}

	void Ground::OnCollisionStay(Collider* other)
	{
		Cuphead* cuphead = dynamic_cast<Cuphead*>(other->GetOwner());
		if (cuphead == nullptr)
			return;

		Rigidbody* rb = cuphead->GetComponent<Rigidbody>();

		Vector2 cupheadPos = cuphead->GetComponent<Transform>()->GetPos();
		Collider* groundCol = this->GetComponent<Collider>();

		if (cupheadPos.y < groundCol->GetCenter().y)
		{
			// ÄÅÇìµå ¹Ù´Ú À§Ä¡¸¦ ¶¥ À§·Î Á¶Á¤
			cupheadPos.y = groundCol->GetCenter().y - groundCol->GetSize().y / 2.0f;
			cuphead->GetComponent<Transform>()->SetPos(cupheadPos);
			rb->SetGround(true);
		}
	}

	void Ground::OnCollisionExit(Collider* other)
	{

	}
}
