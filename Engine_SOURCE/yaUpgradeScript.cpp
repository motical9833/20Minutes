#include "yaUpgradeScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaBulletScript.h"
#include "yaWeaponScript.h"
#include "yaMonsterScript.h"
#include "yaPlayerScript.h"

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
	//T1 źȯ�ӵ� 30% ��ź ���� -15%
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
	//T2 //źȯ �ӵ� 15% ����+1
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
	//T2 //źȯ�ӵ� 25% �Ѿ� ���ݷ� 15%
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
	//T3 //ź�� 10% ü�� 20%�̸� �� �ڵ����
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
	//T1 źȯ ���ݷ� 35%, �˹� 20%
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
	//T2 ���� ����Ҷ� �Ѿ� ���� 3����Ѹ��� ���� �Ѿ���(������ 10%)
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
	//T2 źȯ ���ݷ� 45%, źȯ ũ��+40%,����ӵ� -5%
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
	//T3 źȯ ���ݷ�15% ���� +1 //���� ���̸� ����+1
	void UpgradeScript::ReaperRounds()
	{
		if (bupgrade[1][3])
			return;

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.15f);
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetPenetrateInc(1);
		}


		bupgrade[1][3] = true;
	}
	//T1 ����ӵ� 25%
	void UpgradeScript::RapidFire()
	{
		if (bupgrade[2][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.25f);

		bupgrade[2][0] = true;
	}
	//T2 ����ӵ� 15% �ִ�źâ +1 ź�� 15%
	void UpgradeScript::LightBullets()
	{
		if (bupgrade[2][1])
			return;
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.15f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetMaxBullet(1);

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.15f);
		}

		bupgrade[2][1] = true;
	}
	//T3 ƨ��+1,����ӵ� +10% źȯ ������-10%
	void UpgradeScript::RubberBullets()
	{
		if (bupgrade[2][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBounceTrigger();

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageDec(0.10f);
		}

		bupgrade[2][2] = true;
	}
	//T3 �������� ��ݽ� 33%�� źȯ�Һ�X
	void UpgradeScript::Siege()
	{
		if (bupgrade[2][3])
			return;
			
			pscene->GetWeapon()->GetScript<WeaponScript>()->SetbSiege();

			return;


		bupgrade[2][3] = true;
	}
	//T1 �߻��+1 ��ź����+15%, źȯ������-10%
	void UpgradeScript::DoubleShot()
	{
		if (bupgrade[3][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBulletCnt(1);
		pscene->GetWeapon()->GetScript<WeaponScript>()->FirePosRot();
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);

		bupgrade[3][0] = true;
	}
	//T2 ������ źȯ�� �߻��Ҷ� 15%�� ���ظ� �ִ� źȯ ������� 10�� �߻�
	void UpgradeScript::FanFire()
	{
		if (bupgrade[3][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFanFire();

		bupgrade[3][1] = true;
	}
	//T2 �������� �ѹ��� ź�� �߰� �߻�
	void UpgradeScript::SplitFire()
	{
		if (bupgrade[3][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBackFire();


		bupgrade[3][2] = true;
	}
	//T3 �߻�� +1 ��ź ���� 15%, ź ������ -25% �⺻ �߻�ü�� �ι踦 �ι��
	void UpgradeScript::Fusillade()
	{
		if (bupgrade[3][3])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBulletCnt(1);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);
		bupgrade[3][3] = true;
	}
	//T1 ������ �ӵ� +20, ���� �ӵ� 5%
	void UpgradeScript::QuickHands()
	{
		if (bupgrade[4][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.20);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeInc(0.05f);

		bupgrade[4][0] = true;
	}
	//T2 �������ӵ� 10%, �ִ�ź�� +2
	void UpgradeScript::ArmedAndReady()
	{
		if (bupgrade[4][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.10);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetMaxBullet(2);
		bupgrade[4][1] = true;
	}
	//T2 ������ �ӵ� 5%, ������ �� 1�ʵ��� �Ѿ� ���ط� 50%
	void UpgradeScript::FreshClip()
	{
		if (bupgrade[4][2])
			return;
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.05);

		bupgrade[4][2] = true;
	}
	//T3 óġ�� ������ �ӵ� 5%���� ������ �� �ʱ�ȭ
	void UpgradeScript::KillClip()
	{
		if (bupgrade[4][3])
			return;


		bupgrade[4][3] = true;
	}
}