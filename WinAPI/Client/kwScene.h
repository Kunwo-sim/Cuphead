#pragma once
#include "kwEntity.h"
#include "kwLayer.h"

namespace kw
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Destroy();
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObeject(GameObject* obj, eLayerType layer);
		std::vector<GameObject*>& GetGameObjects(eLayerType layer);

	private:
		std::vector<Layer> mLayers;
	};
}
