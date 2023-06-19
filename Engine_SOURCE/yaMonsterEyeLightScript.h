#pragma once
#include "yaScript.h"


namespace ya
{
	class MonsterEyeLightScript : public Script
	{
	public:
		MonsterEyeLightScript(Vector3 leftDir,Vector3 rightDir);
		virtual ~MonsterEyeLightScript();

		virtual void Initalize();
		virtual void Update();


		void SetLeft();
		void SetRight();
		void SetLeftCharge();
		void SetRightCharge();
		void SetLeftAttack();
		void SetRightAttack();
		void SetLeftHit();
		void SetRightHit();
	private:
		Vector3 leftPos;
		Vector3 rightPos;
	};
}