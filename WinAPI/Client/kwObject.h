#pragma once
#include "kwGameObject.h"
#include "kwScene.h"
#include "kwSceneManager.h"
#include "kwTransform.h"

namespace kw::object
{
	template <typename T>
	static inline T* Instantiate(eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObeject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(eLayerType type, Vector2 pos)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObeject(gameObj, type);
		gameObj->Initialize();
		gameObj->GameObject::GetComponent<Transform>()->SetPos(pos);
		return gameObj;
	}

	static void Destory(GameObject* obj)
	{
		obj->SetState(GameObject::eState::Death);
	}
}