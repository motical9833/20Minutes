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
			void SmiteFire(Vector3 pos);
			void HolyShield();
			void DragonFIre(Vector3 pos, Vector3 dir);

			void HolyShieldBreak();
			void Spear();
			void IceShard(Vector3 pos, Vector3 dir);

			void SetJusticeOn() { bJustice = true; }
			void SetAngelicOn() { bAngelic = true; }

			void SmiteKillCnt();

			void GameReset();
	private:	
		bool bShieldOn;
		bool bShield;
		bool bJustice;
		bool bAngelic;

		float shieldTime;

		int smiteKillStack;
		int justiceCnt;
	};
}