#include "kwBlueFlowerSeed.h"

#include "kwTime.h"
#include "kwObject.h"

#include "kwVenus.h"

namespace kw
{
	BlueFlowerSeed::BlueFlowerSeed()
	{

	}

	BlueFlowerSeed::~BlueFlowerSeed()
	{

	}

	void BlueFlowerSeed::Initialize()
	{
		FlowerSeed::Initialize();

		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\BlueSeed\\Fall", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\BlueSeed\\Grow", Vector2::Zero, 0.04f);
		mAnimator->GetCompleteEvent(L"BlueSeedGrow") = std::bind(&BlueFlowerSeed::CreateVine, this);
		mAnimator->Play(L"BlueSeedFall", true);
	}

	void BlueFlowerSeed::Update()
	{
		FlowerSeed::Update();
	}

	void BlueFlowerSeed::Render(HDC hdc)
	{
		FlowerSeed::Render(hdc);
	}

	void BlueFlowerSeed::Release()
	{

	}

	void BlueFlowerSeed::PlayFallAnim()
	{
		mAnimator->Play(L"BlueSeedFall", true);
	}

	void BlueFlowerSeed::PlayGrowAnim()
	{
		mAnimator->Play(L"BlueSeedGrow", true);
	}

	void BlueFlowerSeed::CreateVine()
	{
		FlowerSeed::CreateVine();
	}

	void BlueFlowerSeed::PlayLongVineEndAnim()
	{
		FlowerSeed::PlayLongVineEndAnim();
		Vector2 pos = mTransform->GetPos();
		pos.y -= 300.0f;
		Venus* obj = object::Instantiate<Venus>(eLayerType::Monster, pos);
	}
}
