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
	//T2 //탄환속도 25% 총알 공격력 15%
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
		if (bupgrade[4][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.25f);

		bupgrade[4][0] = true;
	}
	//T2 연사속도 15% 최대탄창 +1 탄속 15%
	void UpgradeScript::LightBullets()
	{
		if (bupgrade[4][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.15f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetMaxBullet(1);
		pscene->GetWeapon()->GetScript<WeaponScript>()->MaxBulletUISetting();

		for (size_t i = 0; i < pscene->GetBullet().size(); i++)
		{
			pscene->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.15f);
		}

		bupgrade[4][1] = true;
	}
	//T3 튕김+1,연사속도 +10% 탄환 데미지-10%
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
	//T3 정지상태 사격시 33%로 탄환소비X
	void UpgradeScript::Siege()
	{
		if (bupgrade[4][3])
			return;
			
			pscene->GetWeapon()->GetScript<WeaponScript>()->SetbSiege();

			return;


		bupgrade[4][3] = true;
	}
	//T1 발사수+1 산탄범위+15%, 탄환데미지-10%
	void UpgradeScript::DoubleShot()
	{
		if (bupgrade[12][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBulletCnt(1);
		pscene->GetWeapon()->GetScript<WeaponScript>()->FirePosRot();
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);

		bupgrade[12][0] = true;
	}
	//T2 마지막 탄환을 발사할때 15%의 피해를 주는 탄환 사방으로 10발 발사
	void UpgradeScript::FanFire()
	{
		if (bupgrade[12][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFanFire();

		bupgrade[12][1] = true;
	}
	//T2 뒤쪽으로 한발의 탄을 추가 발사
	void UpgradeScript::SplitFire()
	{
		if (bupgrade[12][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBackFire();


		bupgrade[12][2] = true;
	}
	//T3 발사수 +1 산탄 범위 15%, 탄 데미지 -25% 기본 발사체를 두배를 두배로
	void UpgradeScript::Fusillade()
	{
		if (bupgrade[12][3])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetBulletCnt(1);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeDec(0.10f);

		bupgrade[12][3] = true;
	}
	//T1 재장전 속도 +20, 연사 속도 5%
	void UpgradeScript::QuickHands()
	{
		if (bupgrade[14][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.2f);
		pscene->GetReloadUI()[1]->GetScript<ReloadBarScript>()->SetReloadUITimeMul(0.2f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFireDelayTimeInc(0.05f);

		bupgrade[14][0] = true;
	}
	//T2 재장전속도 10%, 최대탄장 +2
	void UpgradeScript::ArmedAndReady()
	{
		if (bupgrade[14][1])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.1f);
		pscene->GetReloadUI()[1]->GetScript<ReloadBarScript>()->SetReloadUITimeMul(0.1f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetMaxBullet(2);
		pscene->GetWeapon()->GetScript<WeaponScript>()->MaxBulletUISetting();
		bupgrade[14][1] = true;
	}
	//T2 재장전 속도 5%, 재장전 후 1초동안 총알 피해량 50%
	void UpgradeScript::FreshClip()
	{
		if (bupgrade[14][2])
			return;
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.05);
		pscene->GetReloadUI()[1]->GetScript<ReloadBarScript>()->SetReloadUITimeMul(0.05f);

		bupgrade[14][2] = true;
	}
	//T3 처치당 재장전 속도 5%증가 재장전 후 초기화
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
	//(T1) : 탄환을 2회 발사할 때마다 22의 피해를 주는 번개를 소환한다.
	void UpgradeScript::ElectroMage()
	{
		if (bupgrade[3][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetThunderOn();

		bupgrade[3][0] = true;
	}
	//(T2) : 매 초마다 근접한 두명의 적에게 번개를 떨어뜨리는 번개 벌레를 소환한다.
	void UpgradeScript::ElectroBug()
	{
		if (bupgrade[3][1])
			return;

		pscene->ThunderBugOn();

		bupgrade[3][1] = true;
	}
	//(T2) : 적에게 번개가 칠 때마다 20% 확률로 탄환을 3개 충전한다.
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
	//(T3) : 모든 번개 피해가 12 증가하고, 범위 효과가 75% 늘어난다.
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
	//(T1) : 탄환이 35% 확률로 3초간 적을 빙결시킨다. 보스는 0.3초간 빙결된다.
	void UpgradeScript::FrostMage()
	{
		if (bupgrade[8][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetFreezeOn();

		bupgrade[8][0] = true;
	}
	//(T2) : 적이 빙결될 때마다 최대 체력의 15%만큼 피해를 입는다. 보스는 1%만큼 피해를 입는다.
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
	//(T2) : 탄창의 마지막 탄을 발사했을 때 적을 얼리는 3개의 얼음 조각을 발사한다.
	void UpgradeScript::IceShard()
	{
		if (bupgrade[8][2])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetIceShardOn();

		bupgrade[8][2] = true;
	}
	//(T3) : 빙결된 적이 죽으면 폭발하여 주변에 최대 체력의 10%에 해당하는 피해를 준다.
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
	//(T1) : 탄환이 25% 확률로 저주 효과를 걸고, 탄환 데미지의 2배의 데미지를 입힙니다.
	void UpgradeScript::DarkArts()
	{
		if (bupgrade[17][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetCurseOn();

		bupgrade[17][0] = true;
	}
	//(T2) : 저주가 발동되기까지 시간을 1초 늘립니다. 대신 저주가 탄환 데미지의 100%를 추가로 입힙니다.
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
	//(T2) : 저주에 걸린적은 30% 추가 피해를 입습니다.
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
	//(T3) : 저주로 죽인 적 10마리 마다 탄환 데미지를 1% 증가시킵니다.
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
	//(T1) : 마지막 탄을 발사했을 때, 근처의 적을 강타하여 20의 데미지를 줍니다.
	void UpgradeScript::HolyAttack()
	{
		if (bupgrade[18][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetHolyAttack();

		bupgrade[18][0] = true;
	}
	//(T2) : 강타가 현재 체력당 10의 추가데미지를 줍니다.
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
	//(T2) : 강타로 죽인 적 500마리마다 최대체력이 1 증가합니다. 이 방식으로 얻는 최대 체력은 최대 3입니다.
	void UpgradeScript::Justice()
	{
		if (bupgrade[18][2])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetJusticeOn();

		bupgrade[18][2] = true;
	}
	//(T3) : 강타로 죽인 적 500마리마다 체력 1을 회복합니다.
	void UpgradeScript::Angelic()
	{
		if (bupgrade[18][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetAngelicOn();

		bupgrade[18][3] = true;
	}
	//(T1) : 마지막 탄을 발사했을 때, 돌풍을 추가로 발사합니다. 돌풍은 0.5초마다 10의 데미지를 입힙니다.
	void UpgradeScript::AeroMagic()
	{
		if (bupgrade[19][0])
			return;

		pscene->GetWeapon()->GetScript<WeaponScript>()->SetGaleTrigger();

		bupgrade[19][0] = true;
	}
	//(T2) : 이동속도 +15%, 이동속도 보너스만큼 돌풍의 데미지가 증가합니다.
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
	//(T2) : 근처의 적에게 돌풍의 2배의 데미지를 입힙니다. 돌풍의 데미지가 5증가합니다.
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
	//(T3) : 돌풍의 데미지가 15증가합니다.
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
	//(T1) : 최대 체력 +1
	void UpgradeScript::Vitality()
	{
		if (bupgrade[6][0])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetMaxHP_Add(1);
		pscene->GetPlayer()->GetScript<PlayerScript>()->HPReset();
		bupgrade[6][0] = true;
	}
	//(T2) : 피격시 15초 동안 총알 공격력 및 탄속 +50%
	void UpgradeScript::AngerPoint()
	{
		if (bupgrade[6][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetAngerPoint();

		bupgrade[6][1] = true;
	}
	//(T2) : 최대 체력 +2, 플레이어 크기 +50%, 이동 속도 -16%
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
	//(T3) : 90초마다 체력 1 회복
	void UpgradeScript::Regeneration()
	{
		if (bupgrade[6][3])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetRegeneration();

		bupgrade[6][3] = true;
	}
	//(T1) : 공격을 1회 막아주는 신성한 보호막을 생성한다. 소모된 보호막은 2분마다 재생된다.
	void UpgradeScript::HolyShield()
	{
		if (bupgrade[7][0])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->HolyShield();
		pscene->GetSoundObjects(7)->GetComponent<AudioSource>()->Play();

		bupgrade[7][0] = true;
	}
	//(T2) : 신성한 보호막이 활성화된 동안, 재장전 속도와 이동 속도를 25% 증가시킨다.
	void UpgradeScript::DivineBlessing()
	{
		if (bupgrade[7][1])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetDivineBlessingOn();

		bupgrade[7][1] = true;
	}
	//(T2) : 신성한 보호막이 활성화 된 동안 매 초 22의 피해를 주는 번개를 가까이 있는 적에게 떨어뜨린다.
	void UpgradeScript::DivineWrath()
	{
		if (bupgrade[7][2])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->DivinWrath();

		bupgrade[7][2] = true;
	}
	//(T3) : 보호막 재생성 시간이 1분이 된다.
	void UpgradeScript::StalwartShield()
	{
		if (bupgrade[12][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetShieldOnTime(60);

		bupgrade[12][3] = true;
	}
	//(T1) : 경험치 획득 범위 +30%
	void UpgradeScript::Magnetism()
	{
		if (bupgrade[10][0])
			return;

		bupgrade[10][0] = true;
	}
	//(T2) : 경험치 획득 범위 +20%, 경험치 획득 시 10% 확률로 탄환 1개 충전
	void UpgradeScript::Recharge()
	{
		if (bupgrade[10][1])
			return;

		bupgrade[10][1] = true;
	}
	//(T2) : 경험치 획득 범위 +15%, 시야 +25%	
	void UpgradeScript::WatchLearn()
	{
		if (bupgrade[10][2])
			return;

		bupgrade[10][2] = true;
	}
	//(T3) : 경험치 획득 범위 +20%, 경험치 획득 시 1초 동안 연사 속도 +35%
	void UpgradeScript::Excitement()
	{
		if (bupgrade[10][3])
			return;

		bupgrade[10][3] = true;
	}
	//(T1) : 이동속도 +20%, 연사 속도 +5%
	void UpgradeScript::Haste()
	{
		if (bupgrade[11][0])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.2f);
		pscene->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeMul(0.05f);

		bupgrade[11][0] = true;
	}
	//(T2) : 이동속도 +10%, 이동하는 동안 주변의 적에게 발화 효과를 가한다. 이 효과는 빨리 움직일수록 자주 발동된다.
	void UpgradeScript::BlazingSpeed()
	{
		if (bupgrade[11][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.1f);

		bupgrade[11][1] = true;
	}
	//(T2) : 사격 중 이동 속도를 100% 증가시킨다.
	void UpgradeScript::RunGun()
	{
		if (bupgrade[11][2])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetslowSpeedMul(1.0f);

		bupgrade[11][2] = true;
	}
	//(T3) : 10초마다 이동속도 및 총알 공격력 +10%(최대 40%), 이 효과는 피격시 초기화된다.
	void UpgradeScript::IntheWind()
	{
		if (bupgrade[11][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetIntheWindOn();

		bupgrade[11][3] = true;
	}
	//(T1) : 시야 +25%, 시야 내의 적에게 2초마다 25 피해를 준다.
	void UpgradeScript::Glare()
	{
		if (bupgrade[15][0])
			return;

		bupgrade[15][0] = true;
	}
	//(T2) : 시야 +25%. 섬광으로 주는 피해량이 2배로 증가한다.
	void UpgradeScript::IntenseGlare()
	{
		if (bupgrade[15][1])
			return;

		bupgrade[15][1] = true;
	}
	//(T2) : 시야 +15%. 섬광 피해가 총알이 명중했을 때의 효과를 적용한다.
	void UpgradeScript::SightMagic()
	{
		if (bupgrade[15][2])
			return;

		bupgrade[15][2] = true;
	}
	//(T3) : 시야 +15%. 섬광이 발생하는 빈도가 두배가 된다.
	void UpgradeScript::Saccade()
	{
		if (bupgrade[15][3])
			return;

		bupgrade[15][3] = true;
	}
	//(T1) : 회피율 +20%
	void UpgradeScript::Evasive()
	{
		if (bupgrade[20][0])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetDodgeRate(20);

		bupgrade[20][0] = true;
	}
	//(T2) : 회피율 +10%, 이동속도 +10%
	void UpgradeScript::Nimble()
	{
		if (bupgrade[20][1])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetDodgeRate(10);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.10f);

		bupgrade[20][1] = true;
	}
	//(T2) : 회피율 +5%, 캐릭터크기 -25%
	void UpgradeScript::Tiny()
	{
		if (bupgrade[20][2])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetDodgeRate(5);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetScaleRed(0.25f);

		bupgrade[20][2] = true;
	}
	//(T3) : 이동속도 +15%, 이동속도 보너스만큼 회피율이 증가합니다.
	void UpgradeScript::Reflex()
	{
		if (bupgrade[20][3])
			return;

		pscene->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.15f);
		pscene->GetPlayer()->GetScript<PlayerScript>()->SetReflexOn();

		bupgrade[20][3] = true;
	}
	//1분 후에 용으로 부화하는 알을 얻는다. 부화한 용은 커서 방향으로 피해와 발화 상태를 주는 탄을 세 갈래로 발사한다. (기본 관통 1회, 기본 피해량 20)
	void UpgradeScript::DragonEgg()
	{
		if (bupgrade[2][0])
			return;

		pscene->GetDragonPet()->Life();

		bupgrade[2][0] = true;
	}
	//(T2) : 용의 피해량이 60초마다 8 상승한다. 이 효과는 아직 부화하지 않았어도 적용된다.
	void UpgradeScript::AgedDragon()
	{
		if (bupgrade[2][1])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetAgedDragonOn();

		bupgrade[2][1] = true;
	}
	//(T2) : 용의 공격 속도가 60초마다 10% 상승한다. 이 효과는 아직 부화하지 않았어도 적용된다.
	void UpgradeScript::TrainedDragon()
	{
		if (bupgrade[2][2])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->SetTrainedDragon();

		bupgrade[2][2] = true;
	}
	//(T3) : 투사체가 용의 공격력 10%에 해당하는 추가 피해를 입힌다.드래곤 특성을 얼마나 빨리 먹느냐로 갈린다.일반 모드에선 이론상 최대 17.2까지 받을 수 있다.
	void UpgradeScript::DragonBond()
	{
		if (bupgrade[2][3])
			return;

		pscene->GetSkillManager()->GetScript<SkillManager>()->DragonBond();

		bupgrade[2][3] = true;
	}
	//(T1) : 22의 피해를 주는 탄을 발사하는 유령을 소환한다.
	void UpgradeScript::GhostFriend()
	{
		if (bupgrade[5][0])
			return;

		pscene->GetGhostPet()->Life();

		bupgrade[5][0] = true;
	}
	//(T2) : 소환수 공격 속도 +50%
	void UpgradeScript::EnergeticFriends()
	{
		if (bupgrade[5][1])
			return;

		pscene->GetGhostPet()->GetScript<GhostPetScript>()->SetAttackSpeedRed(0.5f);

		bupgrade[5][1] = true;
	}
	//(T2) : 소환수 공격력 +15%, 소환수 공격 속도 +15%, 커서 방향으로 공격한다.
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
	//(T3) : 소환수 공격력 +15%, 유령의 탄을 2개 더 추가한다.
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
	//(T1) : 통과한 탄의 피해량과 크기를 30% 증가시키는 렌즈를 소환한다. 이 효과는 소환 공격력에 비례한다. 유령 친구의 탄이나 Hina의 분신 등에도 적용되며 한 탄에 여러번 적용시킬 수 있다.
	void UpgradeScript::MagicLens()
	{
		if (bupgrade[9][0])
			return;

		pscene->GetMagicLens()->Life();

		bupgrade[9][0] = true;
	}
	//(T2) : 렌즈를 통과한 탄환이 발화 효과를 입힌다. 이 발화 피해량은 탄환 피해량과 비례하기 때문에, 실질적으로 DPS를 몇배 끌어올린다.
	void UpgradeScript::IgnitingLens()
	{
		if (bupgrade[9][1])
			return;

		pscene->GetMagicLens()->GetScript<MagicLensScript>()->SetIgnitionLens();

		bupgrade[9][1] = true;
	}
	//(T2) : 렌즈를 통과한 탄환이 바운스+2를 얻는다.
	void UpgradeScript::Refraction()
	{
		if (bupgrade[9][2])
			return;

		pscene->GetMagicLens()->GetScript<MagicLensScript>()->SetRefraction();

		bupgrade[9][2] = true;
	}
	//(T3) : 렌즈의 모든 효과가 2배가 되지만, 렌즈의 크기가 절반으로 작아진다.
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

	void UpgradeScript::GameReset()
	{
		for (size_t i = 0; i < 25; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				bupgrade[i][j] = false;
			}
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