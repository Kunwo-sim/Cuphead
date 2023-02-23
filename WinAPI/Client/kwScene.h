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
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObeject(GameObject* obj, eLayerType layer);

	private:
		std::vector<Layer> mLayers;
	};
}
