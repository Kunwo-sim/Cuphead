#pragma once
#include "kwEntity.h"
#include "kwComponent.h"

namespace kw
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Pause,
			Death,
		};

		enum class ePivot
		{
			MiddleCenter,
			LowCenter,
		};

		enum class eDirection
		{
			Front,
			Up,
			UpDiagnal,
			Down,
			DownDiagnal,
			Left,
			Right,
			Side,
			None
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mComponents)
			{
				if (dynamic_cast<T*>(comp))
					return dynamic_cast<T*>(comp);
			}

			return nullptr;
		}

		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; }
		ePivot GetPivot() { return mPivot; }
		void SetPivot(ePivot pivot) { mPivot = pivot; }
		eDirection GetDirection() { return mDirection; }
		void SetDirection(eDirection direction) { mDirection = direction; }

		bool GetFlipX() { return mFlipX; }
		void SetFlipX(bool value) { mFlipX = value; }

	private:
		std::vector<Component*> mComponents;
		eState mState;
		ePivot mPivot;
		eDirection mDirection;

		bool mFlipX;
		bool mFlipY;
	};
}

