#include "yaSkillManager.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "GaleScript.h"
#include "yaTime.h"
#include "yaPlayerScript.h"
#include "yaHolyShieldScript.h"
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
	void SkillManager::HolyShield()
	{
		GameObject* shield = SceneManager::GetPlayScene()->GetShield();
		shield->Life();
		SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->ShieldOn();
	}
	void SkillManager::HolyShieldBreak()
	{
		bShieldOn = true;
		bShield = false;
		//SceneManager::GetPlayScene()->GetShield()->Death();
		SceneManager::GetPlayScene()->GetShield()->GetScript<HolyShieldScript>()->Break();
	}
}