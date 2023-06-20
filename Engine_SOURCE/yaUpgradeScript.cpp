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
#include "yaSpearScript.h"
#include "yaReloadBarScript.h"
#include "yaAudioSource.h"

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
	void UpgradeScript::Penetration()
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
	void UpgradeScript::Sniper()
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
		if (bupgrade[4][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.25f);

		bupgrade[4][0] = true;
	}
	//T2 ����ӵ� 15% �ִ�źâ +1 ź�� 15%
	void UpgradeScript::LightBullets()
	{
		if (bupgrade[4][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.15f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetMaxBullet(1);

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.15f);
		}

		bupgrade[4][1] = true;
	}
	//T3 ƨ��+1,����ӵ� +10% źȯ ������-10%
	void UpgradeScript::RubberBullets()
	{
		if (bupgrade[4][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBounceTrigger();

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageDec(0.10f);
		}

		bupgrade[4][2] = true;
	}
	//T3 �������� ��ݽ� 33%�� źȯ�Һ�X
	void UpgradeScript::Siege()
	{
		if (bupgrade[4][3])
			return;
			
			pscene->GetWeapon()->GetScript<WeaponScript>()->SetbSiege();

			return;


		bupgrade[4][3] = true;
	}
	//T1 �߻��+1 ��ź����+15%, źȯ������-10%
	void UpgradeScript::DoubleShot()
	{
		if (bupgrade[12][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBulletCnt(1);
		pscene->GetWeapon()->GetScript<WeaponScript>()->FirePosRot();
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);

		bupgrade[12][0] = true;
	}
	//T2 ������ źȯ�� �߻��Ҷ� 15%�� ���ظ� �ִ� źȯ ������� 10�� �߻�
	void UpgradeScript::FanFire()
	{
		if (bupgrade[12][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFanFire();

		bupgrade[12][1] = true;
	}
	//T2 �������� �ѹ��� ź�� �߰� �߻�
	void UpgradeScript::SplitFire()
	{
		if (bupgrade[12][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBackFire();


		bupgrade[12][2] = true;
	}
	//T3 �߻�� +1 ��ź ���� 15%, ź ������ -25% �⺻ �߻�ü�� �ι踦 �ι��
	void UpgradeScript::Fusillade()
	{
		if (bupgrade[12][3])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBulletCnt(1);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);

		bupgrade[12][3] = true;
	}
	//T1 ������ �ӵ� +20, ���� �ӵ� 5%
	void UpgradeScript::QuickHands()
	{
		if (bupgrade[14][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.2f);
		pscene->GetReloadUI()[1]->GetScript<ReloadBarScript>()->SetReloadUITimeMul(0.2f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeInc(0.05f);

		bupgrade[14][0] = true;
	}
	//T2 �������ӵ� 10%, �ִ�ź�� +2
	void UpgradeScript::ArmedAndReady()
	{
		if (bupgrade[14][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.1f);
		pscene->GetReloadUI()[1]->GetScript<ReloadBarScript>()->SetReloadUITimeMul(0.1f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetMaxBullet(2);
		bupgrade[14][1] = true;
	}
	//T2 ������ �ӵ� 5%, ������ �� 1�ʵ��� �Ѿ� ���ط� 50%
	void UpgradeScript::FreshClip()
	{
		if (bupgrade[14][2])
			return;
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.05);
		pscene->GetReloadUI()[1]->GetScript<ReloadBarScript>()->SetReloadUITimeMul(0.05f);

		bupgrade[14][2] = true;
	}
	//T3 óġ�� ������ �ӵ� 5%���� ������ �� �ʱ�ȭ
	void UpgradeScript::KillClip()
	{
		if (bupgrade[14][3])
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


		bupgrade[14][3] = true;
	}
	//(T1) : źȯ�� 2ȸ �߻��� ������ 22�� ���ظ� �ִ� ������ ��ȯ�Ѵ�.
	void UpgradeScript::ElectroMage()
	{
		if (bupgrade[3][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetThunderOn();

		bupgrade[3][0] = true;
	}
	//(T2) : �� �ʸ��� ������ �θ��� ������ ������ ����߸��� ���� ������ ��ȯ�Ѵ�.
	void UpgradeScript::ElectroBug()
	{
		if (bupgrade[3][1])
			return;

		pscene->ThunderBugOn();

		bupgrade[3][1] = true;
	}
	//(T2) : ������ ������ ĥ ������ 20% Ȯ���� źȯ�� 3�� �����Ѵ�.
	void UpgradeScript::Energized()
	{
		if (bupgrade[3][2])
			return;

		for (size_t i = 0; i < pscene->GetThunders().size(); i++)
		{
			pscene->GetThunders()[i]->GetScript<ThunderScript>()->EnergizedOn();
		}

		bupgrade[3][2] = true;
	}
	//(T3) : ��� ���� ���ذ� 12 �����ϰ�, ���� ȿ���� 75% �þ��.
	void UpgradeScript::ElectroMastery()
	{
		if (bupgrade[3][3])
			return;

		for (size_t i = 0; i < pscene->GetThunders().size(); i++)
		{
			pscene->GetThunders()[i]->GetScript<ThunderScript>()->DamageUP(12);
			pscene->GetThunders()[i]->GetComponent<Collider2D>()->SetSize(Vector2(0.4f, 1.0f));
		}

		bupgrade[3][3] = true;
	}
	//(T1) : źȯ�� 35% Ȯ���� 3�ʰ� ���� �����Ų��. ������ 0.3�ʰ� ����ȴ�.
	void UpgradeScript::FrostMage()
	{
		if (bupgrade[8][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFreezeOn();

		bupgrade[8][0] = true;
	}
	//(T2) : ���� ����� ������ �ִ� ü���� 15%��ŭ ���ظ� �Դ´�. ������ 1%��ŭ ���ظ� �Դ´�.
	void UpgradeScript::Frostbite()
	{
		if (bupgrade[8][1])
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

		bupgrade[8][1] = true;
	}
	//(T2) : źâ�� ������ ź�� �߻����� �� ���� �󸮴� 3���� ���� ������ �߻��Ѵ�.
	void UpgradeScript::IceShard()
	{
		if (bupgrade[8][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetIceShardOn();

		bupgrade[8][2] = true;
	}
	//(T3) : ����� ���� ������ �����Ͽ� �ֺ��� �ִ� ü���� 10%�� �ش��ϴ� ���ظ� �ش�.
	void UpgradeScript::Shatter()
	{
		if (bupgrade[8][3])
			return;

		bupgrade[8][3] = true;
	}
	void UpgradeScript::PyroMage()
	{
		if (bupgrade[13][0])
			return;

		bupgrade[13][0] = true;
	}
	void UpgradeScript::FireStarter()
	{
		if (bupgrade[13][1])
			return;

		bupgrade[13][1] = true;
	}
	void UpgradeScript::IntenseBurn()
	{
		if (bupgrade[13][2])
			return;

		bupgrade[13][2] = true;
	}
	void UpgradeScript::SoothingWarmth()
	{
		if (bupgrade[13][3])
			return;

		bupgrade[13][3] = true;
	}
	//(T1) : źȯ�� 25% Ȯ���� ���� ȿ���� �ɰ�, źȯ �������� 2���� �������� �����ϴ�.
	void UpgradeScript::DarkArts()
	{
		if (bupgrade[17][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetCurseOn();

		bupgrade[17][0] = true;
	}
	//(T2) : ���ְ� �ߵ��Ǳ���� �ð��� 1�� �ø��ϴ�. ��� ���ְ� źȯ �������� 100%�� �߰��� �����ϴ�.
	void UpgradeScript::Doom()
	{
		if (bupgrade[17][1])
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

		bupgrade[17][1] = true;
	}
	//(T2) : ���ֿ� �ɸ����� 30% �߰� ���ظ� �Խ��ϴ�.
	void UpgradeScript::Wither()
	{
		if (bupgrade[17][2])
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

		bupgrade[17][2] = true;
	}
	//(T3) : ���ַ� ���� �� 10���� ���� źȯ �������� 1% ������ŵ�ϴ�.
	void UpgradeScript::Ritual()
	{
		if (bupgrade[17][3])
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

		bupgrade[17][3] = true;
	}
	//(T1) : ������ ź�� �߻����� ��, ��ó�� ���� ��Ÿ�Ͽ� 20�� �������� �ݴϴ�.
	void UpgradeScript::HolyAttack()
	{
		if (bupgrade[18][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetHolyAttack();

		bupgrade[18][0] = true;
	}
	//(T2) : ��Ÿ�� ���� ü�´� 10�� �߰��������� �ݴϴ�.
	void UpgradeScript::HolyMight()
	{
		if (bupgrade[18][1])
			return;

		for (size_t i = 0; i < pscene->GetSmites().size(); i++)
		{
			pscene->GetSmites()[i]->GetScript<SmiteScript>()->SetHolyMightOn();
		}
			bupgrade[18][1] = true;
	}
	//(T2) : ��Ÿ�� ���� �� 500�������� �ִ�ü���� 1 �����մϴ�. �� ������� ��� �ִ� ü���� �ִ� 3�Դϴ�.
	void UpgradeScript::Justice()
	{
		if (bupgrade[18][2])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetJusticeOn();

		bupgrade[18][2] = true;
	}
	//(T3) : ��Ÿ�� ���� �� 500�������� ü�� 1�� ȸ���մϴ�.
	void UpgradeScript::Angelic()
	{
		if (bupgrade[18][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetAngelicOn();

		bupgrade[18][3] = true;
	}
	//(T1) : ������ ź�� �߻����� ��, ��ǳ�� �߰��� �߻��մϴ�. ��ǳ�� 0.5�ʸ��� 10�� �������� �����ϴ�.
	void UpgradeScript::AeroMagic()
	{
		if (bupgrade[19][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetGaleTrigger();

		bupgrade[19][0] = true;
	}
	//(T2) : �̵��ӵ� +15%, �̵��ӵ� ���ʽ���ŭ ��ǳ�� �������� �����մϴ�.
	void UpgradeScript::WindBorne()
	{
		if (bupgrade[19][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.15f);
		for (size_t i = 0; i < pscene->GetGale().size(); i++)
		{
			pscene->GetGale()[i]->GetScript<GaleScript>()->SetWindBorneOn();
		}

		bupgrade[19][1] = true;
	}
	//(T2) : ��ó�� ������ ��ǳ�� 2���� �������� �����ϴ�. ��ǳ�� �������� 5�����մϴ�.
	void UpgradeScript::EyeoftheStorm()
	{
		if (bupgrade[19][2])
			return;

		for (size_t i = 0; i < pscene->GetGale().size(); i++)
		{
			pscene->GetGale()[i]->GetScript<GaleScript>()->SetEyeoftheStormOn();
			pscene->GetGale()[i]->GetScript<GaleScript>()->SetDamageUP(5);
		}

		bupgrade[19][2] = true;
	}
	//(T3) : ��ǳ�� �������� 15�����մϴ�.
	void UpgradeScript::AeroMastery()
	{
		if (bupgrade[19][3])
			return;

		for (size_t i = 0; i < pscene->GetGale().size(); i++)
		{
			pscene->GetGale()[i]->GetScript<GaleScript>()->SetDamageUP(15);
		}

		bupgrade[19][3] = true;
	}
	//(T1) : �ִ� ü�� +1
	void UpgradeScript::Vitality()
	{
		if (bupgrade[6][0])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetMaxHP_Add(1);
		pscene->GetPlayer()->GetScript<PlayerScript>()->HPReset();
		bupgrade[6][0] = true;
	}
	//(T2) : �ǰݽ� 15�� ���� �Ѿ� ���ݷ� �� ź�� +50%
	void UpgradeScript::AngerPoint()
	{
		if (bupgrade[6][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetAngerPoint();

		bupgrade[6][1] = true;
	}
	//(T2) : �ִ� ü�� +2, �÷��̾� ũ�� +50%, �̵� �ӵ� -16%
	void UpgradeScript::Giant()
	{
		if (bupgrade[6][2])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetMaxHP_Add(2);
		pscene->GetPlayer()->GetScript<PlayerScript>()->HPReset();
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedRed(0.16f);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetScaleMul(0.5f);

		bupgrade[6][2] = true;
	}
	//(T3) : 90�ʸ��� ü�� 1 ȸ��
	void UpgradeScript::Regeneration()
	{
		if (bupgrade[6][3])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetRegeneration();

		bupgrade[6][3] = true;
	}
	//(T1) : ������ 1ȸ �����ִ� �ż��� ��ȣ���� �����Ѵ�. �Ҹ�� ��ȣ���� 2�и��� ����ȴ�.
	void UpgradeScript::HolyShield()
	{
		if (bupgrade[7][0])
			return;

		pscene->GetShield()->Life();
		pscene->GetSoundObjects(7)->GetComponent<AudioSource>()->Play();

		bupgrade[7][0] = true;
	}
	//(T2) : �ż��� ��ȣ���� Ȱ��ȭ�� ����, ������ �ӵ��� �̵� �ӵ��� 25% ������Ų��.
	void UpgradeScript::DivineBlessing()
	{
		if (bupgrade[7][1])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetDivineBlessingOn();

		bupgrade[7][1] = true;
	}
	//(T2) : �ż��� ��ȣ���� Ȱ��ȭ �� ���� �� �� 22�� ���ظ� �ִ� ������ ������ �ִ� ������ ����߸���.
	void UpgradeScript::DivineWrath()
	{
		if (bupgrade[7][2])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->DivinWrath();

		bupgrade[7][2] = true;
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
		if (bupgrade[10][0])
			return;

		bupgrade[10][0] = true;
	}
	//(T2) : ����ġ ȹ�� ���� +20%, ����ġ ȹ�� �� 10% Ȯ���� źȯ 1�� ����
	void UpgradeScript::Recharge()
	{
		if (bupgrade[10][1])
			return;

		bupgrade[10][1] = true;
	}
	//(T2) : ����ġ ȹ�� ���� +15%, �þ� +25%	
	void UpgradeScript::WatchLearn()
	{
		if (bupgrade[10][2])
			return;

		bupgrade[10][2] = true;
	}
	//(T3) : ����ġ ȹ�� ���� +20%, ����ġ ȹ�� �� 1�� ���� ���� �ӵ� +35%
	void UpgradeScript::Excitement()
	{
		if (bupgrade[10][3])
			return;

		bupgrade[10][3] = true;
	}
	//(T1) : �̵��ӵ� +20%, ���� �ӵ� +5%
	void UpgradeScript::Haste()
	{
		if (bupgrade[11][0])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.2f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeMul(0.05f);

		bupgrade[11][0] = true;
	}
	//(T2) : �̵��ӵ� +10%, �̵��ϴ� ���� �ֺ��� ������ ��ȭ ȿ���� ���Ѵ�. �� ȿ���� ���� �����ϼ��� ���� �ߵ��ȴ�.
	void UpgradeScript::BlazingSpeed()
	{
		if (bupgrade[11][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.1f);

		bupgrade[11][1] = true;
	}
	//(T2) : ��� �� �̵� �ӵ��� 100% ������Ų��.
	void UpgradeScript::RunGun()
	{
		if (bupgrade[11][2])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetslowSpeedMul(1.0f);

		bupgrade[11][2] = true;
	}
	//(T3) : 10�ʸ��� �̵��ӵ� �� �Ѿ� ���ݷ� +10%(�ִ� 40%), �� ȿ���� �ǰݽ� �ʱ�ȭ�ȴ�.
	void UpgradeScript::IntheWind()
	{
		if (bupgrade[11][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetIntheWindOn();

		bupgrade[11][3] = true;
	}
	//(T1) : �þ� +25%, �þ� ���� ������ 2�ʸ��� 25 ���ظ� �ش�.
	void UpgradeScript::Glare()
	{
		if (bupgrade[15][0])
			return;

		bupgrade[15][0] = true;
	}
	//(T2) : �þ� +25%. �������� �ִ� ���ط��� 2��� �����Ѵ�.
	void UpgradeScript::IntenseGlare()
	{
		if (bupgrade[15][1])
			return;

		bupgrade[15][1] = true;
	}
	//(T2) : �þ� +15%. ���� ���ذ� �Ѿ��� �������� ���� ȿ���� �����Ѵ�.
	void UpgradeScript::SightMagic()
	{
		if (bupgrade[15][2])
			return;

		bupgrade[15][2] = true;
	}
	//(T3) : �þ� +15%. ������ �߻��ϴ� �󵵰� �ι谡 �ȴ�.
	void UpgradeScript::Saccade()
	{
		if (bupgrade[15][3])
			return;

		bupgrade[15][3] = true;
	}
	//(T1) : ȸ���� +20%
	void UpgradeScript::Evasive()
	{
		if (bupgrade[20][0])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetDodgeRate(20);

		bupgrade[20][0] = true;
	}
	//(T2) : ȸ���� +10%, �̵��ӵ� +10%
	void UpgradeScript::Nimble()
	{
		if (bupgrade[20][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetDodgeRate(10);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.10f);

		bupgrade[20][1] = true;
	}
	//(T2) : ȸ���� +5%, ĳ����ũ�� -25%
	void UpgradeScript::Tiny()
	{
		if (bupgrade[20][2])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetDodgeRate(5);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetScaleRed(0.25f);

		bupgrade[20][2] = true;
	}
	//(T3) : �̵��ӵ� +15%, �̵��ӵ� ���ʽ���ŭ ȸ������ �����մϴ�.
	void UpgradeScript::Reflex()
	{
		if (bupgrade[20][3])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.15f);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetReflexOn();

		bupgrade[20][3] = true;
	}
	//1�� �Ŀ� ������ ��ȭ�ϴ� ���� ��´�. ��ȭ�� ���� Ŀ�� �������� ���ؿ� ��ȭ ���¸� �ִ� ź�� �� ������ �߻��Ѵ�. (�⺻ ���� 1ȸ, �⺻ ���ط� 20)
	void UpgradeScript::DragonEgg()
	{
		if (bupgrade[2][0])
			return;

		pscene->GetDragonPet()->Life();

		bupgrade[2][0] = true;
	}
	//(T2) : ���� ���ط��� 60�ʸ��� 8 ����Ѵ�. �� ȿ���� ���� ��ȭ���� �ʾҾ ����ȴ�.
	void UpgradeScript::AgedDragon()
	{
		if (bupgrade[2][1])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetAgedDragonOn();

		bupgrade[2][1] = true;
	}
	//(T2) : ���� ���� �ӵ��� 60�ʸ��� 10% ����Ѵ�. �� ȿ���� ���� ��ȭ���� �ʾҾ ����ȴ�.
	void UpgradeScript::TrainedDragon()
	{
		if (bupgrade[2][2])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetTrainedDragon();

		bupgrade[2][2] = true;
	}
	//(T3) : ����ü�� ���� ���ݷ� 10%�� �ش��ϴ� �߰� ���ظ� ������.�巡�� Ư���� �󸶳� ���� �Դ��ķ� ������.�Ϲ� ��忡�� �̷л� �ִ� 17.2���� ���� �� �ִ�.
	void UpgradeScript::DragonBond()
	{
		if (bupgrade[2][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->DragonBond();

		bupgrade[2][3] = true;
	}
	//(T1) : 22�� ���ظ� �ִ� ź�� �߻��ϴ� ������ ��ȯ�Ѵ�.
	void UpgradeScript::GhostFriend()
	{
		if (bupgrade[5][0])
			return;

		pscene->GetGhostPet()->Life();

		bupgrade[5][0] = true;
	}
	//(T2) : ��ȯ�� ���� �ӵ� +50%
	void UpgradeScript::EnergeticFriends()
	{
		if (bupgrade[5][1])
			return;

		pscene->GetGhostPet()->GetScript<GhostPetScript>()->SetAttackSpeedRed(0.5f);

		bupgrade[5][1] = true;
	}
	//(T2) : ��ȯ�� ���ݷ� +15%, ��ȯ�� ���� �ӵ� +15%, Ŀ�� �������� �����Ѵ�.
	void UpgradeScript::InSync()
	{
		if (bupgrade[5][2])
			return;

		for (size_t i = 0; i < pscene->GetGhostBullets().size(); i++)
		{
			pscene->GetGhostBullets()[i]->GetScript<GhostBullet>()->SetDamageMul(0.15f);
		}
		pscene->GetGhostPet()->GetScript<GhostPetScript>()->SetAttackSpeedRed(0.15f);
		pscene->GetGhostPet()->GetScript<GhostPetScript>()->SetTargetToMouseOn();

		bupgrade[5][2] = true;
	}
	//(T3) : ��ȯ�� ���ݷ� +15%, ������ ź�� 2�� �� �߰��Ѵ�.
	void UpgradeScript::VengefulGhost()
	{
		if (bupgrade[5][3])
			return;

		for (size_t i = 0; i < pscene->GetGhostBullets().size(); i++)
		{
			pscene->GetGhostBullets()[i]->GetScript<GhostBullet>()->SetDamageMul(0.15f);
		}
		pscene->GetGhostPet()->GetScript<GhostPetScript>()->SetVengefulGhostOn();


		bupgrade[5][3] = true;
	}
	//(T1) : ����� ź�� ���ط��� ũ�⸦ 30% ������Ű�� ��� ��ȯ�Ѵ�. �� ȿ���� ��ȯ ���ݷ¿� ����Ѵ�. ���� ģ���� ź�̳� Hina�� �н� ��� ����Ǹ� �� ź�� ������ �����ų �� �ִ�.
	void UpgradeScript::MagicLens()
	{
		if (bupgrade[9][0])
			return;

		pscene->GetMagicLens()->Life();

		bupgrade[9][0] = true;
	}
	//(T2) : ��� ����� źȯ�� ��ȭ ȿ���� ������. �� ��ȭ ���ط��� źȯ ���ط��� ����ϱ� ������, ���������� DPS�� ��� ����ø���.
	void UpgradeScript::IgnitingLens()
	{
		if (bupgrade[9][1])
			return;

		pscene->GetMagicLens()->GetScript<MagicLensScript>()->SetIgnitionLens();

		bupgrade[9][1] = true;
	}
	//(T2) : ��� ����� źȯ�� �ٿ+2�� ��´�.
	void UpgradeScript::Refraction()
	{
		if (bupgrade[9][2])
			return;

		pscene->GetMagicLens()->GetScript<MagicLensScript>()->SetRefraction();

		bupgrade[9][2] = true;
	}
	//(T3) : ������ ��� ȿ���� 2�谡 ������, ������ ũ�Ⱑ �������� �۾�����.
	void UpgradeScript::FocalPoint()
	{
		if (bupgrade[9][3])
			return;

		pscene->GetMagicLens()->GetScript<MagicLensScript>()->FocalPoint();

		bupgrade[9][3] = true;
	}
	void UpgradeScript::MagicSpear()
	{
		if (bupgrade[21][0])
			return;

		for (size_t i = 0; i < pscene->Getspears().size(); i++)
		{
			pscene->Getspears()[i]->Life();
		}

		bupgrade[21][0] = true;
	}
	void UpgradeScript::HolySpear()
	{
		if (bupgrade[21][1])
			return;
		for (size_t i = 0; i < pscene->Getspears().size(); i++)
		{
			pscene->Getspears()[i]->GetScript<SpearScript>()->SetHolySPearOn();
		}

		bupgrade[21][1] = true;
	}
	void UpgradeScript::SoulDrain()
	{
		if (bupgrade[21][2])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetMaxHP_Add(1);
		pscene->GetPlayer()->GetScript<PlayerScript>()->HPReset();

		bupgrade[21][2] = true;
	}
	void UpgradeScript::SoulKnight()
	{
		if (bupgrade[21][3])
			return;

		for (size_t i = 0; i < pscene->Getspears().size(); i++)
		{
			pscene->Getspears()[i]->GetScript<SpearScript>()->SetSoulKnightOn();
		}

		bupgrade[21][3] = true;
	}
	void UpgradeScript::MagicScythe()
	{
		if (bupgrade[16][0])
			return;

		pscene->GetScythe()->Life();

		bupgrade[16][0] = true;
	}
	void UpgradeScript::Shadowblade()
	{
		if (bupgrade[16][1])
			return;


		bupgrade[16][1] = true;
	}
	void UpgradeScript::Windcutter()
	{
		if (bupgrade[16][2])
			return;


		bupgrade[16][2] = true;
	}
	void UpgradeScript::ScytheMastery()
	{
		if (bupgrade[16][3])
			return;


		bupgrade[16][3] = true;
	}
	void UpgradeScript::SoulReap()
	{
		if (bupgrade[22][0])
			return;

		bupgrade[22][0] = true;
	}
	void UpgradeScript::SoulConversion()
	{
		if (bupgrade[22][1])
			return;

		bupgrade[22][1] = true;
	}
	void UpgradeScript::SoulPowered()
	{
		if (bupgrade[22][2])
			return;

		bupgrade[22][2] = true;
	}
	void UpgradeScript::SoulLink()
	{
		if (bupgrade[22][3])
			return;

		bupgrade[22][3] = true;
	}
	void UpgradeScript::Trainer()
	{
		if (bupgrade[23][0])
			return;

		bupgrade[23][0] = true;
	}
	void UpgradeScript::PulsingSummons()
	{
		if (bupgrade[23][1])
			return;

		bupgrade[23][1] = true;
	}
	void UpgradeScript::FeedtheBeasts()
	{
		if (bupgrade[23][2])
			return;

		bupgrade[23][2] = true;
	}
	void UpgradeScript::Bloodsuckers()
	{
		if (bupgrade[23][3])
			return;

		bupgrade[23][3] = true;
	}
	void UpgradeScript::Frenzy()
	{
		if (bupgrade[24][0])
			return;

		bupgrade[24][0] = true;
	}
	void UpgradeScript::Hellspawns()
	{
		if (bupgrade[24][1])
			return;

		bupgrade[24][1] = true;
	}
	void UpgradeScript::Tunderspawns()
	{
		if (bupgrade[24][2])
			return;

		bupgrade[24][2] = true;
	}
	void UpgradeScript::Culling()
	{
		if (bupgrade[24][3])
			return;

		bupgrade[24][3] = true;
	}

	void UpgradeScript::FastBulletsTree(int step)
	{
		switch (step)
		{
		case 0:
			TakeAim();
			break;
		case 1:
			Penetration();
			break;
		case 2:
			Sniper();
			break;
		case 3:
			Assassin();
			break;
		}
	}

	void UpgradeScript::DamageBoostTree(int step)
	{
		switch (step)
		{
		case 0:
			PowerShot();
			break;
		case 1:
			BigShot();
			break;
		case 2:
			Splinter();
			break;
		case 3:
			ReaperRounds();
			break;
		}
	}

	void UpgradeScript::DragonSummonTree(int step)
	{
		switch (step)
		{
		case 0:
			DragonEgg();
			break;
		case 1:
			AgedDragon();
			break;
		case 2:
			TrainedDragon();
			break;
		case 3:
			DragonBond();
			break;
		}
	}

	void UpgradeScript::ElectromancyTree(int step)
	{
		switch (step)
		{
		case 0:
			ElectroMage();
			break;
		case 1:
			ElectroBug();
			break;
		case 2:
			Energized();
			break;
		case 3:
			ElectroMastery();
			break;
		}
	}

	void UpgradeScript::QuickShotsTree(int step)
	{
		switch (step)
		{
		case 0:
			RapidFire();
			break;
		case 1:
			LightBullets();
			break;
		case 2:
			RubberBullets();
			break;
		case 3:
			Siege();
			break;
		}
	}

	void UpgradeScript::GhostAllyTree(int step)
	{
		switch (step)
		{
		case 0:
			GhostFriend();
			break;
		case 1:
			EnergeticFriends();
			break;
		case 2:
			InSync();
			break;
		case 3:
			VengefulGhost();
			break;
		}
	}

	void UpgradeScript::HealthBoostTree(int step)
	{
		switch (step)
		{
		case 0:
			Vitality();
			break;
		case 1:
			AngerPoint();
			break;
		case 2:
			Giant();
			break;
		case 3:
			Regeneration();
			break;
		}
	}

	void UpgradeScript::ShieldBoostTree(int step)
	{
		switch (step)
		{
		case 0:
			HolyShield();
			break;
		case 1:
			DivineBlessing();
			break;
		case 2:
			DivineWrath();
			break;
		case 3:
			StalwartShield();
			break;
		}
	}

	void UpgradeScript::CryomancyTree(int step)
	{
		switch (step)
		{
		case 0:
			FrostMage();
			break;
		case 1:
			Frostbite();
			break;
		case 2:
			IceShard();
			break;
		case 3:
			Shatter();
			break;
		}
	}

	void UpgradeScript::MagicLensTree(int step)
	{
		switch (step)
		{
		case 0:
			MagicLens();
			break;
		case 1:
			IgnitingLens();
			break;
		case 2:
			Refraction();
			break;
		case 3:
			FocalPoint();
			break;
		}
	}

	void UpgradeScript::MagnetXPTree(int step)
	{
		switch (step)
		{
		case 0:
			Magnetism();
			break;
		case 1:
			Recharge();
			break;
		case 2:
			WatchLearn();
			break;
		case 3:
			Excitement();
			break;
		}
	}

	void UpgradeScript::SpeedBoostTree(int step)
	{
		switch (step)
		{
		case 0:
			Haste();
			break;
		case 1:
			BlazingSpeed();
			break;
		case 2:
			RunGun();
			break;
		case 3:
			IntheWind();
			break;
		}
	}

	void UpgradeScript::MultiShotsTree(int step)
	{
		switch (step)
		{
		case 0:
			DoubleShot();
			break;
		case 1:
			FanFire();
			break;
		case 2:
			SplitFire();
			break;
		case 3:
			Fusillade();
			break;
		}
	}

	void UpgradeScript::PyromancyTree(int step)
	{
		switch (step)
		{
		case 0:
			PyroMage();
			break;
		case 1:
			FireStarter();
			break;
		case 2:
			IntenseBurn();
			break;
		case 3:
			SoothingWarmth();
			break;
		}
	}

	void UpgradeScript::ReloadBoostTree(int step)
	{
		switch (step)
		{
		case 0:
			QuickHands();
			break;
		case 1:
			ArmedAndReady();
			break;
		case 2:
			FreshClip();
			break;
		case 3:
			KillClip();
			break;
		}
	}

	void UpgradeScript::SynergiesTree(int step)
	{
		switch (step)
		{
		case 0:
			Glare();
			break;
		case 1:
			IntenseGlare();
			break;
		case 2:
			SightMagic();
			break;
		case 3:
			Saccade();
			break;
		}
	}

	void UpgradeScript::MagicScythetree(int step)
	{
		switch (step)
		{
		case 0:
			MagicScythe();
			break;
		case 1:
			Shadowblade();
			break;
		case 2:
			Windcutter();
			break;
		case 3:
			ScytheMastery();
			break;
		}
	}

	void UpgradeScript::DarkArtsTree(int step)
	{
		switch (step)
		{
		case 0:
			DarkArts();
			break;
		case 1:
			Doom();
			break;
		case 2:
			Wither();
			break;
		case 3:
			Ritual();
			break;
		}
	}

	void UpgradeScript::HolyArtsTree(int step)
	{
		switch (step)
		{
		case 0:
			HolyAttack();
			break;
		case 1:
			HolyMight();
			break;
		case 2:
			Justice();
			break;
		case 3:
			Angelic();
			break;
		}
	}

	void UpgradeScript::AeroMagicTree(int step)
	{
		switch (step)
		{
		case 0:
			AeroMagic();
			break;
		case 1:
			WindBorne();
			break;
		case 2:
			EyeoftheStorm();
			break;
		case 3:
			AeroMastery();
			break;
		}
	}

	void UpgradeScript::DodgeBoostTree(int step)
	{
		switch (step)
		{
		case 0:
			Evasive();
			break;
		case 1:
			Nimble();
			break;
		case 2:
			Tiny();
			break;
		case 3:
			Reflex();
			break;
		}
	}

	void UpgradeScript::MagicSpearTree(int step)
	{
		switch (step)
		{
		case 0:
			MagicSpear();
			break;
		case 1:
			HolySpear();
			break;
		case 2:
			SoulDrain();
			break;
		case 3:
			SoulKnight();
			break;
		}
	}

	void UpgradeScript::SoulHeartTree(int step)
	{
		switch (step)
		{
		case 0:
			SoulReap();
			break;
		case 1:
			SoulConversion();
			break;
		case 2:
			SoulPowered();
			break;
		case 3:
			SoulLink();
			break;
		}
	}

	void UpgradeScript::TrainerTree(int step)
	{
		switch (step)
		{
		case 0:
			Trainer();
			break;
		case 1:
			PulsingSummons();
			break;
		case 2:
			FeedtheBeasts();
			break;
		case 3:
			Bloodsuckers();
			break;
		}
	}

	void UpgradeScript::FrenzyTree(int step)
	{
		switch (step)
		{
		case 0:
			Frenzy();
			break;
		case 1:
			Hellspawns();
			break;
		case 2:
			Tunderspawns();
			break;
		case 3:
			Culling();
			break;
		}
	}

	void UpgradeScript::UpgradeSkill(int num, int step)
	{
		switch (num)
		{
		case 0:
			FastBulletsTree(step);
			break;
		case 1:
			DamageBoostTree(step);
			break;
		case 2:
			DragonSummonTree(step);
			break;
		case 3:
			ElectromancyTree(step);
			break;
		case 4:
			QuickShotsTree(step);
			break;
		case 5:
			GhostAllyTree(step);
			break;
		case 6:
			HealthBoostTree(step);
			break;
		case 7:
			ShieldBoostTree(step);
			break;
		case 8:
			CryomancyTree(step);
			break;
		case 9:
			MagicLensTree(step);
			break;
		case 10:
			MagnetXPTree(step);
			break;
		case 11:
			SpeedBoostTree(step);
			break;
		case 12:
			MultiShotsTree(step);
			break;
		case 13:
			PyromancyTree(step);
			break;
		case 14:
			ReloadBoostTree(step);
			break;
		case 15:
			SynergiesTree(step);
			break;
		case 16:
			MagicScythetree(step);
			break;
		case 17:
			DarkArtsTree(step);
			break;
		case 18:
			HolyArtsTree(step);
			break;
		case 19:
			AeroMagicTree(step);
			break;
		case 20:
			DodgeBoostTree(step);
			break;
		case 21:
			MagicSpearTree(step);
			break;
		case 22:
			SoulHeartTree(step);
			break;
		case 23:
			TrainerTree(step);
			break;
		case 24:
			FrenzyTree(step);
			break;
		}
	}
}