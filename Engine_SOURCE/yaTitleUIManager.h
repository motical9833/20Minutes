#pragma once
#include "yaScript.h"
#include <array>

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

		void MainMenu();
		void selectionScreenUI();

	private:
		UINT8 mainNumber;
		UINT8 subNumber;
	};
}