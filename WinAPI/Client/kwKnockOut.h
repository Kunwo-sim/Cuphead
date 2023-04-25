#pragma once
#include "kwGameObject.h"

namespace kw
{
	class KnockOut : public GameObject
	{
	public:
		KnockOut();
		virtual ~KnockOut();

		virtual void Initialize();
		virtual void Update();
		void KnockOutCallback();

	private:
		class Sound* mExplosionSFX;
	};
}
