#pragma once
#include "yaScript.h"


namespace ya
{
	class ReloadBarScript : public Script
	{
	public:
		ReloadBarScript();
		virtual ~ReloadBarScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetReloadUITimeMul(float value) { mSpeedMul += value; }
		void SetReloadUITimeRed(float value) { mSpeedMul -= value; }
		void SetKillClip(float value) { killClip += value; }
		void UIOn();
		void UIOff();

	private:
		float mCurrentTime;
		float mTimeLimit;
		float mSpeed;
		float mSpeedMul;
		float killClip;
		float distance;
	};
}