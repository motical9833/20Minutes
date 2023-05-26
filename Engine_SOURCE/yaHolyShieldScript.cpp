#include "yaHolyShieldScript.h"
#include "yaAnimator.h"
#include "yaGameObject.h"
#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaPlayerScript.h"
#include "yaWeaponScript.h"
#include "yaColliderCheckScript.h"
#include "yaSkillManager.h"
#include "yaTime.h"
#include "yaExpBarScript.h"

namespace ya
{
	HolyShieldScript::HolyShieldScript()
		:player{}
		,rotTime(0.0f)
		, bDivinWrath(false)
	{

	}
	HolyShieldScript::~HolyShieldScript()
	{

	}
	void HolyShieldScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"HolyShieldBreak") = std::bind(&HolyShieldScript::End, this);
	}
	void HolyShieldScript::Update()
	{
		DivineWrath();
	}
	void HolyShieldScript::Render()
	{

	}
	void HolyShieldScript::OnCollisionEnter(Collider2D* collider)
	{
		
	}
	void HolyShieldScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void HolyShieldScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void HolyShieldScript::DivineBlessing()
	{
		SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->SetSpeedMul(0.25f);
		SceneManager::GetPlayScene()->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeMul(0.25f);
		SceneManager::GetPlayScene()->GetReloadUI()[1]->GetScript<ExpBarScript>()->SetReloadUITimeMul(0.25f);
	}
	void HolyShieldScript::DivineWrath()
	{
		if (bDivinWrath)
		{
			divinWrathTime += Time::DeltaTime();


			if (divinWrathTime >= 1.0f)
			{
				Vector3 pos = SceneManager::GetPlayScene()->GetColliderChack()->GetScript<ColliderCheckScript>()->GetMonsterPos();

				SceneManager::GetPlayScene()->GetColliderChack()->GetScript<SkillManager>()->ThunderEnchant(pos + +Vector3(0.0f, 2.0f, 0.0f));
				divinWrathTime = 0.0f;
			}
		}
	}
	void HolyShieldScript::StalwartShield()
	{
		SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->SetShieldOnTime(60);
	}
	void HolyShieldScript::Start()
	{

	}
	void HolyShieldScript::Action()
	{

	}
	void HolyShieldScript::End()
	{
		GetOwner()->Death();

		Animator* ani = GetOwner()->GetComponent<Animator>();

		ani->Play(L"HolyShieldIdle", true);
	}
	void HolyShieldScript::GameReset()
	{
		bDivinWrath = false;
	}
	void HolyShieldScript::Break()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"HolyShieldBreak", false);

		SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->SetSpeedRed(0.25f);
		SceneManager::GetPlayScene()->GetWeapon()->GetScript<WeaponScript>()->SetReloadTimeRed(0.25f);
		SceneManager::GetPlayScene()->GetReloadUI()[1]->GetScript<ExpBarScript>()->SetReloadUITimeRed(0.25f);

	}
}