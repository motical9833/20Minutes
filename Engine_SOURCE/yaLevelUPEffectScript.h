#pragma once
#include "yaScript.h"

namespace ya
{
	class LevelUPEffectScript : public Script
	{
	public:
		LevelUPEffectScript();
		~LevelUPEffectScript();

		virtual void Initalize() override;

		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void Start();
		void Action();
		void End();
		void Reset();

		void LevelUPEffect();

	private:
	};
}