#pragma once
#include "yaScene.h"
#include "yaPlayer.h"
#include "yaWeapon.h"

namespace ya
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


	private:
		Player* player;
		GameObject* pSceneCamera;
		Weapon* pWeapon;
	};
}