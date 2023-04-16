#pragma once
#include "yaScript.h"

namespace ya
{
	class SkillManager : public Script
	{
		public:
			SkillManager();
			virtual ~SkillManager();

			virtual void Initalize();
			virtual void Update();
			virtual void FixedUpdate();
			virtual void Render();

	private:

	};
}