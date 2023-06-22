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
		GameObject* GetPlaySceneCamera() { return pSceneCamera; }
		void ChoosePlayers(int num);
		Weapon* GetWeapon() { return pWeapon; }
		Scene* GetScene() { return this; }
		std::vector<Bullet*> GetBullet() { return bullets; }
		std::vector<GameObject*> GetThunders() { return thunders; }
		std::vector<GameObject*> GetThundersEffect() { return thundersEffect; }
		std::vector<GameObject*> GetGale() { return gales; }
		std::vector<Bullet*> GetGhostBullets() { return ghostBullets; }
		std::vector<Bullet*> GetDragonFires() { return dragonFires; }
		std::vector<GameObject*> GetSmites() { return smites; }
		std::vector<GameObject*> Getspears() { return spears; }
		std::vector<GameObject*> GetHpObjects() { return hpObjects; }
		std::vector<GameObject*> GetIcicles() { return icicles; }
		std::vector<GameObject*> GetIcicleSounds() { return icicleSounds; }
		std::vector<GameObject*> GetCurses() { return curses; }
		std::vector<GameObject*> GetExpMarble() { return expMarbles; }
		GameObject* GetGhostPet() { return ghostPet; }
		GameObject* GetGhostPetRotObj() { return ghostPetRotobject; }
		GameObject* GetMagicLens() { return magicLens; }
		GameObject* GetExpGauge() { return expGauge; }
		GameObject* GetBulletFireLight() { return bulletFireLight; }

		std::vector<Monster*> GetBrainMonsters() { return mBrainMonsters; }
		std::vector<Monster*> GetTreeMonsters() { return mTreeMonsters; }
		std::vector<Monster*> GetEyeMonsters() { return mEyeMonsters; }
		std::vector<Monster*> GetBoomerMonsters() { return mBoomerMonsters; }
		std::vector<Monster*> GetBossMonsters() { return mBossMonsters; }
		std::vector<Monster*> getBigBoomerMonsters() { return mBigBoomerMonsters; }
		std::vector<GameObject*> GetBoomerExplosions() { return boomersExplosions; }
		std::vector<GameObject*> GetBoomerSound() { return boomersSounds; }
		std::vector<GameObject*> GetTimerObjects() { return timerObj; }
		std::vector<GameObject*> GetLevelTexts() { return levelTexts; }
		std::vector<GameObject*> GetBulletUITexts() { return bulletTexts; }
		std::vector<GameObject*> GetExitUIs() { return exitUIs; }

		void ThunderBugOn() { for (size_t i = 0; i < thunderBugs.size(); i++) { thunderBugs[i]->Life(); } }


		GameObject* GetShield() { return holyShield; }
		GameObject* GetColliderChack() { return colliderCheck; }
		GameObject* GetDragonPet() { return dragonPet; }
		GameObject* GetUpgradeobj() { return upgradeobj; }
		GameObject* GetScythe() { return scythe; }
		GameObject* GetLevelUPEffect() { return levelUPEffectObj; }
		GameObject* GetLevelManager() { return levelManager; }
		GameObject* GetMuzzleFlash() { return muzzleFlash; }
		GameObject* GetSoundObjects(int number) { return soundObj[number]; }
		GameObject* GetMonsterFactory() { return monsterFactoryManager; }
		bool GetUIOn() { return uiOn; }
		bool GetBoolUIOns(int number) { return uiOns[number]; }

		std::vector<GameObject*> GetIcon() { return iconObjects; }
		std::vector<GameObject*> GetIcons() { return icons; }
		std::vector<GameObject*> GetIconsTexts() { return iconTexts; }
		std::vector<GameObject*> GetUIframe() { return uiFrames; }
		std::vector<GameObject*> GetReloadUI() { return reloadUI; }

		void SetReroll(bool bValue) { bReroll = bValue; }

		void CreatePlayer();
		void CreateWeapon();
		void CreateFirePos();
		void CreateBrainMonster();
		void CreateBrainEyeEffect();
		void CreateTreeMonster(Vector3 pos);
		void CreateEyeMonster();
		void CreateEyeMonsterEffect();
		void CreateBommerMonster();
		void CreateBommerEyeEffect();
		void CreateBossMonster();
		void CreateBossEffect();

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
		void CreateFreezes();
		void CreateCurses();


		void CreateHpUIobj();
		void CreateAbilityIcon(GameObject* parent);
		void CreateLevelUpEffect();
		void CreateUIPanal(/*GameObject* parent*/Vector3 pos, Vector3 scale);
		void CreateUIObject(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreateUIObject(const std::wstring& key, std::vector<GameObject*>& array, Vector3 pos, Vector3 scale);
		void CreatePowerUpFrame(/*GameObject* parent, */Vector3 pos, Vector3 scale);
		void CreateSkillUI(GameObject* parent);
		void CreateSkillIcon(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreatetimerObject(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreateLevelUI(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreateLevelText(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreateBulletText(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreateIconText(const std::wstring& key, Vector3 pos, Vector3 scale);
		void CreateExpBar(GameObject* parent);
		void CreateCollider(auto* monster, eColliderType type,Vector2 size);
		void CreateDeathFX();
		void CreateAmmoIcon(GameObject* parent);
		void CreateSpriteRenderer(auto* object, const std::wstring& materialKey);
		void CreateSoundobject(const std::wstring& key);
		GameObject* CreateSkillObject(eColliderType type, eLayerType layertype, const std::wstring& materialKey);
		GameObject* CreateSkillObject(eLayerType layertype, const std::wstring& materialKey);
		void CreateExitUI();
		void CreateEndUI();
		void M_DefaultTr(auto* object, Vector3 pos, Vector3 scale);

		void FreezeAddToMonster();
		void CurseAddToMonster();
		GameObject* GetSkillManager() { return skillManager; };

		void ALLSKILL();

		glm::vec2 ScreenToCamera(const glm::vec2& screenCoord, const glm::mat4& viewProjectionMatrix, int screenWidth, int screenHeight);

		void LevelUPUI();
		void UiButton(Vector3 pos);
		void EscUIButton(Vector3 pos);
		void EscUIOn();
		void EscUIClick(int number);
		void EscUIMousePoint(int number);
		void AbilityUIClick(int number);
		void AbilityUIMousePoint(int number);
		void AbilityTreeClick(int ablityNum, int treeNum);
		void AbilityTreeClickReset();
		void EndUIButton(Vector3 pos);
		void EndUIClick(int number);
		void EndUIMousePoint(int number);
		void SurvivalEndUIOn();
		void DeadEndUIOn();
		void SelectAbility();

		Vector3 UiMousePos();

		void CreateStageOneTile(Vector3 pos);
		void ReturnTitleScene();
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
		std::vector<GameObject*> thundersEffect;
		std::vector<GameObject*> gales;
		std::vector<GameObject*> freezes;
		std::vector<GameObject*> curses;
		std::vector<GameObject*> smites;
		std::vector<GameObject*> spears;
		std::vector<GameObject*> thunderBugs;
		std::vector<GameObject*> icicles;
		std::vector<GameObject*> icicleSounds;
		std::vector<GameObject*> expMarbles;
		std::vector<GameObject*> uiObjects;
		std::vector<GameObject*> uiFrames;
		std::vector<GameObject*> iconObjects;
		std::vector<GameObject*> icons;
		std::vector<GameObject*> iconTexts;
		std::vector<GameObject*> reloadUI;
		std::vector<GameObject*> soundObj;
		std::vector<GameObject*> timerObj;
		std::vector<GameObject*> levelTexts;
		std::vector<GameObject*> bulletTexts;
		std::vector<GameObject*> exitUIs;
		std::vector<GameObject*> endUIs;

		GameObject* holyShield;
		GameObject* magicLens;
		GameObject* dragonPet;
		GameObject* ghostPet;
		GameObject* ghostPetRotobject;
		GameObject* scythe;
		GameObject* colliderCheck;
		GameObject* upgradeobj;
		GameObject* monsterFactoryManager;
		GameObject* playerPointLight;
		GameObject* playerSubPointLight;
		GameObject* directionalLight;
		GameObject* bulletFireLight;
		GameObject* expGauge;

		std::vector<Bullet*> ghostBullets;
		std::vector<Bullet*> dragonFires;
		Bullet* bullet;

		std::vector<Monster*> mBrainMonsters;	
		std::vector<GameObject*> mBrainMonsterEyes;
		std::vector<Monster*> mTreeMonsters;
		std::vector<Monster*> mEyeMonsters;
		std::vector<GameObject*> mEyeMonsterEyes;
		std::vector<Monster*> mBoomerMonsters;
		std::vector<GameObject*> mBoomerMonsterEyes;
		std::vector<Monster*> mBigBoomerMonsters;
		std::vector<GameObject*> boomersExplosions;
		std::vector<GameObject*> boomersSounds;
		std::vector<Monster*> mBossMonsters;
		std::vector<GameObject*> mBossMonsterEffects;

		std::vector<GameObject*> hpUiObj;

		int randomValue[5];
		__int8 abliltyNumber;

		int click[5][2];
		bool uiOn;
		bool uiOns[3];
		bool bReroll;
	};
}