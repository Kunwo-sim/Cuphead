#include "kwPinkFlowerSeed.h"

#include "kwTime.h"
#include "kwObject.h"
#include "kwParryObject.h"

#include "kwVenus.h"

namespace kw
{
	PinkFlowerSeed::PinkFlowerSeed()
		: mParryObject(nullptr)
	{

	}

	PinkFlowerSeed::~PinkFlowerSeed()
	{

	}

	void PinkFlowerSeed::Initialize()
	{
		FlowerSeed::Initialize();

		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\PinkSeed\\Fall", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\PinkSeed\\Grow", Vector2::Zero, 0.04f);
		mAnimator->GetCompleteEvent(L"PinkSeedGrow") = std::bind(&PinkFlowerSeed::CreateVine, this);
		mAnimator->Play(L"PinkSeedFall", true);

		mParryObject = object::Instantiate<ParryObject>(eLayerType::ParryObject, mTransform->GetPos());
		mParryObject->SetOwner(this);
		mParryObject->SetColliderSize(Vector2(150.0f, 150.0f));
	}

	void PinkFlowerSeed::Update()
	{
		FlowerSeed::Update();
	}

	void PinkFlowerSeed::Render(HDC hdc)
	{
		FlowerSeed::Render(hdc);
	}

	void PinkFlowerSeed::Release()
	{

	}

	void PinkFlowerSeed::PlayFallAnim()
	{
		mAnimator->Play(L"PinkSeedFall", true);
	}

	void PinkFlowerSeed::PlayGrowAnim()
	{
		object::Destory(mParryObject);
		mAnimator->Play(L"PinkSeedGrow", true);
	}

	void PinkFlowerSeed::CreateVine()
	{
		FlowerSeed::CreateVine();
	}

	void PinkFlowerSeed::PlayLongVineEndAnim()
	{
		FlowerSeed::PlayLongVineEndAnim();
		Vector2 pos = mTransform->GetPos();
		pos.y -= 300.0f;
		Venus* obj = object::Instantiate<Venus>(eLayerType::Monster, pos);
	}
}
