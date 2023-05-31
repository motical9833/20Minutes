#pragma once
#include "yaScene.h"
#include "yaPlayer.h"
#include "yaWeapon.h"
#include "yaBullet.h"
#include "yaMonster.h"

#include <iostream>
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

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
		void ChoosePlayers(int num);
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
		std::vector<GameObject*> GetIcicles() { return icicles; }
		std::vector<GameObject*> GetCurses() { return curses; }
		std::vector<GameObject*> GetExpMarble() { return expMarbles; }
		GameObject* GetGhostPet() { return ghostPet; }
		GameObject* GetGhostPetRotObj() { return ghostPetRotobject; }
		GameObject* GetMagicLens() { return magicLens; }

		std::vector<Monster*> GetBrainMonsters() { return mBrainMonsters; }
		std::vector<Monster*> GetTreeMonsters() { return mTreeMonsters; }
		std::vector<Monster*> GetEyeMonsters() { return mEyeMonsters; }
		std::vector<Monster*> GetBoomerMonsters() { return mBoomerMonsters; }

		void ThunderBugOn() { for (size_t i = 0; i < thunderBugs.size(); i++) { thunderBugs[i]->Life(); } }


		GameObject* GetShield() { return holyShield; }
		GameObject* GetColliderChack() { return colliderCheck; }
		GameObject* GetDragonPet() { return dragonPet; }
		GameObject* GetUpgradeobj() { return upgradeobj; }
		GameObject* GetScythe() { return scythe; }
		GameObject* GetLevelUPEffect() { return levelUPEffectObj; }
		GameObject* GetLevelManager() { return levelManager; }
		GameObject* GetMuzzleFlash() { return muzzleFlash; }
		bool GetUIOn() { return uiOn; }

		std::vector<GameObject*> GetIcon() { return iconObjects; }
		std::vector<GameObject*> GetIcons() { return icons; }
		std::vector<GameObject*> GetUIframe() { return uiFrames; }
		std::vector<GameObject*> GetReloadUI() { return reloadUI; }
		void CreatePlayer();
		void CreateWeapon();
		void CreateFirePos();
		void CreateBrainMonster();
		void CreateTreeMonster();
		void CreateEyeMonster();
		void CreateBommerMonster();
		void CreateDragonPet();
		void CreateDragonPetBullet();
		void CreateGhostPet();
		void CreateGhostPetBullet();
		void CreateSmite();
		void CreateMagicLens();
		void CreateHolyShiled();
		void CreateThunder();
		void CreateGale();
		void CreateScythe();
		void CreateColliderChackObj();
		void CreateSpear();
		void CreateThunderBug();
		void CreateIcicle();
		void CreateExpMarble();
		void CreateGameManagers();

		void CreateHpUIobj(GameObject* parent);
		void CreateAbilityIcon(GameObject* parent);
		void CreateLevelUpEffect();
		void CreateUIPanal(GameObject* parent, Vector3 pos, Vector3 scale);
		void CreateUILeader(const std::wstring& key,GameObject* parent, Vector3 pos, Vector3 scale);
		void CreatePowerUpFrame(GameObject* parent, Vector3 pos, Vector3 scale);
		void CreateSkillUI(GameObject* parent);
		void CreateSkillIcon(const std::wstring& key, GameObject* parent, Vector3 pos, Vector3 scale);
		void CreateExpBar(GameObject* parent);
		void CreateCollider(auto* monster, eColliderType type,Vector2 size);
		void CreateDeathFX();
		void CreateAmmoIcon(GameObject* parent);
		void CreateSpriteRenderer(auto* object, const std::wstring& materialKey);
		GameObject* CreateSkillObject(eColliderType type, eLayerType layertype, const std::wstring& materialKey);
		GameObject* CreateSkillObject(eLayerType layertype, const std::wstring& materialKey);
		void M_DefaultTr(auto* object, Vector3 pos, Vector3 scale);

		GameObject* GetSkillManager() { return skillManager; };

		void ALLSKILL();

		glm::vec2 ScreenToCamera(const glm::vec2& screenCoord, const glm::mat4& viewProjectionMatrix, int screenWidth, int screenHeight);

		void LevelUPUI();
		void UiButton(Vector3 pos);
		void AbilityUIClick(int number);
		void AbilityTreeClick(int ablityNum, int treeNum);
		void AbilityTreeClickReset();
		void SelectAbility();

		Vector3 UiMousePos();

		void CreateStageOneTile(Vector3 pos);

	private:
		Player* player;
		std::vector<Player*> players;
		GameObject* levelUPEffectObj;
		GameObject* levelManager;
		GameObject* pSceneCamera;
		GameObject* skillManager;
		GameObject* stageOneMapManager;
		GameObject* pulseObject;
		GameObject* muzzleFlash;
		Weapon* pWeapon;
		std::vector<GameObject*> hpObjects;
		std::vector<Bullet*> bullets;
		std::vector<GameObject*> thunders;
		std::vector<GameObject*> gales;
		std::vector<GameObject*> freezes;
		std::vector<GameObject*> curses;
		std::vector<GameObject*> smites;
		std::vector<GameObject*> spears;
		std::vector<GameObject*> thunderBugs;
		std::vector<GameObject*> icicles;
		std::vector<GameObject*> expMarbles;
		std::vector<GameObject*> uiObjects;
		std::vector<GameObject*> uiFrames;
		std::vector<GameObject*> iconObjects;
		std::vector<GameObject*> icons;
		std::vector<GameObject*> reloadUI;

		GameObject* holyShield;
		GameObject* magicLens;
		GameObject* dragonPet;
		GameObject* ghostPet;
		GameObject* ghostPetRotobject;
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

		std::vector<GameObject*> hpUiObj;

		int randomValue[5];
		__int8 abliltyNumber;

		int click[5][2];
		bool uiOn;
	};
}