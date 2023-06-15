#include "yaMonsterFactoryScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTime.h"
#include "yaMonsterScript.h"
#include <random>>

#define _USE_MATH_DEFINES
#include <math.h>

namespace ya
{
	MonsterFactoryScript::MonsterFactoryScript()
		:mTime(0.0f)
		, level(0)
		, maxMonsterCnt(50)
		, currentMonsterCnt(0)
		, playerPos{}
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

		if (currentMonsterCnt > maxMonsterCnt)
			return;

		mTime += Time::DeltaTime();

		if (mTime >= 0.5f)
		{
			playerPos = SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
			MonsterSpawn();
			mTime = 0;
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
		std::vector<Monster*> brainMonster = SceneManager::GetPlayScene()->GetBrainMonsters();

		for (size_t i = 0; i < brainMonster.size(); i++)
		{
			if (brainMonster[i]->IsDead() == false)
				continue;

			brainMonster[i]->GetScript<MonsterScript>()->Respawn();
			brainMonster[i]->GetComponent<Transform>()->SetPosition(MonsterPos(playerPos));
			currentMonsterCnt++;
			break;
		}
	}
	Vector3 MonsterFactoryScript::MonsterPos(Vector3 pos)
	{

		double x = 0;
		double y = 0;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(0, 2 * M_PI);

		double theta = dis(gen);

		x = pos.x + 10 * cosf(theta);
		y = pos.y + 10 * sinf(theta);


		return Vector3(x,y,0.0f);
	}
}