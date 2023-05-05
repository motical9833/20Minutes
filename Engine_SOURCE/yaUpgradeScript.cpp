#include "yaUpgradeScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaBulletScript.h"
#include "yaWeaponScript.h"
#include "yaMonsterScript.h"
#include "yaPlayerScript.h"
#include "yaThunderScript.h"
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

		for (size_t i = 0; i < pscene->GetBoomerMonsters().size(); i++)
		{
			pscene->GetBoomerMonsters()[i]->GetScript<MonsterScript>()->KillClipOn();
		}
		for (size_t i = 0; i < pscene->GetBrainMonsters().size(); i++)
		{
			pscene->GetBrainMonsters()[i]->GetScript<MonsterScript>()->KillClipOn();
		}
		for (size_t i = 0; i < pscene->GetEyeMonsters().size(); i++)
		{
			pscene->GetEyeMonsters()[i]->GetScript<MonsterScript>()->KillClipOn();
		}


		bupgrade[4][3] = true;
	}
	//(T1) : źȯ�� 2ȸ �߻��� ������ 22�� ���ظ� �ִ� ������ ��ȯ�Ѵ�.
	void UpgradeScript::ElectroMage()
	{
		if (bupgrade[5][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetThunderOn();
	}
	//(T2) : �� �ʸ��� ������ �θ��� ������ ������ ����߸��� ���� ������ ��ȯ�Ѵ�.
	void UpgradeScript::ElectroBug()
	{
		if (bupgrade[5][1])
			return;

		pscene->ThunderBugOn();
	}
	//(T2) : ������ ������ ĥ ������ 20% Ȯ���� źȯ�� 3�� �����Ѵ�.
	void UpgradeScript::Energized()
	{
		if (bupgrade[5][2])
			return;

		for (size_t i = 0; i < pscene->GetThunders().size(); i++)
		{
			pscene->GetThunders()[i]->GetScript<ThunderScript>()->EnergizedOn();
		}
	}
	//(T3) : ��� ���� ���ذ� 12 �����ϰ�, ���� ȿ���� 75% �þ��.
	void UpgradeScript::ElectroMastery()
	{
		if (bupgrade[5][3])
			return;

		for (size_t i = 0; i < pscene->GetThunders().size(); i++)
		{
			pscene->GetThunders()[i]->GetScript<ThunderScript>()->DamageUP(12);
			pscene->GetThunders()[i]->GetComponent<Collider2D>()->SetSize(Vector2(0.4f, 1.0f));
		}
	}
	//(T1) : źȯ�� 35% Ȯ���� 3�ʰ� ���� �����Ų��. ������ 0.3�ʰ� ����ȴ�.
	void UpgradeScript::FrostMage()
	{
		if (bupgrade[6][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFreezeOn();
	}
	//(T2) : ���� ����� ������ �ִ� ü���� 15%��ŭ ���ظ� �Դ´�. ������ 1%��ŭ ���ظ� �Դ´�.
	void UpgradeScript::Frostbite()
	{
		if (bupgrade[6][1])
			return;


		for (size_t i = 0; i < pscene->GetBoomerMonsters().size(); i++)
		{
			pscene->GetBoomerMonsters()[i]->GetScript<MonsterScript>()->SetFrostbiteOn();
		}
		for (size_t i = 0; i < pscene->GetBrainMonsters().size(); i++)
		{
			pscene->GetBrainMonsters()[i]->GetScript<MonsterScript>()->SetFrostbiteOn();
		}
		for (size_t i = 0; i < pscene->GetEyeMonsters().size(); i++)
		{
			pscene->GetEyeMonsters()[i]->GetScript<MonsterScript>()->SetFrostbiteOn();
		}
	}
	//(T2) : źâ�� ������ ź�� �߻����� �� ���� �󸮴� 3���� ���� ������ �߻��Ѵ�.
	void UpgradeScript::IceShard()
	{
		if (bupgrade[6][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetIceShardOn();
	}
	//(T3) : ����� ���� ������ �����Ͽ� �ֺ��� �ִ� ü���� 10%�� �ش��ϴ� ���ظ� �ش�.
	void UpgradeScript::Shatter()
	{

	}
	void UpgradeScript::PyroMage()
	{

	}
	void UpgradeScript::FireStarter()
	{

	}
	void UpgradeScript::IntenseBurn()
	{

	}
	void UpgradeScript::SoothingWarmth()
	{

	}
	//(T1) : źȯ�� 25% Ȯ���� ���� ȿ���� �ɰ�, źȯ �������� 2���� �������� �����ϴ�.
	void UpgradeScript::DarkArts()
	{
		if (bupgrade[8][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetCurseOn();
	}
	//(T2) : ���ְ� �ߵ��Ǳ���� �ð��� 1�� �ø��ϴ�. ��� ���ְ� źȯ �������� 100%�� �߰��� �����ϴ�.
	void UpgradeScript::Doom()
	{

	}
	//(T2) : ���ֿ� �ɸ����� 30% �߰� ���ظ� �Խ��ϴ�.
	void UpgradeScript::Wither()
	{

	}
	//(T3) : ���ַ� ���� �� 10���� ���� źȯ �������� 1% ������ŵ�ϴ�.
	void UpgradeScript::Ritual()
	{

	}
	//(T1) : ������ ź�� �߻����� ��, ��ó�� ���� ��Ÿ�Ͽ� 20�� �������� �ݴϴ�.
	void UpgradeScript::HolyAttack()
	{

	}
	//(T2) : ��Ÿ�� ���� ü�´� 10�� �߰��������� �ݴϴ�.
	void UpgradeScript::HolyMight()
	{

	}
	//(T2) : ��Ÿ�� ���� �� 500�������� �ִ�ü���� 1 �����մϴ�. �� ������� ��� �ִ� ü���� �ִ� 3�Դϴ�.
	void UpgradeScript::Justice()
	{

	}
	//(T3) : ��Ÿ�� ���� �� 500�������� ü�� 1�� ȸ���մϴ�.
	void UpgradeScript::Angelic()
	{

	}
	//(T1) : ������ ź�� �߻����� ��, ��ǳ�� �߰��� �߻��մϴ�. ��ǳ�� 0.5�ʸ��� 10�� �������� �����ϴ�.
	void UpgradeScript::AeroMagic()
	{

	}
	//(T2) : �̵��ӵ� +15%, �̵��ӵ� ���ʽ���ŭ ��ǳ�� �������� �����մϴ�.
	void UpgradeScript::WindBorne()
	{

	}
	//(T2) : ��ó�� ������ ��ǳ�� 2���� �������� �����ϴ�. ��ǳ�� �������� 5�����մϴ�.
	void UpgradeScript::EyeoftheStorm()
	{

	}
	//(T3) : ��ǳ�� �������� 15�����մϴ�.
	void UpgradeScript::AeroMastery()
	{

	}
	//(T1) : �ִ� ü�� +1
	void UpgradeScript::Vitality()
	{

	}
	//(T2) : �ǰݽ� 15�� ���� �Ѿ� ���ݷ� �� ź�� +50%
	void UpgradeScript::AngerPoint()
	{

	}
	//(T2) : �ִ� ü�� +2, �÷��̾� ũ�� +50%, �̵� �ӵ� -16%
	void UpgradeScript::Giant()
	{

	}
	//(T3) : 90�ʸ��� ü�� 1 ȸ��
	void UpgradeScript::Regeneration()
	{

	}
	//(T1) : ������ 1ȸ �����ִ� �ż��� ��ȣ���� �����Ѵ�. �Ҹ�� ��ȣ���� 2�и��� ����ȴ�.
	void UpgradeScript::HolyShield()
	{

	}
	//(T2) : �ż��� ��ȣ���� Ȱ��ȭ�� ����, ������ �ӵ��� �̵� �ӵ��� 25% ������Ų��.
	void UpgradeScript::DivineBlessing()
	{

	}
	//(T2) : �ż��� ��ȣ���� Ȱ��ȭ �� ���� �� �� 22�� ���ظ� �ִ� ������ ������ �ִ� ������ ����߸���.
	void UpgradeScript::DivineWrath()
	{

	}
	//(T3) : ��ȣ�� ����� �ð��� 1���� �ȴ�.
	void UpgradeScript::StalwartShield()
	{

	}
	//(T1) : ����ġ ȹ�� ���� +30%
	void UpgradeScript::Magnetism()
	{

	}
	//(T2) : ����ġ ȹ�� ���� +20%, ����ġ ȹ�� �� 10% Ȯ���� źȯ 1�� ����
	void UpgradeScript::Recharge()
	{

	}
	//(T2) : ����ġ ȹ�� ���� +15%, �þ� +25%	
	void UpgradeScript::WatchLearn()
	{

	}
	//(T3) : ����ġ ȹ�� ���� +20%, ����ġ ȹ�� �� 1�� ���� ���� �ӵ� +35%
	void UpgradeScript::Excitement()
	{

	}
	//(T1) : �̵��ӵ� +20%, ���� �ӵ� +5%
	void UpgradeScript::Haste()
	{

	}
	//(T2) : �̵��ӵ� +10%, �̵��ϴ� ���� �ֺ��� ������ ��ȭ ȿ���� ���Ѵ�. �� ȿ���� ���� �����ϼ��� ���� �ߵ��ȴ�.
	void UpgradeScript::BlazingSpeed()
	{

	}
	//(T2) : ��� �� �̵� �ӵ��� 100% ������Ų��.
	void UpgradeScript::RunGun()
	{

	}
	//(T3) : 10�ʸ��� �̵��ӵ� �� �Ѿ� ���ݷ� +10%(�ִ� 40%), �� ȿ���� �ǰݽ� �ʱ�ȭ�ȴ�.
	void UpgradeScript::IntheWind()
	{

	}
	//(T1) : �þ� +25%, �þ� ���� ������ 2�ʸ��� 25 ���ظ� �ش�.
	void UpgradeScript::Glare()
	{

	}
	//(T2) : �þ� +25%. �������� �ִ� ���ط��� 2��� �����Ѵ�.
	void UpgradeScript::IntenseGlare()
	{

	}
	//(T2) : �þ� +15%. ���� ���ذ� �Ѿ��� �������� ���� ȿ���� �����Ѵ�.
	void UpgradeScript::SightMagic()
	{

	}
	//(T3) : �þ� +15%. ������ �߻��ϴ� �󵵰� �ι谡 �ȴ�.
	void UpgradeScript::Saccade()
	{

	}
	//(T1) : ȸ���� +20%
	void UpgradeScript::Evasive()
	{

	}
	//(T2) : ȸ���� +10%, �̵��ӵ� +10%
	void UpgradeScript::Nimble()
	{

	}
	//(T2) : ȸ���� +5%, ĳ����ũ�� -25%
	void UpgradeScript::Tiny()
	{

	}
	//(T3) : �̵��ӵ� +15%, �̵��ӵ� ���ʽ���ŭ ȸ������ �����մϴ�.
	void UpgradeScript::Reflex()
	{

	}
	//1�� �Ŀ� ������ ��ȭ�ϴ� ���� ��´�. ��ȭ�� ���� Ŀ�� �������� ���ؿ� ��ȭ ���¸� �ִ� ź�� �� ������ �߻��Ѵ�. (�⺻ ���� 1ȸ, �⺻ ���ط� 20)
	void UpgradeScript::DragonEgg()
	{

	}
	//(T2) : ���� ���ط��� 60�ʸ��� 8 ����Ѵ�. �� ȿ���� ���� ��ȭ���� �ʾҾ ����ȴ�.
	void UpgradeScript::AgedDragon()
	{

	}
	//(T2) : ���� ���� �ӵ��� 60�ʸ��� 10% ����Ѵ�. �� ȿ���� ���� ��ȭ���� �ʾҾ ����ȴ�.
	void UpgradeScript::TrainedDragon()
	{

	}
	//(T3) : ����ü�� ���� ���ݷ� 10%�� �ش��ϴ� �߰� ���ظ� ������.�巡�� Ư���� �󸶳� ���� �Դ��ķ� ������.�Ϲ� ��忡�� �̷л� �ִ� 17.2���� ���� �� �ִ�.
	void UpgradeScript::DragonBond()
	{

	}
	void UpgradeScript::GhostFriend()
	{

	}
	void UpgradeScript::EnergeticFriends()
	{

	}
	void UpgradeScript::InSync()
	{

	}
	void UpgradeScript::VengefulGhost()
	{

	}
	void UpgradeScript::MagicLens()
	{

	}
	void UpgradeScript::IgnitingLens()
	{

	}
	void UpgradeScript::Refraction()
	{

	}
	void UpgradeScript::FocalPoint()
	{

	}
}