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

	private:	
		//PlayScene* pscene;
	};
}