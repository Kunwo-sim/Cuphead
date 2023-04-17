#include "kwPurpleFlowerSeed.h"

#include "kwTime.h"
#include "kwObject.h"

#include "kwChomper.h"

namespace kw
{
	PurpleFlowerSeed::PurpleFlowerSeed()
	{

	}

	PurpleFlowerSeed::~PurpleFlowerSeed()
	{

	}

	void PurpleFlowerSeed::Initialize()
	{
		FlowerSeed::Initialize();

		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\PurpleSeed\\Fall", Vector2::Zero, 0.08f);
		mAnimator->CreateAnimations(L"..\\Resources\\Stage\\Carnation\\Object\\PurpleSeed\\Grow", Vector2::Zero, 0.04f);
		mAnimator->GetCompleteEvent(L"PurpleSeedGrow") = std::bind(&PurpleFlowerSeed::CreateChomper, this);
		
		mAnimator->Play(L"PurpleSeedFall", true);
	}

	void PurpleFlowerSeed::Update()
	{
		FlowerSeed::Update();
	}

	void PurpleFlowerSeed::Render(HDC hdc)
	{
		FlowerSeed::Render(hdc);
	}

	void PurpleFlowerSeed::Release()
	{

	}
	
	void PurpleFlowerSeed::PlayFallAnim()
	{
		mAnimator->Play(L"PurpleSeedFall", true);
	}

	void PurpleFlowerSeed::PlayGrowAnim()
	{
		mAnimator->Play(L"PurpleSeedGrow", false);
	}

	void PurpleFlowerSeed::CreateChomper()
	{
		object::Instantiate<Chomper>(eLayerType::Monster, mTransform->GetPos());
	}
}
