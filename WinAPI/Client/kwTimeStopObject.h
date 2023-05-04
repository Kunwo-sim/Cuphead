#pragma once
#include "kwGameObject.h"

namespace kw
{
	class TimeStopObject : public GameObject
	{
	public:
		TimeStopObject();
		virtual ~TimeStopObject();

		virtual void Initialize();
		virtual void Update();

		void SetStopTime(float time) { mStopTime = time; }

	private:
		float mTime;
		float mStopTime;
	};
}
