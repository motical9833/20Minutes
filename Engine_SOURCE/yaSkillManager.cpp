#include "yaSkillManager.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "GaleScript.h"
#include "yaTime.h"
#include "yaPlayerScript.h"
#include "yaHolyShieldScript.h"
#include "yaGhostBullet.h"
#include "yaSmiteScript.h"
#include "yaColliderCheckScript.h"
#include "yaSpearScript.h"
#include "yaDragonFireScript.h"
#include "yaAnimator.h"
#include "yaWeaponScript.h"
#include "yaBulletScript.h"
#include "yaDragonPetScript.h"

namespace ya
{
	SkillManager::SkillManager()
		: bShieldOn(false)
		, bShield(false)
		, bJustice(false)
		, bAngelic(false)
		, bDivineBlessing(false)
		, bIntheWind(false)
		, bAgedDragon(false)
		, bTrainedDragon(false)
		, shieldTime(0.0f)
		, intheWindTime(0.0f)
		, AgedDragonTime(0.0f)
		, trainedDragonTime(0.0f)
		, shieldOnTime(120)
		, smiteKillStack(0)
		, justiceCnt(0)
		, intheWindStack(0)
		, trainedDragonStack(0)
	{

	}
	SkillManager::~SkillManager()
	{

	}
	void SkillManager::Initalize()
	{

	}
	void SkillManager::Update()
	{
		if (bShieldOn)
		{
			if (bShield == false)
			{
				shieldTime += Time::DeltaTime();

				if (shieldTime > shieldOnTime)
				{
					HolyShield();
					bShield = true;
					bShieldOn = false;
					shieldTime = 0;
				}
			}
		}

		if (bIntheWind)
		{
			IntheWind();
		}

		if (bAgedDragon)
		{
			AgedDragonTime += Time::DeltaTime();

			if (AgedDragonTime >= 60)
			{
				AgedDragon();
				AgedDragonTime = 0.0f;
			}
		}

		if (bTrainedDragon)
		{
			trainedDragonTime += Time::DeltaTime();

			if (trainedDragonTime >= 60 && trainedDragonStack < 6)
			{
				TrainedDragon();
				trainedDragonTime = 0.0f;
			}
		}
	}
	void SkillManager::FixedUpdate()
	{

	}
	void SkillManager::Render()
	{

	}
	void SkillManager::ThunderEnchant(Vector3 Enchantobject)
	{

		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetThunders().size(); i++)
		{
			if (SceneManager::GetPlayScene()->GetThunders()[i] == nullptr)
				return;

			if (SceneManager::GetPlayScene()->GetThunders()[i]->IsDead() == false)
				continue;

			SceneManager::GetPlayScene()->GetThunders()[i]->GetComponent<Transform>()->SetPosition(Enchantobject);
			SceneManager::GetPlayScene()->GetThunders()[i]->Life();
			break;
		}
	}
	void SkillManager::GaleFire(Vector3 pos,Vector3 dir)
	{
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetGale().size(); i++)
		{
			if (SceneManager::GetPlayScene()->GetGale()[i] == nullptr)
				return;

			if (SceneManager::GetPlayScene()->GetGale()[i]->IsDead() == false)
				continue;

			SceneManager::GetPlayScene()->GetGale()[i]->GetComponent<Transform>()->SetPosition(pos);
			SceneManager::GetPlayScene()->GetGale()[i]->GetScript<GaleScript>()->SetDir(dir);
			SceneManager::GetPlayScene()->GetGale()[i]->Life();
			break;
		}
	}

	void SkillManager::GhostFire(Vector3 pos, Vector3 dir)
	{
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetGhostBullets().size(); i++)
		{
			if (SceneManager::GetPlayScene()->GetGhostBullets()[i] == nullptr)
				return;

			if (SceneManager::GetPlayScene()->GetGhostBullets()[i]->IsDead() == false)
				continue;

			SceneManager::GetPlayScene()->GetGhostBullets()[i]->GetComponent<Transform>()->SetPosition(pos);
			SceneManager::GetPlayScene()->GetGhostBullets()[i]->GetScript<GhostBullet>()->SetDir(dir);
			SceneManager::GetPlayScene()->GetGhostBullets()[i]->Life();
			break;
		}
	}

	void SkillManager::SmiteFire(Vector3 pos)
	{
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetSmites().size(); i++)
		{
			if (SceneManager::GetPlayScene()->GetSmites()[i] == nullptr)
				return;

			if (SceneManager::GetPlayScene()->GetSmites()[i]->IsDead() == false)
				continue;

			SceneManager::GetPlayScene()->GetSmites()[i]->GetComponent<Transform>()->SetPosition(pos);
			SceneManager::GetPlayScene()->GetSmites()[i]->Life();
			break;
		}
	}

	void SkillManager::HolyShield()
	{
		GameObject* shield = SceneManager::GetPlayScene()->GetShield();
		shield->Life();
		SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->ShieldOn();
		if(bDivineBlessing)
		shield->GetScript<HolyShieldScript>()->DivineBlessing();
	}
	void SkillManager::DivinWrath()
	{
		SceneManager::GetPlayScene()->GetShield()->GetScript<HolyShieldScript>()->SetDivinWrathOn();
	}
	void SkillManager::DragonFIre(Vector3 pos, Vector3 dir)
	{
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetDragonFires().size(); i++)
		{
			if (SceneManager::GetPlayScene()->GetDragonFires()[i] == nullptr)
				return;

			if (SceneManager::GetPlayScene()->GetDragonFires()[i]->IsDead() == false)
				continue;

			SceneManager::GetPlayScene()->GetDragonFires()[i]->GetComponent<Transform>()->SetPosition(pos);
			SceneManager::GetPlayScene()->GetDragonFires()[i]->GetScript<DragonFireScript>()->SetDir(dir);
			SceneManager::GetPlayScene()->GetDragonFires()[i]->GetComponent<Animator>()->Stop();
			SceneManager::GetPlayScene()->GetDragonFires()[i]->Life();
			break;
		}
	}
	void SkillManager::AgedDragon()
	{
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetDragonFires().size(); i++)
		{
			SceneManager::GetPlayScene()->GetDragonFires()[i]->GetScript<DragonFireScript>()->SetDamage(8);
			break;
		}
	}
	void SkillManager::TrainedDragon()
	{
		SceneManager::GetPlayScene()->GetDragonPet()->GetScript<DragonPetScript>()->SetmAttackSpeedRed(0.1f);
		trainedDragonStack++;
	}
	void SkillManager::HolyShieldBreak()
	{
		bShieldOn = true;
		bShield = false;
		SceneManager::GetPlayScene()->GetShield()->GetScript<HolyShieldScript>()->Break();
	}
	void SkillManager::Spear()
	{
		for (size_t i = 0; i < 2; i++)
		{
			if (SceneManager::GetPlayScene()->Getspears()[i]->GetScript<SpearScript>()->GetBAttack() == true)
				return;

			SceneManager::GetPlayScene()->Getspears()[i]->GetScript<SpearScript>()->Attack();
		}
	}
	void SkillManager::IceShard(Vector3 pos, Vector3 dir)
	{
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetIcicles().size(); i++)
		{
			if (SceneManager::GetPlayScene()->GetIcicles()[i] == nullptr)
				return;

			if (SceneManager::GetPlayScene()->GetIcicles()[i]->IsDead() == false)
				continue;


			SceneManager::GetPlayScene()->GetIcicles()[i]->GetComponent<Transform>()->SetRotation(dir);
			SceneManager::GetPlayScene()->GetIcicles()[i]->GetComponent<Transform>()->SetPosition(pos);
			SceneManager::GetPlayScene()->GetIcicles()[i]->Life();
			break;
		}
	}
	void SkillManager::SmiteKillCnt()
	{
		if (bJustice)
		{
			smiteKillStack++;


			if (smiteKillStack % 500 == 0 && justiceCnt < 3)
			{
				SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->SetMaxHP_Add(1);
				justiceCnt++;
			}
			if (smiteKillStack % 500 == 0 && bAngelic)
			{
				SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->SetHealing();
			}
		}
	}
	void SkillManager::IntheWind()
	{
		if (intheWindStack < 4)
		{
			intheWindTime += Time::DeltaTime();

			if (intheWindTime >= 10)
			{
				intheWindStack++;

				for (size_t i = 0; i < SceneManager::GetPlayScene()->GetBullet().size(); i++)
				{
					SceneManager::GetPlayScene()->GetBullet()[i]->GetScript<BulletScript>()->SetDamageInc(0.1f);
				}
				SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.1f);
				intheWindTime = 0.0f;
			}
		}
	}
	void SkillManager::IntheWindReset()
	{
		if (intheWindStack == 0)
			return;

		for (size_t i = 0; i < intheWindStack; i++)
		{
			for (size_t j = 0; j < SceneManager::GetPlayScene()->GetBullet().size(); j++)
			{
				SceneManager::GetPlayScene()->GetBullet()[i]->GetScript<BulletScript>()->SetDamageDec(0.1f);
			}

			SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->SetSpeedRed(0.1f);
		}

		intheWindStack = 0;
		intheWindTime = 0.0f;
	}
	void SkillManager::GameReset()
	{
		smiteKillStack = 0;
		justiceCnt = 0;
		bShieldOn = false;
		bShield = false;
		bJustice = false;
		bAngelic = false;
		bDivineBlessing = false;
		bIntheWind = false;
		bAgedDragon = false;
		bTrainedDragon = false;
		shieldOnTime = 120;
		intheWindTime = 0;
		intheWindStack = 0;
		trainedDragonStack = 0;
		AgedDragonTime = 0.0f;
		trainedDragonTime = 0.0f;
	}
}