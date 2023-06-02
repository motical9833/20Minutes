#include "yaMonsterFactoryScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTime.h"
#include "yaMonsterScript.h"
#include <random>


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
		std::random_device rd;
		std::mt19937 rng(rd());

		int minX = -10;
		int maxX = 10;
		int minY = -10;
		int maxY = 10;

		std::uniform_int_distribution<int> uniX(minX, maxX);
		std::uniform_int_distribution<int> uniY(minY, maxY);

		int randomX = uniX(rng);
		int randomY = uniY(rng);


		pos.x += randomX;
		pos.y += randomY;

		if (randomX == 0)	
		{
			pos.x += 8;
		}
		else if (-3 < randomX < 3)
		{
			pos.x += randomX * 3;
		}
		else if (6 < randomX > 3 || -6 > randomX < -3)
		{
			pos.x += randomX * 2;
		}

		if (randomY == 0)
		{
			pos.y += 8;
		}
		else if (-2 < randomY < 2)
		{
			pos.y += randomY * 3;
		}
		else if (5 < randomY > 2 || -5 > randomY < -2)
		{
			pos.y += randomY * 2;
		}

		return pos;
	}
}