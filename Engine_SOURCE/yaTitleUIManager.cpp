#include "yaTitleUIManager.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaTitleScene.h"
#include "yaInput.h"
#include "yaAudioSource.h"

namespace ya
{
	TitleUIManager::TitleUIManager()
		:mainNumber(0)
		, subNumber(0)
		, mousePos{}
		, selectNum(0)

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
		MainUI(mainNumber, subNumber);
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
			&& mousePos.y >= -0.302f && mousePos.y <= -0.215f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->StartUI();
			SceneManager::GetTitleScene()->GetFaceTexts()[0]->Life();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.157f && mousePos.x <= 0.157f
			&& mousePos.y >= -0.433f && mousePos.y <= -0.344f && SceneManager::GetTitleScene()->GetMainUIbutterns()[5]->GetState() == GameObject::Dead)
		{
			for (size_t i = 4; i < SceneManager::GetTitleScene()->GetMainUIbutterns().size(); i++)
			{
				SceneManager::GetTitleScene()->GetMainUIbutterns()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetMainUIbutterns()[5]->Life();
			mousePos = {};
		}
		else if (mousePos.x >= -0.157f && mousePos.x <= 0.157f
			&& mousePos.y >= -0.562f && mousePos.y <= -0.475f && SceneManager::GetTitleScene()->GetMainUIbutterns()[6]->GetState() == GameObject::Dead)
		{
			for (size_t i = 4; i < SceneManager::GetTitleScene()->GetMainUIbutterns().size(); i++)
			{
				SceneManager::GetTitleScene()->GetMainUIbutterns()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetMainUIbutterns()[6]->Life();
			mousePos = {};
		}
		else if (mousePos.x >= -0.157f && mousePos.x <= 0.157f
			&& mousePos.y >= -0.693f && mousePos.y <= -0.604f && SceneManager::GetTitleScene()->GetMainUIbutterns()[7]->GetState() == GameObject::Dead)
		{
			for (size_t i = 4; i < SceneManager::GetTitleScene()->GetMainUIbutterns().size(); i++)
			{
				SceneManager::GetTitleScene()->GetMainUIbutterns()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetMainUIbutterns()[7]->Life();
			mousePos = {};
		}
		else if (mousePos.x >= -0.157f && mousePos.x <= 0.157f
			&& mousePos.y >= -0.302f && mousePos.y <= -0.215f && SceneManager::GetTitleScene()->GetMainUIbutterns()[4]->GetState() == GameObject::Dead)
		{
			for (size_t i = 4; i < SceneManager::GetTitleScene()->GetMainUIbutterns().size(); i++)
			{
				SceneManager::GetTitleScene()->GetMainUIbutterns()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetMainUIbutterns()[4]->Life();
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
	void TitleUIManager::SelectMap()
	{
		switch (subNumber)
		{
		case 0:
			Map();
			break;
		case 1:
			break;
		case 2:

			break;
		}
	}
	void TitleUIManager::Map()
	{
		if (mousePos.x >= -0.589f && mousePos.x <= -0.241f
			&& mousePos.y >= 0.01f && mousePos.y <= 0.419f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			for (size_t i = 1; i < SceneManager::GetTitleScene()->GetSelectMapObjs().size() - 4; i++)
			{
				if (i % 2 == 0)
					SceneManager::GetTitleScene()->GetSelectMapObjs()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetSelectMapObjs()[2]->Life();
			mousePos = {};
		}
		else if (mousePos.x >= -0.172f && mousePos.x <= 0.175f
			&& mousePos.y >= 0.01f && mousePos.y <= 0.419f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			for (size_t i = 1; i < SceneManager::GetTitleScene()->GetSelectMapObjs().size() - 4; i++)
			{
				if (i % 2 == 0)
					SceneManager::GetTitleScene()->GetSelectMapObjs()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetSelectMapObjs()[4]->Life();
			mousePos = {};
		}
		else if (mousePos.x >= 0.246f && mousePos.x <= 0.587f
			&& mousePos.y >= 0.01f && mousePos.y <= 0.419f && Input::GetKeyDown(eKeyCode::LBTN))
		{

			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			for (size_t i = 1; i < SceneManager::GetTitleScene()->GetSelectMapObjs().size() - 4; i++)
			{
				if (i % 2 == 0)
					SceneManager::GetTitleScene()->GetSelectMapObjs()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetSelectMapObjs()[6]->Life();
			mousePos = {};
		}
		else if (mousePos.x >= -0.218f && mousePos.x <= -0.136f
			&& mousePos.y >= -0.342f && mousePos.y <= -0.246f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			Reset();
			SceneManager::GetTitleScene()->Start();
			mousePos = {};
		}
		else if (mousePos.x >= 0.137f && mousePos.x <= 0.216f
			&& mousePos.y >= -0.342f && mousePos.y <= -0.246f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOff();
			BackMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.589f && mousePos.x <= -0.241f
			&& mousePos.y >= 0.01f && mousePos.y <= 0.419f && SceneManager::GetTitleScene()->GetSelectMapObjs()[1]->GetComponent<Transform>()->GetScale() == Vector3(3.0f, 2.0f, 1.0f))
		{
			for (size_t i = 1; i < SceneManager::GetTitleScene()->GetSelectMapObjs().size() - 4; i++)
			{
				SceneManager::GetTitleScene()->GetSelectMapObjs()[i]->GetComponent<Transform>()->SetScale(Vector3(3.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetSelectMapObjs()[1]->GetComponent<Transform>()->SetScale(Vector3(3.1f, 2.1f, 1.0f));
			SceneManager::GetTitleScene()->GetSelectMapObjs()[2]->GetComponent<Transform>()->SetScale(Vector3(3.1f, 2.1f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			mousePos = {};
		}
		else if (mousePos.x >= -0.172f && mousePos.x <= 0.175f
			&& mousePos.y >= 0.01f && mousePos.y <= 0.419f && SceneManager::GetTitleScene()->GetSelectMapObjs()[3]->GetComponent<Transform>()->GetScale() == Vector3(3.0f, 2.0f, 1.0f))
		{
			for (size_t i = 1; i < SceneManager::GetTitleScene()->GetSelectMapObjs().size() - 4; i++)
			{
				SceneManager::GetTitleScene()->GetSelectMapObjs()[i]->GetComponent<Transform>()->SetScale(Vector3(3.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetSelectMapObjs()[3]->GetComponent<Transform>()->SetScale(Vector3(3.1f, 2.1f, 1.0f));
			SceneManager::GetTitleScene()->GetSelectMapObjs()[4]->GetComponent<Transform>()->SetScale(Vector3(3.1f, 2.1f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			mousePos = {};
		}
		else if (mousePos.x >= 0.246f && mousePos.x <= 0.587f
			&& mousePos.y >= 0.01f && mousePos.y <= 0.419f && SceneManager::GetTitleScene()->GetSelectMapObjs()[5]->GetComponent<Transform>()->GetScale() == Vector3(3.0f, 2.0f, 1.0f))
		{
			for (size_t i = 1; i < SceneManager::GetTitleScene()->GetSelectMapObjs().size() - 4; i++)
			{
				SceneManager::GetTitleScene()->GetSelectMapObjs()[i]->GetComponent<Transform>()->SetScale(Vector3(3.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetSelectMapObjs()[5]->GetComponent<Transform>()->SetScale(Vector3(3.1f, 2.1f, 1.0f));
			SceneManager::GetTitleScene()->GetSelectMapObjs()[6]->GetComponent<Transform>()->SetScale(Vector3(3.1f, 2.1f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			mousePos = {};
		}
		else if (mousePos.x >= -0.218f && mousePos.x <= -0.136f
			&& mousePos.y >= -0.342f && mousePos.y <= -0.246f && SceneManager::GetTitleScene()->GetSelectMapObjs()[8]->GetState() == GameObject::Dead)
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();

			for (size_t i = 7; i < SceneManager::GetTitleScene()->GetSelectMapObjs().size(); i++)
			{
				if (i % 2 == 0)
					SceneManager::GetTitleScene()->GetSelectMapObjs()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetSelectMapObjs()[8]->Life();
			mousePos = {};
		}
		else if (mousePos.x >= 0.137f && mousePos.x <= 0.216f
			&& mousePos.y >= -0.342f && mousePos.y <= -0.246f && SceneManager::GetTitleScene()->GetSelectMapObjs()[10]->GetState() == GameObject::Dead)
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();

			for (size_t i = 7; i < SceneManager::GetTitleScene()->GetSelectMapObjs().size(); i++)
			{
				if (i % 2 == 0)
					SceneManager::GetTitleScene()->GetSelectMapObjs()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetSelectMapObjs()[10]->Life();
			mousePos = {};
		}
	}
	void TitleUIManager::SelectCharacter()
	{
		if (mousePos.x >= -0.887f && mousePos.x <= -0.787f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.887f && mousePos.x <= -0.787f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && SceneManager::GetTitleScene()->GetPlayerBubbles()[0]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(0);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[0]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPlayerBubbles()[0]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= -0.709f && mousePos.x <= -0.607f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.709f && mousePos.x <= -0.607f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && SceneManager::GetTitleScene()->GetPlayerBubbles()[1]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(1);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[1]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPlayerBubbles()[1]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= -0.532f && mousePos.x <= -0.428f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.532f && mousePos.x <= -0.428f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && SceneManager::GetTitleScene()->GetPlayerBubbles()[2]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(2);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[2]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetPlayerBubbles()[2]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= -0.353f && mousePos.x <= -0.25f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.353f && mousePos.x <= -0.25f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && SceneManager::GetTitleScene()->GetPlayerBubbles()[3]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(3);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[3]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetPlayerBubbles()[3]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= -0.174f && mousePos.x <= -0.07f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.174f && mousePos.x <= -0.07f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && SceneManager::GetTitleScene()->GetPlayerBubbles()[4]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(4);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[4]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetPlayerBubbles()[4]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= 0.003f && mousePos.x <= 0.107f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= 0.003f && mousePos.x <= 0.107f
			&& mousePos.y >= -0.277f && mousePos.y <= 0.1f && SceneManager::GetTitleScene()->GetPlayerBubbles()[5]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(5);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[5]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetPlayerBubbles()[5]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= -0.887f && mousePos.x <= -0.787f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.887f && mousePos.x <= -0.787f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f && SceneManager::GetTitleScene()->GetPlayerBubbles()[6]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(6);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[6]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetPlayerBubbles()[6]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= -0.709f && mousePos.x <= -0.607f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.709f && mousePos.x <= -0.607f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f && SceneManager::GetTitleScene()->GetPlayerBubbles()[7]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(7);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[7]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetPlayerBubbles()[7]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= -0.532f && mousePos.x <= -0.428f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.532f && mousePos.x <= -0.428f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f && SceneManager::GetTitleScene()->GetPlayerBubbles()[8]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(8);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[8]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetPlayerBubbles()[8]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= -0.353f && mousePos.x <= -0.25f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectMapOn();
			NextMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.353f && mousePos.x <= -0.25f
			&& mousePos.y >= -0.588f && mousePos.y <= -0.411f && SceneManager::GetTitleScene()->GetPlayerBubbles()[9]->GetComponent<Transform>()->GetScale() == Vector3(2.0f, 2.0f, 1.0f))
		{
			SceneManager::GetTitleScene()->ClickCharacter(9);
			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceObjects().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceObjects()[i]->Death();
			}
			SceneManager::GetTitleScene()->GetFaceObjects()[9]->Life();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetPlayerBubbles().size(); i++)
			{
				SceneManager::GetTitleScene()->GetPlayerBubbles()[i]->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			}

			SceneManager::GetTitleScene()->GetPlayerBubbles()[9]->GetComponent<Transform>()->SetScale(Vector3(2.2f, 2.2f, 1.0f));
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPanals()[4]->Death();
			SceneManager::GetTitleScene()->GetPanals()[2]->Death();
			mousePos = {};
		}
		else if (mousePos.x >= -0.907f && mousePos.x <= -0.217f
			&& mousePos.y >= -0.88f && mousePos.y <= -0.708f && Input::GetKeyDown(eKeyCode::LBTN))
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[1]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->SelectScreenUI();

			for (size_t i = 0; i < SceneManager::GetTitleScene()->GetFaceTexts().size(); i++)
			{
				SceneManager::GetTitleScene()->GetFaceTexts()[i]->Death();
			}
			BackMainUI();
			mousePos = {};
		}
		else if (mousePos.x >= -0.907f && mousePos.x <= -0.217f
			&& mousePos.y >= -0.88f && mousePos.y <= -0.708f && SceneManager::GetTitleScene()->GetPanals()[4]->GetState() == GameObject::Dead)
		{
			SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
			SceneManager::GetTitleScene()->GetPanals()[4]->Life();
			mousePos = {};
		}
		else if (mousePos.x >= -0.501f && mousePos.x <= -0.246f
			&& mousePos.y >= 0.857f && mousePos.y <= 0.96f && SceneManager::GetTitleScene()->GetPanals()[2]->GetState() == GameObject::Dead)
			{
				SceneManager::GetTitleScene()->GetSoundObjects()[0]->GetComponent<AudioSource>()->Play();
				SceneManager::GetTitleScene()->GetPanals()[2]->Life();
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
	void TitleUIManager::Reset()
	{
		mainNumber = 0;
		subNumber = 0;
	}
	void TitleUIManager::selectionScreenUI()
	{

	}
	void TitleUIManager::MainUI(UINT8 main, UINT8 sub)
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
			SelectMap();
			break;
		}
	}
}