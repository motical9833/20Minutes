#pragma once
#include "yaScript.h"

namespace ya
{
	//class PlayScene;
	class SkillManager : public Script
	{
		public:
			SkillManager();
			~SkillManager();

			virtual void Initalize();
			virtual void Update();
			virtual void FixedUpdate();
			virtual void Render();


			void ThunderEnchant(Vector3 Enchantobject);
			void GaleFire(Vector3 pos, Vector3 dir);
			void GhostFire(Vector3 pos, Vector3 dir);
			void GhostFireToMouse(Vector3 pos, Vector3 rot);
			void SmiteFire(Vector3 pos);
			void HolyShield();
			void DivinWrath();
			void DragonFIre(Vector3 pos, Vector3 dir);
			void AgedDragon();
			void TrainedDragon();
			void DragonBond();

			void HolyShieldBreak();
			void Spear();
			void IceShard(Vector3 pos, Vector3 dir);
			void VengefulGhostFire(Vector3 pos, Vector3 dir);

			void SetJusticeOn() { bJustice = true; }
			void SetAngelicOn() { bAngelic = true; }
			void SetHolyShieldOn() { bShieldOn = true; }
			void SetDivineBlessingOn() { bDivineBlessing = true; }
			void SetIntheWindOn() { bIntheWind = true; }
			void SetAgedDragonOn() { bAgedDragon = true; }
			void SetTrainedDragon() { bTrainedDragon = true; }
			void SetShieldOnTime(int value) { shieldOnTime = value; }
			int GetIntheWindStack() { return intheWindStack; }
			void SmiteKillCnt();
			void IntheWind();
			void IntheWindReset();

			void GameReset();
	private:	
		bool bShieldOn;
		bool bShield;
		bool bJustice;
		bool bAngelic;
		bool bDivineBlessing;
		bool bIntheWind;
		bool bAgedDragon;
		bool bTrainedDragon;

		float shieldTime;
		float intheWindTime;
		float AgedDragonTime;
		float trainedDragonTime;

		int smiteKillStack;
		int justiceCnt;
		int shieldOnTime;
		int intheWindStack;
		int trainedDragonStack;
	};
}