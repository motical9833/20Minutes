#include "yaMonsterFactoryScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTime.h"
#include "yaMonsterScript.h"
#include "yaHubNigguratScript.h"
#include <random>>


#define _USE_MATH_DEFINES
#include <math.h>

namespace ya
{
	MonsterFactoryScript::MonsterFactoryScript()
		:mTime(0.0f)
		,mCurrentTime(0.0f)
		, bossDeadTime(0.0f)
		, spawnTime(1.5f)
		, level(0)
		, maxMonsterCnt(50)
		, currentMonsterCnt(0)
		, playerPos{}
		, spawnCnt(0)
		, gameTime(0.0f)
		, minute(0)
		, seconds(0)
		, tenSeconds(0)
		, bBossDead(false)
	{

	}
	MonsterFactoryScript::~MonsterFactoryScript()
	{

	}
	void MonsterFactoryScript::Initalize()
	{

	}
	void MonsterFactoryScript::Update()
	{
		if (SceneManager::GetPlayScene()->GetUIOn())
			return;

		if (bBossDead)
		{
			bossDeadTime += Time::DeltaTime();

			if (bossDeadTime >= 3.0f)
			{
				SceneManager::GetPlayScene()->SurvivalEndUIOn();
			}
			return;
		}

		gameTime += Time::DeltaTime();

		if (gameTime >= 1.0f)
		{
			if (minute > 9)
			{
				int a = 0;
			}


			if (seconds >= 9)
			{
				SceneManager::GetPlayScene()->GetTimerObjects()[seconds]->Death();
				seconds = 0;
				SceneManager::GetPlayScene()->GetTimerObjects()[seconds]->Life();


				if (tenSeconds >= 5)
				{
					SceneManager::GetPlayScene()->GetTimerObjects()[10 + tenSeconds]->Death();
					tenSeconds = 0;
					SceneManager::GetPlayScene()->GetTimerObjects()[10 + tenSeconds]->Life();

					SceneManager::GetPlayScene()->GetTimerObjects()[20 + minute]->Death();
					minute++;
					SceneManager::GetPlayScene()->GetTimerObjects()[20 + minute]->Life();
				}
				else
				{
					SceneManager::GetPlayScene()->GetTimerObjects()[10 + tenSeconds]->Death();
					tenSeconds++;
					SceneManager::GetPlayScene()->GetTimerObjects()[10 + tenSeconds]->Life();
				}
			}
			else
			{
				SceneManager::GetPlayScene()->GetTimerObjects()[seconds]->Death();
				seconds++;
				SceneManager::GetPlayScene()->GetTimerObjects()[seconds]->Life();
			}

			gameTime = 0;
		}




		if (SceneManager::GetPlayScene()->GetUIOn())
			return;

		if (currentMonsterCnt > maxMonsterCnt)
			return;

		mTime += Time::DeltaTime();
		mCurrentTime += Time::DeltaTime();
		if (mTime >= spawnTime)
		{
			playerPos = SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
			MonsterSpawn();
			mTime = 0;
		}

		if (mCurrentTime >=60.0f)
		{
			level++;

			if (spawnTime >= 0.5f)
				spawnTime -= 0.25f;

			mCurrentTime = 0.0f;
			if (level == 5)
			{
				BossSpawn();
			}
		}
	}

;	void MonsterFactoryScript::FixedUpdate()
	{

	}
	void MonsterFactoryScript::Render()
	{

	}
	void MonsterFactoryScript::MonsterSpawn()
	{
		spawnCnt++;
		std::vector<Monster*> brainMonster = SceneManager::GetPlayScene()->GetBrainMonsters();

		for (size_t i = 0; i < brainMonster.size(); i++)
		{
			if (brainMonster[i]->IsDead() == false)
				continue;

			brainMonster[i]->GetScript<MonsterScript>()->Respawn();
			brainMonster[i]->GetComponent<Transform>()->SetPosition(MonsterSpawnPos(playerPos));
			currentMonsterCnt++;
			break;
		}

		switch (level)
		{
		case 1:
			BoomerSpawn(4);
			break;
		case 2:
			BoomerSpawn(4);
			EyeMonsterSpawn(3);
			break;
		case 3:
			BoomerSpawn(4);
			EyeMonsterSpawn(2);
			break;
		case 4:
			BoomerSpawn(4);
			EyeMonsterSpawn(2);
			break;
		case 5:
			BoomerSpawn(3);
			EyeMonsterSpawn(2);
			break;
		}
	}
	void MonsterFactoryScript::BoomerSpawn(int remainder)
	{
		if (spawnCnt % remainder == 0)
		{
			std::vector<Monster*> boomerMonster = SceneManager::GetPlayScene()->GetBoomerMonsters();

			for (size_t i = 0; i < boomerMonster.size(); i++)
			{
				if (boomerMonster[i]->IsDead() == false)
					continue;

				boomerMonster[i]->GetScript<MonsterScript>()->Respawn();
				boomerMonster[i]->GetComponent<Transform>()->SetPosition(MonsterSpawnPos(playerPos));
				currentMonsterCnt++;
				break;
			}
		}
	}
	void MonsterFactoryScript::EyeMonsterSpawn(int remainder)
	{
		if (spawnCnt % remainder == 0)
		{
			std::vector<Monster*> eyeMonster = SceneManager::GetPlayScene()->GetEyeMonsters();

			for (size_t i = 0; i < eyeMonster.size(); i++)
			{
				if (eyeMonster[i]->IsDead() == false)
					continue;

				eyeMonster[i]->GetScript<MonsterScript>()->Respawn();
				eyeMonster[i]->GetComponent<Transform>()->SetPosition(MonsterSpawnPos(playerPos));
				currentMonsterCnt++;
				break;
			}
		}
	}
	void MonsterFactoryScript::BossSpawn()
	{
		std::vector<Monster*> boss = SceneManager::GetPlayScene()->GetBossMonsters();

		if (boss[0]->GetState() == 0)
		{
			return;
		}

		boss[0]->GetScript<HubNigguratScript>()->Respawn();
		boss[0]->GetComponent<Transform>()->SetPosition(MonsterSpawnPos(playerPos));
	}
	Vector3 MonsterFactoryScript::MonsterSpawnPos(Vector3 pos)
	{
		double x = 0;
		double y = 0;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(0, 2 * M_PI);

		double theta = dis(gen);

		x = pos.x + 15 * cosf(theta);
		y = pos.y + 15 * sinf(theta);


		return Vector3(x,y,0.0f);
	}
	void MonsterFactoryScript::GameReset()
	{
		mTime = 0.0f;
		mCurrentTime = 0.0f;
		level = 0;
		maxMonsterCnt = 50;
		currentMonsterCnt = 0;
		spawnCnt = 0;
		gameTime = 0.0f;
		minute = 0;
		seconds = 0;
		tenSeconds = 0;
		bBossDead = false;
		bossDeadTime = 0.0f;
	}
}