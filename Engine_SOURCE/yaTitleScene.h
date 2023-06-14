#pragma once
#include "yaScene.h"
#include "yaGameObject.h"
#include <array>

#include <iostream>
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "yaFmod.h"

namespace ya
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void CreateCamera();
		void CreateLeavs();
		void CreateLogo();
		void CreateBg();
		void CreateBgEye();

		void CreateUIManager();
		void CreateTitleUI();
		void CreateSelectPanal();
		void CreatePlayerFace(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreatePlayerFaceText(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreateFaceImg();
		void CreateFaceTextImg();
		void CreateWeaponUI(const std::wstring& key, GameObject* parent, Vector3 pos);
		void CreateWeaponImg();
		void CreateBubble(std::vector<GameObject*>& keepArray, Vector3 pos);
		void CreateBubble(std::vector<GameObject*>& keepArray,GameObject* parent, Vector3 pos);
		void CreateBubbleUI();
		void CreateLock(GameObject* parent,Vector3 pos);
		void CreateLockObjet();
		void CreateCharacterImg(const std::wstring& key, Vector3 pos);
		void CreateSelectCharacter();
		void CreatePanal();
		void CreateUIPanal(Vector3 pos);
		void CreateUIPanal(const std::wstring& key, Vector3 pos,Vector3 scale);
		GameObject* CreateUIPanal(const std::wstring& key, Vector3 pos);
		void CreateUIPanal(const std::wstring& key, GameObject* parent, Vector3 pos);
		void CreateUIPanal(const std::wstring& key, GameObject* parent, Vector3 pos,Vector3 scale);
		GameObject* CreateUIPanal(const std::wstring& key, eLayerType type, GameObject* parent, Vector3 pos, Vector3 scale);
		void CreateBubblePanal();
		void CreateSelectMapObject();
		void TemporaryPanal();

		void SelectMapOn();
		void SelectMapOff();
		void UIReset();
		void FirstUI();
		void StartUI();
		void WeaponSelectUI();
		void CharacterSelectUI();
		void ClickCharacter(int num);
		void ClickWeapon(int num);
		void SelectScreenUI();
		Vector3 UIMousePos();
		glm::vec2 ScreenToCamera(const glm::vec2 & screenCoord, const glm::mat4 & viewProjectionMatrix, int screenWidth, int screenHeight);

		std::vector<GameObject*> GetMainUIbutterns() { return mainUIbutterns; }
		std::vector<GameObject*> GetSoundObjects() { return soundObj; }
		std::vector<GameObject*> GetFaceObjects() { return faceObjs; }
		std::vector<GameObject*> GetPlayerBubbles() { return playerBubbles; }
		std::vector<GameObject*> GetFaceTexts() { return faceTextObjes; }
		std::vector<GameObject*> GetSelectMapObjs() { return selectMapObjs; }
		std::vector<GameObject*> GetPanals() { return panals; }
		//void TitleAudioClip();

		void Start(int num);
		void Start();
	private:
		std::vector<GameObject*> leves;
		std::vector<GameObject*> selectPanals;
		std::vector<GameObject*> faceObjs;
		std::vector<GameObject*> faceTextObjes;
		std::vector<GameObject*> weaponBubbles;
		std::vector<GameObject*> lockObjs;
		std::vector<GameObject*> playerBubbles;
		std::vector<GameObject*> uiPanals;
		std::vector<GameObject*> uiPlayers;;
		std::vector<GameObject*> bubbleParents;
		std::vector<GameObject*> mainUIbutterns;
		std::vector<GameObject*> soundObj;
		std::vector<GameObject*> playerTexts;
		std::vector<GameObject*> selectMapObjs;
		std::vector<GameObject*> panals;

		float time;
		bool bLoadScene;

		GameObject* tSceneCamera;
		GameObject* tUICamera;
		GameObject* logo;
		GameObject* bgEye;
		GameObject* uiManager;
		GameObject* faceParent;

		int selectCharNum;
		int selectWeaponNum;
	};
}
