#pragma once
#include "CommonInclude.h"
#include "kwEnums.h"
#include "kwCollider.h"

namespace kw
{
	class Scene;
	class CollisionManager
	{
	public:
		static void Update();
		static void LayerCollision(Scene* scene, eLayerType left, eLayerType right);
		static bool Intersect(Collider* left, Collider* right);

		static void SetLayer(eLayerType left, eLayerType right, bool value);
		static void Clear();

	private:
		static WORD mMatrix[(UINT)eLayerType::End];
	};
}
