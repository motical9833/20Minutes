#pragma once
#include "yaScript.h"


namespace ya
{
	class BommerSoundEffectScript : public Script
	{
	public:
		BommerSoundEffectScript();
		virtual ~BommerSoundEffectScript();

		virtual void Initalize();
		virtual void Update();


		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

	private:
		float mTime;
	};
}