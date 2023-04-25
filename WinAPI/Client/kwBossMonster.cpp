#include "kwBossMonster.h"

#include "kwSceneManager.h"
#include "kwInput.h"
#include "kwResources.h"
#include "kwObject.h"
#include "kwTime.h"

#include "kwKnockOut.h"
#include "kwSound.h"

namespace kw
{
	BossMonster::BossMonster()
		: mKnoctOutSound(nullptr)
	{

	}

	BossMonster::~BossMonster()
	{

	}

	void BossMonster::Initialize()
	{
		mKnoctOutSound = Resources::Load<Sound>(L"KnoctOutSound", L"..\\Resources\\Sound\\SFX\\KhockOut.wav");
		Monster::Initialize();
	}

	void BossMonster::Update()
	{
		Monster::Update();
	}

	void BossMonster::Die()
	{
		Time::SetTimeScale(0.0);
		SceneManager::GetActiveScene()->StopBGM();
		Input::SetInputEnable(false);
		mKnoctOutSound->Play(false);
		object::Instantiate<KnockOut>(eLayerType::Effect, Vector2::Zero);
		Monster::Die();
	}
}