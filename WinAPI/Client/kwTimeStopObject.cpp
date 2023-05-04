#include "kwTimeStopObject.h"

#include "kwObject.h"
#include "kwTime.h"
namespace kw
{
	TimeStopObject::TimeStopObject()
		: mTime(0.0f)
	{
		mTimeIndependent = true;
	}

	TimeStopObject::~TimeStopObject()
	{
	}

	void TimeStopObject::Initialize()
	{
		Time::SetTimeScale(0.0);

		GameObject::Initialize();
	}

	void TimeStopObject::Update()
	{
		mTime += Time::IndependentDeltaTime();

		if (mTime > mStopTime)
		{
			Time::SetTimeScale(1.0);
			object::Destory(this);
		}

		GameObject::Update();
	}
}
