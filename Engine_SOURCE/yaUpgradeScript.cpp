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

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.15f);
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetPenetrateInc(1);
		}


		bupgrade[1][3] = true;
	}
	//T1 연사속도 25%
	void UpgradeScript::RapidFire()
	{
		if (bupgrade[2][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.25f);

		bupgrade[2][0] = true;
	}
	//T2 연사속도 15% 최대탄창 +1 탄속 15%
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
	//T3 튕김+1,연사속도 +10% 탄환 데미지-10%
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
	//T3 정지상태 사격시 33%로 탄환소비X
	void UpgradeScript::Siege()
	{
		if (bupgrade[2][3])
			return;
			
			pscene->GetWeapon()->GetScript<WeaponScript>()->SetbSiege();

			return;


		bupgrade[2][3] = true;
	}
	//T1 발사수+1 산탄범위+15%, 탄환데미지-10%
	void UpgradeScript::DoubleShot()
	{
		if (bupgrade[3][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBulletCnt(1);
		pscene->GetWeapon()->GetScript<WeaponScript>()->FirePosRot();
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);

		bupgrade[3][0] = true;
	}
	//T2 마지막 탄환을 발사할때 15%의 피해를 주는 탄환 사방으로 10발 발사
	void UpgradeScript::FanFire()
	{
		if (bupgrade[3][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFanFire();

		bupgrade[3][1] = true;
	}
	//T2 뒤쪽으로 한발의 탄을 추가 발사
	void UpgradeScript::SplitFire()
	{
		if (bupgrade[3][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBackFire();


		bupgrade[3][2] = true;
	}
	//T3 발사수 +1 산탄 범위 15%, 탄 데미지 -25% 기본 발사체를 두배를 두배로
	void UpgradeScript::Fusillade()
	{
		if (bupgrade[3][3])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBulletCnt(1);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);
		bupgrade[3][3] = true;
	}
	//T1 재장전 속도 +20, 연사 속도 5%
	void UpgradeScript::QuickHands()
	{
		if (bupgrade[4][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.20);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeInc(0.05f);

		bupgrade[4][0] = true;
	}
	//T2 재장전속도 10%, 최대탄장 +2
	void UpgradeScript::ArmedAndReady()
	{
		if (bupgrade[4][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.10);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetMaxBullet(2);
		bupgrade[4][1] = true;
	}
	//T2 재장전 속도 5%, 재장전 후 1초동안 총알 피해량 50%
	void UpgradeScript::FreshClip()
	{
		if (bupgrade[4][2])
			return;
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.05);

		bupgrade[4][2] = true;
	}
	//T3 처치당 재장전 속도 5%증가 재장전 후 초기화
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
	//(T1) : 탄환을 2회 발사할 때마다 22의 피해를 주는 번개를 소환한다.
	void UpgradeScript::ElectroMage()
	{
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetThunderOn();
	}
	//(T2) : 매 초마다 근접한 두명의 적에게 번개를 떨어뜨리는 번개 벌레를 소환한다.
	void UpgradeScript::ElectroBug()
	{
		pscene->ThunderBugOn();
	}
	//(T2) : 적에게 번개가 칠 때마다 20% 확률로 탄환을 3개 충전한다.
	void UpgradeScript::Energized()
	{
		for (size_t i = 0; i < pscene->GetThunders().size(); i++)
		{
			pscene->GetThunders()[i]->GetScript<ThunderScript>()->EnergizedOn();
		}
	}
	//(T3) : 모든 번개 피해가 12 증가하고, 범위 효과가 75% 늘어난다.
	void UpgradeScript::ElectroMastery()
	{

	}
	void UpgradeScript::FrostMage()
	{

	}
	void UpgradeScript::Frostbite()
	{

	}
	void UpgradeScript::IceShard()
	{

	}
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
	void UpgradeScript::DarkArts()
	{

	}
	void UpgradeScript::Doom()
	{

	}
	void UpgradeScript::Wither()
	{

	}
	void UpgradeScript::Ritual()
	{

	}
	void UpgradeScript::HolyAttack()
	{

	}
	void UpgradeScript::HolyMight()
	{

	}
	void UpgradeScript::Justice()
	{

	}
	void UpgradeScript::Angelic()
	{

	}
	void UpgradeScript::AeroMagic()
	{

	}
	void UpgradeScript::WindBorne()
	{

	}
	void UpgradeScript::EyeoftheStorm()
	{

	}
	void UpgradeScript::AeroMastery()
	{

	}
	void UpgradeScript::Vitality()
	{

	}
	void UpgradeScript::AngerPoint()
	{

	}
	void UpgradeScript::Giant()
	{

	}
	void UpgradeScript::Regeneration()
	{

	}
	void UpgradeScript::HolyShield()
	{

	}
	void UpgradeScript::DivineBlessing()
	{

	}
	void UpgradeScript::DivineWrath()
	{

	}
	void UpgradeScript::StalwartShield()
	{

	}
	void UpgradeScript::Magnetism()
	{

	}
	void UpgradeScript::Recharge()
	{

	}
	void UpgradeScript::WatchLearn()
	{

	}
	void UpgradeScript::Excitement()
	{

	}
	void UpgradeScript::Haste()
	{

	}
	void UpgradeScript::BlazingSpeed()
	{

	}
	void UpgradeScript::RunGun()
	{

	}
	void UpgradeScript::IntheWind()
	{

	}
	void UpgradeScript::Glare()
	{

	}
	void UpgradeScript::IntenseGlare()
	{

	}
	void UpgradeScript::SightMagic()
	{

	}
	void UpgradeScript::Saccade()
	{

	}
	void UpgradeScript::Evasive()
	{

	}
	void UpgradeScript::Nimble()
	{

	}
	void UpgradeScript::Tiny()
	{

	}
	void UpgradeScript::Reflex()
	{

	}
	void UpgradeScript::DragonEgg()
	{

	}
	void UpgradeScript::AgedDragon()
	{

	}
	void UpgradeScript::TrainedDragon()
	{

	}
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