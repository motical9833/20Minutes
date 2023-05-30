#pragma once
#include "yaScene.h"
#include "yaGameObject.h"
#include <array>

#include <iostream>
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"


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

		void CreateSelectPanal();
		void CreatePlayerFace(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreateFaceImg();
		void CreateBubble(std::vector<GameObject*>& keepArray, Vector3 pos);
		void CreateBubbleUI();
		void CreateLock(Vector3 pos);
		void CreateLockObjet();
		void CreateCharacterImg(const std::wstring& key, Vector3 pos);
		void CreateSelectCharacter();
		void CreatePanal();
		void CreateUIPanal(const std::wstring& key, GameObject* parent, Vector3 pos);
		void CreateUIPanal(const std::wstring& key, GameObject* parent, Vector3 pos,Vector3 scale);

		void FirstUI();
		void StartUI();
		void SelectScreenUI();

		glm::vec2 ScreenToCamera(const glm::vec2 & screenCoord, const glm::mat4 & viewProjectionMatrix, int screenWidth, int screenHeight);

		void Start(int num);
	private:
		std::vector<GameObject*> leves;
		std::vector<GameObject*> selectPanals;
		std::vector<GameObject*> faceObjs;
		std::vector<GameObject*> weaponBubbles;
		std::vector<GameObject*> lockObjs;
		std::vector<GameObject*> playerBubbles;
		std::vector<GameObject*> uiPanals;
		std::vector<GameObject*> uiPlayers;;
		std::vector<GameObject*> bubbleParents;
		float time;
		bool bLoadScene;

		GameObject* tSceneCamera;
		GameObject* logo;
		GameObject* bgEye;
	};
}
