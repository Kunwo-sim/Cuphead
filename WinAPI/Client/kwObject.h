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
		gameObj->Initialize();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObeject(gameObj, type);
		gameObj->SetScene(scene);
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(eLayerType type, Vector2 pos)
	{
		T* gameObj = new T();
		gameObj->Initialize();
		gameObj->GameObject::GetComponent<Transform>()->SetPos(pos);
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObeject(gameObj, type);
		gameObj->SetScene(scene);
		
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(eLayerType type, Vector2 pos, GameObject::eDirection direction)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObeject(gameObj, type);
		gameObj->GameObject::GetComponent<Transform>()->SetPos(pos);
		gameObj->SetDirection(direction);
		gameObj->Initialize();
		gameObj->SetScene(scene);

		return gameObj;
	}

	static void Destory(GameObject* obj)
	{
		obj->SetState(GameObject::eState::Death);
	}
}