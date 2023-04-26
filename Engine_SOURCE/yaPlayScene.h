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
		std::vector<GameObject*> GetGale() { return gales; }
		std::vector<Bullet*> GetGhostBullets() { return ghostBullets; }
		std::vector<Bullet*> GetDragonFires() { return dragonFires; }
		std::vector<GameObject*> GetSmites() { return smites; }
		std::vector<GameObject*> Getspears() { return spears; }
		std::vector<GameObject*> GetHpObjects() { return hpObjects; }

		std::vector<Monster*> GetBrainMonsters() { return mBrainMonsters; }
		std::vector<Monster*> GetTreeMonsters() { return mTreeMonsters; }
		std::vector<Monster*> GetEyeMonsters() { return mEyeMonsters; }
		std::vector<Monster*> GetBoomerMonsters() { return mBoomerMonsters; }

		GameObject* GetShield() { return holyShield; }
		GameObject* GetColliderChack() { return colliderCheck; }
		GameObject* GetDragonPet() { return dragonPet; }
		GameObject* GetUpgradeobj() { return upgradeobj; }

		void CreateBrainMonster();
		void CreateTreeMonster();
		void CreateEyeMonster();
		void CreateBommerMonster();

		void CreateCollider(auto* monster, eColliderType type,Vector2 size);
		void CreateDeathFX();
		void CreateSpriteRenderer(auto* object, const std::wstring& materialKey);
		GameObject* CreateSkillObject(eColliderType type, eLayerType layertype, const std::wstring& materialKey);
		GameObject* CreateSkillObject(eLayerType layertype, const std::wstring& materialKey);
		void M_DefaultTr(auto* object, Vector3 pos, Vector3 scale);

		GameObject* GetSkillManager() { return skillManager; };

	private:
		Player* player;
		GameObject* pSceneCamera;
		GameObject* skillManager;
		GameObject* pulseObject;
		Weapon* pWeapon;
		std::vector<GameObject*> hpObjects;
		std::vector<Bullet*> bullets;
		std::vector<GameObject*> thunders;
		std::vector<GameObject*> gales;
		std::vector<GameObject*> freezes;
		std::vector<GameObject*> curses;
		std::vector<GameObject*> smites;
		std::vector<GameObject*> spears;

		GameObject* holyShield;
		GameObject* magicLens;
		GameObject* dragonPet;
		GameObject* ghostPet;
		GameObject* scythe;

		GameObject* colliderCheck;
		GameObject* upgradeobj;


		std::vector<Bullet*> ghostBullets;
		std::vector<Bullet*> dragonFires;
		Bullet* bullet;

		std::vector<Monster*> mBrainMonsters;		
		std::vector<Monster*> mTreeMonsters;
		std::vector<Monster*> mEyeMonsters;
		std::vector<Monster*> mBoomerMonsters;

		//std::vector<GameObject*> firePos;
		std::vector<GameObject*> hpUiObj;
	};
}