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

		virtual void StopBGM();
		virtual class Cuphead* GetPlayer();

		void AddGameObject(GameObject* obj, eLayerType layer);
		void AddGameObjectFront(GameObject* obj, eLayerType layer);
		std::vector<GameObject*>& GetGameObjects(eLayerType layer);

	protected:
		std::vector<Layer> mLayers;
		class Sound* mBGM;
	};
}
