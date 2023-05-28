#pragma once
#include "yaScript.h"


namespace ya
{
	class TitleUIManager : public Script
	{
	public:
		TitleUIManager();
		virtual ~TitleUIManager();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:

	};
}