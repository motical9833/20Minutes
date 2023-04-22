#pragma once
#include "yaScript.h"

namespace ya
{
	//class PlayScene;
	class SkillManager : public Script
	{
		public:
			SkillManager();
			virtual ~SkillManager();

			virtual void Initalize();
			virtual void Update();
			virtual void FixedUpdate();
			virtual void Render();


			void ThunderEnchant(Vector3 Enchantobject);
			void GaleFire(Vector3 pos, Vector3 dir);
			void GhostFire(Vector3 pos, Vector3 dir);
			void SmiteFire(Vector3 pos);
			void HolyShield();

			void HolyShieldBreak();

	private:	
		bool bShieldOn;
		bool bShield;

		float shieldTime;
	};
}