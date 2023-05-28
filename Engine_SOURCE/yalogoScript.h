#pragma once
#include "yaScript.h"


namespace ya
{
	class logoScript : public Script
	{
	public:
		logoScript();
		virtual ~logoScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void Next();
		void Reset();

	private:
		
	};
}