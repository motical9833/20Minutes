#pragma once
#include "yaScript.h"

namespace ya
{
	class FadeScript : public Script
	{
	public:
		FadeScript();
		virtual ~FadeScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		float currentTime;
	};
}