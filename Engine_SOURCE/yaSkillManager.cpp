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

namespace ya
{
	SkillManager::SkillManager()
		: bShieldOn(false)
		, bShield(false)
		, shieldTime(0.0f)
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

				if (shieldTime > 30)
				{
					HolyShield();
					bShield = true;
					bShieldOn = false;
					shieldTime = 0;
				}
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

		for (size_t i = 0; i < 20; i++)
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
		for (size_t i = 0; i < 20; i++)
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
		for (size_t i = 0; i < 20; i++)
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
		for (size_t i = 0; i < 30; i++)
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
	}
	void SkillManager::DragonFIre(Vector3 pos, Vector3 dir)
	{
		for (size_t i = 0; i < 20; i++)
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
}