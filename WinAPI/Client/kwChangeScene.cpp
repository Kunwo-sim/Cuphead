#include "kwChangeScene.h"

#include "kwSceneManager.h"
#include "kwTime.h"

#include "kwSpriteRenderer.h"
#include "kwObject.h"
#include "kwImage.h"
#include "kwCamera.h"

namespace kw
{
	ChangeScene::ChangeScene()
		: mLoadScene(eSceneType::Title)
		, mTime(0.0f)
	{

	}

	ChangeScene::~ChangeScene()
	{

	}

	void ChangeScene::Initialize()
	{
		Scene::Initialize();

		GameObject* obj = object::Instantiate<GameObject>(eLayerType::BG);
		Image* backGround = Image::Create(L"BlackBackGround", 1280, 720, RGB(0, 0, 0));
		obj->AddComponent<SpriteRenderer>()->AddSprite(backGround, Vector2::Zero, false);		
	}

	void ChangeScene::Update()
	{
		Scene::Update();

		mTime += Time::DeltaTime();

		if (mTime > 1.0f)
		{
			SceneManager::LoadScene(mLoadScene);
		}
	}

	void ChangeScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void ChangeScene::Release()
	{
		Scene::Release();
	}

	void ChangeScene::OnEnter()
	{
		mTime = 0.0f;
	}

	void ChangeScene::OnExit()
	{
		Scene::OnExit();
	}
}