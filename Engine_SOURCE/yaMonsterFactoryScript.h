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
		void BoomerSpawn(int remainder);
		void EyeMonsterSpawn(int remainder);
		void BossSpawn();
		Vector3 MonsterSpawnPos(Vector3 pos);
		void CurrentMonsterCntDec() { currentMonsterCnt--; }

		void Reset();
	private:
		float mTime;
		float mCurrentTime;

		Vector3 playerPos;
		int level;

		int maxMonsterCnt;
		int currentMonsterCnt;
		int spawnCnt;
	};
}