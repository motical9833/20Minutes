#include "yaTitleUIManager.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaTitleScene.h"

namespace ya
{
	TitleUIManager::TitleUIManager()
		:mainNumber(0)
		,subNumber(0)
		, mousePos{}

	{

	}
	TitleUIManager::~TitleUIManager()
	{

	}
	void TitleUIManager::Initalize()
	{

	}
	void TitleUIManager::Update()
	{
		MainUI(mainNumber,subNumber);
	}
	void TitleUIManager::FixedUpdate()
	{

	}
	void TitleUIManager::Render()
	{

	}
	void TitleUIManager::MainMenu()
	{
		if (mousePos.x >= -0.157f && mousePos.x <= 0.157f
			&& mousePos.y >= -0.302f && mousePos.y <= -0.215f)
		{
			SceneManager::GetTitleScene()->StartUI();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.157f && mousePos.x <= 0.157f
			&& mousePos.y >= -0.433f && mousePos.y <= -0.344f)
		{
			int a = 0;
			mousePos = {};
		}
		else if (mousePos.x >= -0.157f && mousePos.x <= 0.157f
			&& mousePos.y >= -0.562f && mousePos.y <= -0.475f)
		{
			int a = 0;
			mousePos = {};
		}
		else if (mousePos.x >= -0.157f && mousePos.x <= 0.157f
			&& mousePos.y >= -0.693f && mousePos.y <= -0.604f)
		{
			int a = 0;
			mousePos = {};
		}
	}
	void TitleUIManager::SelectMenu()
	{
		switch (subNumber)
		{
		case 0:
			SelectCharacter();
			break;
		case 1:
			SelectWeapon();
			break;
		case 2:

			break;
		}
	}
	void TitleUIManager::SelectCharacter()
	{
		if (mousePos.x >= -0.887f && mousePos.x <= -0.787f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(0);
			mousePos = {};
		}
		else if (mousePos.x >= -0.709f && mousePos.x <= -0.607f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(1);
			mousePos = {};
		}
		else if (mousePos.x >= -0.532f && mousePos.x <= -0.428f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(2);
			mousePos = {};
		}
		else if (mousePos.x >= -0.353f && mousePos.x <= -0.25f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(3);
			mousePos = {};
		}
		else if (mousePos.x >= -0.174f && mousePos.x <= -0.07f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(4);
			mousePos = {};
		}
		else if (mousePos.x >= 0.003f && mousePos.x <= 0.107f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(5);
			mousePos = {};
		}
		else if (mousePos.x >= -0.887f && mousePos.x <= -0.787f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(6);
			mousePos = {};
		}
		else if (mousePos.x >= -0.709f && mousePos.x <= -0.607f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(7);
			mousePos = {};
		}
		else if (mousePos.x >= -0.532f && mousePos.x <= -0.428f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(8);
			mousePos = {};
		}
		else if (mousePos.x >= -0.353f && mousePos.x <= -0.25f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f)
		{
			SceneManager::GetTitleScene()->ClickCharacter(9);
			mousePos = {};
		}
		else if (mousePos.x >= -0.907f && mousePos.x <= -0.592f
			&& mousePos.y >= -0.88f && mousePos.y <= -0.708f)
		{
			SceneManager::GetTitleScene()->WeaponSelectUI();
			NextSubUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.532f && mousePos.x <= -0.217f
			&& mousePos.y >= -0.88f && mousePos.y <= -0.708f)
		{
			SceneManager::GetTitleScene()->SelectScreenUI();
			BackMainUI();
			mousePos = {};
		}
	}
	void TitleUIManager::SelectWeapon()
	{
		if (mousePos.x >= -0.887f && mousePos.x <= -0.787f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickWeapon(0);
			mousePos = {};
		}
		else if (mousePos.x >= -0.709f && mousePos.x <= -0.607f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickWeapon(1);
			mousePos = {};
		}
		else if (mousePos.x >= -0.532f && mousePos.x <= -0.428f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickWeapon(2);
			mousePos = {};
		}
		else if (mousePos.x >= -0.353f && mousePos.x <= -0.25f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickWeapon(3);
			mousePos = {};
		}
		else if (mousePos.x >= -0.174f && mousePos.x <= -0.07f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickWeapon(4);
			mousePos = {};
		}
		else if (mousePos.x >= 0.003f && mousePos.x <= 0.107f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f)
		{
			SceneManager::GetTitleScene()->ClickWeapon(5);
			mousePos = {};
		}
		else if (mousePos.x >= -0.887f && mousePos.x <= -0.787f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f)
		{
			SceneManager::GetTitleScene()->ClickWeapon(6);
			mousePos = {};
		}
		else if (mousePos.x >= -0.709f && mousePos.x <= -0.607f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f)
		{
			SceneManager::GetTitleScene()->ClickWeapon(7);
			mousePos = {};
		}
		else if (mousePos.x >= -0.907f && mousePos.x <= -0.592f
			&& mousePos.y >= -0.88f && mousePos.y <= -0.708f)
		{
			SceneManager::GetTitleScene()->Start();
			mousePos = {};
		}
		else if (mousePos.x >= -0.532f && mousePos.x <= -0.217f
			&& mousePos.y >= -0.88f && mousePos.y <= -0.708f)
		{
			SceneManager::GetTitleScene()->CharacterSelectUI();
			BackSubUI();
			mousePos = {};
		}
	}
	void TitleUIManager::selectionScreenUI()
	{

	}
	void TitleUIManager::MainUI(UINT8 main,UINT8 sub)
	{
		switch (main)
		{
		case 0:
			MainMenu();
			break;
		case 1:
			SelectMenu();
			break;
		case 2:

			break;
		}
	}
}