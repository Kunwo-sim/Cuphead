#pragma once
#include "kwEntity.h"
#include "kwComponent.h"
namespace kw
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetPos(Vector2 pos) { mPos = pos; };

	protected:
		Vector2 mPos;

	private:
		std::vector<Component*> mComponents;
	};
}

