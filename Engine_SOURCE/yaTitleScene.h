#pragma once
#include "yaScene.h"
#include "yaGameObject.h"
#include <array>

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

	private:
		std::vector<Transform*> objTr;
		float time;
		bool bLoadScene;
		GameObject* tSceneCamera;
	};
}
