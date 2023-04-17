#include "kwLayer.h"


namespace kw
{
	Layer::Layer()
	{

	}

	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState() != GameObject::eState::Active)
				continue;

			gameObj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			GameObject* gameObj = mGameObjects[i];

			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState() != GameObject::eState::Active)
				continue;

			gameObj->Update();
		}

		//for (GameObject* gameObj : mGameObjects)
		//{
		//	if (gameObj == nullptr)
		//		continue;

		//	if (gameObj->GetState() != GameObject::eState::Active)
		//		continue;

		//	gameObj->Update();
		//}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState() != GameObject::eState::Active)
				continue;

			gameObj->Render(hdc);
		}
	}

	void Layer::Release()
	{

	}

	void Layer::AddGameObject(GameObject* gameObj)
	{
		if (gameObj == nullptr)
			return;

		mGameObjects.push_back(gameObj);
	}
}
