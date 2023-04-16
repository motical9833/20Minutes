#pragma once
#include "yaScene.h"
#include "yaPlayer.h"
#include "yaWeapon.h"
#include "yaBullet.h"
#include "yaMonster.h"

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

		Player* GetPlayer() { return player; }
		Weapon* GetWeapon() { return pWeapon; }
		Scene* GetScene() { return this; }
		std::vector<Bullet*> GetBullet() { return bullets; }
		std::vector<GameObject*> GetThunders() { return thunders; }


		void CreateBrainMonster();
		void CreateTreeMonster();
		void CreateEyeMonster();
		void CreateBommerMonster();

		void CreateCollider(auto* monster, eColliderType type,Vector2 size);
		void CreateDeathFX();
		void CreateSpriteRenderer(auto* object, const std::wstring& materialKey);
		void CreateAnimator(auto* object);

		void M_DefaultTr(auto* object, Vector3 pos, Vector3 scale);

	private:
		Player* player;
		GameObject* pSceneCamera;
		Weapon* pWeapon;
		std::vector<Bullet*> bullets;
		std::vector<GameObject*> thunders;
		Bullet* bullet;

		std::vector<Monster*> mBrainMonsters;		
		std::vector<Monster*> mTreeMonsters;
		std::vector<Monster*> mEyeMonsters;
		std::vector<Monster*> mBoomerMonsters;

		//std::vector<GameObject*> firePos;
		std::vector<GameObject*> hpUiObj;
	};
}