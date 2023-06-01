#pragma once
#include "yaScript.h"


namespace ya
{
	class MonsterFactoryScript : public Script
	{
	public:
		MonsterFactoryScript();
		virtual ~MonsterFactoryScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void MonsterSpawn();
		Vector3 MonsterPos(Vector3 pos);
	private:
		float mTime;

		Vector3 playerPos;
		int level;

		int maxMonsterCnt;
		int currentMonsterCnt;
	};
}