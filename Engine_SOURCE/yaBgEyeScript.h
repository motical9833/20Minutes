#pragma once
#include "yaScript.h"


namespace ya
{
	class BgEyeScript : public Script
	{
	public:
		BgEyeScript();
		virtual ~BgEyeScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		void End();

		void Next();
		void Reset();

	private:
		float mTime;
		float mSpeed;

		bool bStop;
		bool bCycle;
	};
}