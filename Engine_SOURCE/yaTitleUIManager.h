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
		void SelectMenu();
		void SelectCharacter();
		void SelectWeapon();


		void selectionScreenUI();
		void SetMousePos(Vector3 pos) { mousePos = pos; }
		void MainUI(UINT8 main, UINT8 sub);



		void NextMainUI() { mainNumber++; subNumber = 0; }
		void BackMainUI() { mainNumber--; subNumber = 0; }
		void NextSubUI() { subNumber++; }
		void BackSubUI() { subNumber--; }

	private:
		UINT8 mainNumber;
		UINT8 subNumber;

		Vector3 mousePos;
	};
}