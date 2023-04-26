#include "yaUpgradeScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaBulletScript.h"
#include "yaWeaponScript.h"
#include "yaMonsterScript.h"

namespace ya
{
	UpgradeScript::UpgradeScript()
		: pscene{}
		, bupgrade{}
	{

	}
	UpgradeScript::~UpgradeScript()
	{

	}
	void UpgradeScript::Initalize()
	{
		pscene = SceneManager::GetPlayScene();
		//bupgrade[4][3] = true;
	}
	void UpgradeScript::Update()
	{

	}
	void UpgradeScript::FixedUpdate()
	{

	}
	void UpgradeScript::Render()
	{

	}
	//T1 탄환속도 30% 산탄 범위 -15%
	void UpgradeScript::TakeAim()
	{
		if (bupgrade[0][0])
			return;

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetSpeedMul(0.3f);
		}
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireRotRed(-0.15f);
		bupgrade[0][0] = true;
	}
	//T2 //탄환 속도 15% 관통+1
	void UpgradeScript::Penteration()
	{
		if (bupgrade[0][1])
			return;


		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetSpeedMul(0.15f);
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetPenetrateInc(1);
		}

		bupgrade[0][1] = true;
	}
	//T2 //탄환속도 25% 총알 공격력 15%
	void UpgradeScript::Smiper()
	{
		if (bupgrade[0][2])
			return;

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetSpeedMul(0.25f);
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.15f);
		}

		bupgrade[0][2] = true;
	}
	//T3 //탄속 10% 체력 20%미만 적 자동사살
	void UpgradeScript::Assassin()
	{
		if (bupgrade[0][3])
			return;

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetSpeedMul(0.1f);
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetAssassin();
		}

		bupgrade[0][3] = true;
	}
	//T1 탄환 공격력 35%, 넉백 20%
	void UpgradeScript::PowerShot()
	{
		if (bupgrade[1][0])
			return;

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.35f);
		}

		bupgrade[1][0] = true;
	}
	//T2 적이 사망할때 총알 파편 3발흩뿌리기 기존 총알의(데미지 10%)
	void UpgradeScript::Splinter()
	{
		if (bupgrade[1][1])
			return;

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.35f);
		}

		for (size_t i = 0; i < pscene->GetBrainMonsters().size(); i++)
		{
			pscene->GetBrainMonsters()[i]->GetScript<MonsterScript>()->SetDieBulletOn();
		}

		for (size_t i = 0; i < pscene->GetEyeMonsters().size(); i++)
		{
			pscene->GetEyeMonsters()[i]->GetScript<MonsterScript>()->SetDieBulletOn();
		}

		for (size_t i = 0; i < pscene->GetBoomerMonsters().size(); i++)
		{
			pscene->GetBoomerMonsters()[i]->GetScript<MonsterScript>()->SetDieBulletOn();
		}


		bupgrade[1][1] = true;
	}
	//T2 탄환 공격력 45%, 탄환 크기+40%,연사속도 -5%
	void UpgradeScript::BigShot()
	{
		if (bupgrade[1][2])
			return;

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.45f);
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetScaleInc(0.40f);
		}
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeInc(0.05f);

		bupgrade[1][2] = true;
	}
	//T3 탄환 공격력15% 관통 +1 //적을 죽이면 관통+1
	void UpgradeScript::ReaperRounds()
	{
		if (bupgrade[1][3])
			return;


		bupgrade[1][3] = true;
	}
	void UpgradeScript::RapidFire()
	{
		if (bupgrade[2][0])
			return;


		bupgrade[2][0] = true;
	}
	void UpgradeScript::LightBullets()
	{
		if (bupgrade[2][1])
			return;


		bupgrade[2][1] = true;
	}
	void UpgradeScript::RubberBullets()
	{
		if (bupgrade[2][2])
			return;


		bupgrade[2][2] = true;
	}
	void UpgradeScript::Siege()
	{
		if (bupgrade[2][3])
			return;


		bupgrade[2][3] = true;
	}
	void UpgradeScript::DoubleShot()
	{
		if (bupgrade[3][0])
			return;


		bupgrade[3][0] = true;
	}
	void UpgradeScript::FanFire()
	{
		if (bupgrade[3][1])
			return;


		bupgrade[3][1] = true;
	}
	void UpgradeScript::SplitFire()
	{
		if (bupgrade[3][2])
			return;


		bupgrade[3][2] = true;
	}
	void UpgradeScript::Fusillade()
	{
		if (bupgrade[3][3])
			return;


		bupgrade[3][3] = true;
	}
	void UpgradeScript::QuickHands()
	{
		if (bupgrade[4][0])
			return;


		bupgrade[4][0] = true;
	}
	void UpgradeScript::ArmedAndReady()
	{
		if (bupgrade[4][1])
			return;


		bupgrade[4][1] = true;
	}
	void UpgradeScript::FreshClip()
	{
		if (bupgrade[4][2])
			return;


		bupgrade[4][2] = true;
	}
	void UpgradeScript::KillClip()
	{
		if (bupgrade[4][3])
			return;


		bupgrade[4][3] = true;
	}
}