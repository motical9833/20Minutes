#include "yaUpgradeScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaBulletScript.h"
#include "yaWeaponScript.h"
#include "yaMonsterScript.h"
#include "yaPlayerScript.h"
#include "yaThunderScript.h"
#include "yaCurseScript.h"
#include "yaSmiteScript.h"
#include "yaSkillManager.h"
#include "GaleScript.h"
#include "yaGhostPetScript.h"
#include "yaGhostBullet.h"
#include "yaMagicLensScript.h"

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

		bupgrade[5][0] = true;
	}
	//(T2) : �� �ʸ��� ������ �θ��� ������ ������ ����߸��� ���� ������ ��ȯ�Ѵ�.
	void UpgradeScript::ElectroBug()
	{
		if (bupgrade[5][1])
			return;

		pscene->ThunderBugOn();

		bupgrade[5][1] = true;
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

		bupgrade[5][2] = true;
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

		bupgrade[5][3] = true;
	}
	//(T1) : źȯ�� 35% Ȯ���� 3�ʰ� ���� �����Ų��. ������ 0.3�ʰ� ����ȴ�.
	void UpgradeScript::FrostMage()
	{
		if (bupgrade[6][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFreezeOn();

		bupgrade[6][0] = true;
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

		bupgrade[6][1] = true;
	}
	//(T2) : źâ�� ������ ź�� �߻����� �� ���� �󸮴� 3���� ���� ������ �߻��Ѵ�.
	void UpgradeScript::IceShard()
	{
		if (bupgrade[6][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetIceShardOn();

		bupgrade[6][2] = true;
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

		bupgrade[8][0] = true;
	}
	//(T2) : ���ְ� �ߵ��Ǳ���� �ð��� 1�� �ø��ϴ�. ��� ���ְ� źȯ �������� 100%�� �߰��� �����ϴ�.
	void UpgradeScript::Doom()
	{
		if (bupgrade[8][1])
			return;

		for (size_t i = 0; i < pscene->GetCurses().size(); i++)
		{
			pscene->GetCurses()[i]->GetComponent<Animator>()->Play(L"curseUpgrade", false);
			pscene->GetCurses()[i]->GetScript<CurseScript>()->SetCurseUpgrade();
		}

		for (size_t i = 0; i < pscene->GetBoomerMonsters().size(); i++)
		{
			pscene->GetBoomerMonsters()[i]->GetScript<MonsterScript>()->SetCurseMul(1.0f);
		}
		for (size_t i = 0; i < pscene->GetBrainMonsters().size(); i++)
		{
			pscene->GetBrainMonsters()[i]->GetScript<MonsterScript>()->SetCurseMul(1.0f);
		}
		for (size_t i = 0; i < pscene->GetEyeMonsters().size(); i++)
		{
			pscene->GetEyeMonsters()[i]->GetScript<MonsterScript>()->SetCurseMul(1.0f);
		}

		bupgrade[8][1] = true;
	}
	//(T2) : ���ֿ� �ɸ����� 30% �߰� ���ظ� �Խ��ϴ�.
	void UpgradeScript::Wither()
	{
		if (bupgrade[8][2])
			return;

		for (size_t i = 0; i < pscene->GetBoomerMonsters().size(); i++)
		{
			pscene->GetBoomerMonsters()[i]->GetScript<MonsterScript>()->SetbWitherOn();
		}
		for (size_t i = 0; i < pscene->GetBrainMonsters().size(); i++)
		{
			pscene->GetBrainMonsters()[i]->GetScript<MonsterScript>()->SetbWitherOn();
		}
		for (size_t i = 0; i < pscene->GetEyeMonsters().size(); i++)
		{
			pscene->GetEyeMonsters()[i]->GetScript<MonsterScript>()->SetbWitherOn();
		}

		bupgrade[8][2] = true;
	}
	//(T3) : ���ַ� ���� �� 10���� ���� źȯ �������� 1% ������ŵ�ϴ�.
	void UpgradeScript::Ritual()
	{
		if (bupgrade[8][3])
			return;

		for (size_t i = 0; i < pscene->GetBoomerMonsters().size(); i++)
		{
			pscene->GetBoomerMonsters()[i]->GetScript<MonsterScript>()->SetbRitualOn();
		}
		for (size_t i = 0; i < pscene->GetBrainMonsters().size(); i++)
		{
			pscene->GetBrainMonsters()[i]->GetScript<MonsterScript>()->SetbRitualOn();
		}
		for (size_t i = 0; i < pscene->GetEyeMonsters().size(); i++)
		{
			pscene->GetEyeMonsters()[i]->GetScript<MonsterScript>()->SetbRitualOn();
		}

		bupgrade[8][3] = true;
	}
	//(T1) : ������ ź�� �߻����� ��, ��ó�� ���� ��Ÿ�Ͽ� 20�� �������� �ݴϴ�.
	void UpgradeScript::HolyAttack()
	{
		if (bupgrade[9][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetHolyAttack();

		bupgrade[9][0] = true;
	}
	//(T2) : ��Ÿ�� ���� ü�´� 10�� �߰��������� �ݴϴ�.
	void UpgradeScript::HolyMight()
	{
		if (bupgrade[9][1])
			return;

		for (size_t i = 0; i < pscene->GetSmites().size(); i++)
		{
			pscene->GetSmites()[i]->GetScript<SmiteScript>()->SetHolyMightOn();
		}
			bupgrade[9][1] = true;
	}
	//(T2) : ��Ÿ�� ���� �� 500�������� �ִ�ü���� 1 �����մϴ�. �� ������� ��� �ִ� ü���� �ִ� 3�Դϴ�.
	void UpgradeScript::Justice()
	{
		if (bupgrade[9][2])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetJusticeOn();

		bupgrade[9][2] = true;
	}
	//(T3) : ��Ÿ�� ���� �� 500�������� ü�� 1�� ȸ���մϴ�.
	void UpgradeScript::Angelic()
	{
		if (bupgrade[9][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetAngelicOn();

		bupgrade[9][3] = true;
	}
	//(T1) : ������ ź�� �߻����� ��, ��ǳ�� �߰��� �߻��մϴ�. ��ǳ�� 0.5�ʸ��� 10�� �������� �����ϴ�.
	void UpgradeScript::AeroMagic()
	{
		if (bupgrade[10][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetGaleTrigger();

		bupgrade[10][0] = true;
	}
	//(T2) : �̵��ӵ� +15%, �̵��ӵ� ���ʽ���ŭ ��ǳ�� �������� �����մϴ�.
	void UpgradeScript::WindBorne()
	{
		if (bupgrade[10][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.15f);
		for (size_t i = 0; i < pscene->GetGale().size(); i++)
		{
			pscene->GetGale()[i]->GetScript<GaleScript>()->SetWindBorneOn();
		}

		bupgrade[10][1] = true;
	}
	//(T2) : ��ó�� ������ ��ǳ�� 2���� �������� �����ϴ�. ��ǳ�� �������� 5�����մϴ�.
	void UpgradeScript::EyeoftheStorm()
	{
		if (bupgrade[10][2])
			return;

		for (size_t i = 0; i < pscene->GetGale().size(); i++)
		{
			pscene->GetGale()[i]->GetScript<GaleScript>()->SetEyeoftheStormOn();
			pscene->GetGale()[i]->GetScript<GaleScript>()->SetDamageUP(5);
		}

		bupgrade[10][2] = true;
	}
	//(T3) : ��ǳ�� �������� 15�����մϴ�.
	void UpgradeScript::AeroMastery()
	{
		if (bupgrade[10][3])
			return;

		for (size_t i = 0; i < pscene->GetGale().size(); i++)
		{
			pscene->GetGale()[i]->GetScript<GaleScript>()->SetDamageUP(15);
		}

		bupgrade[10][3] = true;
	}
	//(T1) : �ִ� ü�� +1
	void UpgradeScript::Vitality()
	{
		if (bupgrade[11][0])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetMaxHP_Add(1);
		pscene->GetPlayer()->GetScript<PlayerScript>()->HPReset();
		bupgrade[11][0] = true;
	}
	//(T2) : �ǰݽ� 15�� ���� �Ѿ� ���ݷ� �� ź�� +50%
	void UpgradeScript::AngerPoint()
	{
		if (bupgrade[11][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetAngerPoint();

		bupgrade[11][1] = true;
	}
	//(T2) : �ִ� ü�� +2, �÷��̾� ũ�� +50%, �̵� �ӵ� -16%
	void UpgradeScript::Giant()
	{
		if (bupgrade[11][2])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetMaxHP_Add(2);
		pscene->GetPlayer()->GetScript<PlayerScript>()->HPReset();
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedRed(0.16f);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetScaleMul(0.5f);

		bupgrade[11][2] = true;
	}
	//(T3) : 90�ʸ��� ü�� 1 ȸ��
	void UpgradeScript::Regeneration()
	{
		if (bupgrade[11][3])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetRegeneration();

		bupgrade[11][3] = true;
	}
	//(T1) : ������ 1ȸ �����ִ� �ż��� ��ȣ���� �����Ѵ�. �Ҹ�� ��ȣ���� 2�и��� ����ȴ�.
	void UpgradeScript::HolyShield()
	{
		if (bupgrade[12][0])
			return;

		pscene->GetShield()->Life();

		bupgrade[12][0] = true;
	}
	//(T2) : �ż��� ��ȣ���� Ȱ��ȭ�� ����, ������ �ӵ��� �̵� �ӵ��� 25% ������Ų��.
	void UpgradeScript::DivineBlessing()
	{
		if (bupgrade[12][1])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetDivineBlessingOn();

		bupgrade[12][1] = true;
	}
	//(T2) : �ż��� ��ȣ���� Ȱ��ȭ �� ���� �� �� 22�� ���ظ� �ִ� ������ ������ �ִ� ������ ����߸���.
	void UpgradeScript::DivineWrath()
	{
		if (bupgrade[12][2])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->DivinWrath();

		bupgrade[12][2] = true;
	}
	//(T3) : ��ȣ�� ����� �ð��� 1���� �ȴ�.
	void UpgradeScript::StalwartShield()
	{
		if (bupgrade[12][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetShieldOnTime(60);

		bupgrade[12][3] = true;
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
		if (bupgrade[14][0])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.2f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeMul(0.05f);

		bupgrade[14][0] = true;
	}
	//(T2) : �̵��ӵ� +10%, �̵��ϴ� ���� �ֺ��� ������ ��ȭ ȿ���� ���Ѵ�. �� ȿ���� ���� �����ϼ��� ���� �ߵ��ȴ�.
	void UpgradeScript::BlazingSpeed()
	{
		if (bupgrade[14][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.1f);

		bupgrade[14][1] = true;
	}
	//(T2) : ��� �� �̵� �ӵ��� 100% ������Ų��.
	void UpgradeScript::RunGun()
	{
		if (bupgrade[14][2])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetslowSpeedMul(1.0f);

		bupgrade[14][2] = true;
	}
	//(T3) : 10�ʸ��� �̵��ӵ� �� �Ѿ� ���ݷ� +10%(�ִ� 40%), �� ȿ���� �ǰݽ� �ʱ�ȭ�ȴ�.
	void UpgradeScript::IntheWind()
	{
		if (bupgrade[14][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetIntheWindOn();

		bupgrade[14][3] = true;
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
		if (bupgrade[16][0])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetDodgeRate(20);

		bupgrade[16][0] = true;
	}
	//(T2) : ȸ���� +10%, �̵��ӵ� +10%
	void UpgradeScript::Nimble()
	{
		if (bupgrade[16][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetDodgeRate(10);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.10f);

		bupgrade[16][1] = true;
	}
	//(T2) : ȸ���� +5%, ĳ����ũ�� -25%
	void UpgradeScript::Tiny()
	{
		if (bupgrade[16][2])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetDodgeRate(5);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetScaleRed(0.25f);

		bupgrade[16][2] = true;
	}
	//(T3) : �̵��ӵ� +15%, �̵��ӵ� ���ʽ���ŭ ȸ������ �����մϴ�.
	void UpgradeScript::Reflex()
	{
		if (bupgrade[16][3])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.15f);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetReflexOn();

		bupgrade[16][3] = true;
	}
	//1�� �Ŀ� ������ ��ȭ�ϴ� ���� ��´�. ��ȭ�� ���� Ŀ�� �������� ���ؿ� ��ȭ ���¸� �ִ� ź�� �� ������ �߻��Ѵ�. (�⺻ ���� 1ȸ, �⺻ ���ط� 20)
	void UpgradeScript::DragonEgg()
	{
		if (bupgrade[17][0])
			return;

		pscene->GetDragonPet()->Life();

		bupgrade[17][0] = true;
	}
	//(T2) : ���� ���ط��� 60�ʸ��� 8 ����Ѵ�. �� ȿ���� ���� ��ȭ���� �ʾҾ ����ȴ�.
	void UpgradeScript::AgedDragon()
	{
		if (bupgrade[17][1])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetAgedDragonOn();

		bupgrade[17][1] = true;
	}
	//(T2) : ���� ���� �ӵ��� 60�ʸ��� 10% ����Ѵ�. �� ȿ���� ���� ��ȭ���� �ʾҾ ����ȴ�.
	void UpgradeScript::TrainedDragon()
	{
		if (bupgrade[17][2])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetTrainedDragon();

		bupgrade[17][2] = true;
	}
	//(T3) : ����ü�� ���� ���ݷ� 10%�� �ش��ϴ� �߰� ���ظ� ������.�巡�� Ư���� �󸶳� ���� �Դ��ķ� ������.�Ϲ� ��忡�� �̷л� �ִ� 17.2���� ���� �� �ִ�.
	void UpgradeScript::DragonBond()
	{
		if (bupgrade[17][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->DragonBond();

		bupgrade[17][3] = true;
	}
	//(T1) : 22�� ���ظ� �ִ� ź�� �߻��ϴ� ������ ��ȯ�Ѵ�.
	void UpgradeScript::GhostFriend()
	{
		if (bupgrade[18][0])
			return;

		pscene->GetGhostPet()->Life();

		bupgrade[18][0] = true;
	}
	//(T2) : ��ȯ�� ���� �ӵ� +50%
	void UpgradeScript::EnergeticFriends()
	{
		if (bupgrade[18][1])
			return;

		pscene->GetGhostPet()->GetScript<GhostPetScript>()->SetAttackSpeedRed(0.5f);

		bupgrade[18][1] = true;
	}
	//(T2) : ��ȯ�� ���ݷ� +15%, ��ȯ�� ���� �ӵ� +15%, Ŀ�� �������� �����Ѵ�.
	void UpgradeScript::InSync()
	{
		if (bupgrade[18][2])
			return;

		for (size_t i = 0; i < pscene->GetGhostBullets().size(); i++)
		{
			pscene->GetGhostBullets()[i]->GetScript<GhostBullet>()->SetDamageMul(0.15f);
		}
		pscene->GetGhostPet()->GetScript<GhostPetScript>()->SetAttackSpeedRed(0.15f);
		pscene->GetGhostPet()->GetScript<GhostPetScript>()->SetTargetToMouseOn();

		bupgrade[18][2] = true;
	}
	//(T3) : ��ȯ�� ���ݷ� +15%, ������ ź�� 2�� �� �߰��Ѵ�.
	void UpgradeScript::VengefulGhost()
	{
		if (bupgrade[18][3])
			return;

		for (size_t i = 0; i < pscene->GetGhostBullets().size(); i++)
		{
			pscene->GetGhostBullets()[i]->GetScript<GhostBullet>()->SetDamageMul(0.15f);
		}
		pscene->GetGhostPet()->GetScript<GhostPetScript>()->SetVengefulGhostOn();


		bupgrade[18][3] = true;
	}
	//(T1) : ����� ź�� ���ط��� ũ�⸦ 30% ������Ű�� ��� ��ȯ�Ѵ�. �� ȿ���� ��ȯ ���ݷ¿� ����Ѵ�. ���� ģ���� ź�̳� Hina�� �н� ��� ����Ǹ� �� ź�� ������ �����ų �� �ִ�.
	void UpgradeScript::MagicLens()
	{
		if (bupgrade[19][0])
			return;

		pscene->GetMagicLens()->Life();

		bupgrade[19][0] = true;
	}
	//(T2) : ��� ����� źȯ�� ��ȭ ȿ���� ������. �� ��ȭ ���ط��� źȯ ���ط��� ����ϱ� ������, ���������� DPS�� ��� ����ø���.
	void UpgradeScript::IgnitingLens()
	{
		if (bupgrade[19][1])
			return;

		pscene->GetMagicLens()->GetScript<MagicLensScript>()->SetIgnitionLens();

		bupgrade[19][1] = true;
	}
	//(T2) : ��� ����� źȯ�� �ٿ+2�� ��´�.
	void UpgradeScript::Refraction()
	{
		if (bupgrade[19][2])
			return;

		pscene->GetMagicLens()->GetScript<MagicLensScript>()->SetRefraction();

		bupgrade[19][2] = true;
	}
	//(T3) : ������ ��� ȿ���� 2�谡 ������, ������ ũ�Ⱑ �������� �۾�����.
	void UpgradeScript::FocalPoint()
	{
		if (bupgrade[19][3])
			return;

		pscene->GetMagicLens()->GetScript<MagicLensScript>()->FocalPoint();

		bupgrade[19][3] = true;
	}
	void UpgradeScript::MagicSpear()
	{
		if (bupgrade[20][0])
			return;

		for (size_t i = 0; i < pscene->Getspears().size(); i++)
		{
			pscene->Getspears()[i]->Life();
		}

		bupgrade[20][0] = true;
	}
	void UpgradeScript::HolySpear()
	{
		if (bupgrade[20][1])
			return;


		bupgrade[20][1] = true;
	}
	void UpgradeScript::SoulDrain()
	{
		if (bupgrade[20][2])
			return;


		bupgrade[20][2] = true;
	}
	void UpgradeScript::SoulKnight()
	{
		if (bupgrade[20][3])
			return;


		bupgrade[20][3] = true;
	}
	void UpgradeScript::MagicScythe()
	{
		if (bupgrade[21][0])
			return;

		pscene->GetScythe()->Life();

		bupgrade[21][0] = true;
	}
	void UpgradeScript::Shadowblade()
	{
		if (bupgrade[21][1])
			return;


		bupgrade[21][1] = true;
	}
	void UpgradeScript::Windcutter()
	{
		if (bupgrade[21][2])
			return;


		bupgrade[21][2] = true;
	}
	void UpgradeScript::ScytheMastery()
	{
		if (bupgrade[21][3])
			return;


		bupgrade[21][3] = true;
	}
}