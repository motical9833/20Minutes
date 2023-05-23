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

		glm::vec2 ScreenToCamera(const glm::vec2 & screenCoord, const glm::mat4 & viewProjectionMatrix, int screenWidth, int screenHeight);

	private:
		std::vector<Transform*> objTr;
		float time;
		bool bLoadScene;
		GameObject* tSceneCamera;
	};
}
