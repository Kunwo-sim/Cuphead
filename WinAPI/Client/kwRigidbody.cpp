#include "kwRigidbody.h"
#include "kwTime.h"
#include "kwGameObject.h"
#include "kwTransform.h"

namespace kw
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 1000.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, 2000.0f);
		mFriction = 100.0f;
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Initialize()
	{

	}

	void Rigidbody::Update()
	{
		mAccelation = mForce / mMass;
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// ������ ������
			Vector2 gravity = mGravity;
			gravity.Normalize();

			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		//Vector2 sideVelocity = mVelocity - gravity;
		//if (mLimitedVelocity.y < gravity.Length())
		//{
		//	gravity.Normalize();
		//	gravity *= mLimitedVelocity.y;
		//}

		//if (mLimitedVelocity.x < sideVelocity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitedVelocity.x;
		//}

		//// ������ ���� ( ����� ���� ����, �ӵ��� 0�� �ƴ�)
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	//�ӵ��� �ݴ�������� �������� ����ȴ�.
		//	Vector2 friction = -mVelocity;
		//	friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

		//	//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū ���

		//	if (mVelocity.Length() < friction.Length())
		//	{
		//		mVelocity = Vector2::Zero;
		//	}
		//	else
		//	{
		//		mVelocity += friction;
		//	}
		//}

		// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = pos + mVelocity * Time::DeltaTime();

		tr->SetPos(pos);
		mForce.Clear();
	}

	void Rigidbody::Render(HDC hdc)
	{

	}

	void Rigidbody::Release()
	{

	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}