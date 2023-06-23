#include "yaHubNigguratScript.h"
#include "yaGameObject.h"
#include "yaPlayerScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaCurseScript.h"
#include "yaWeaponScript.h"
#include "yaReloadBarScript.h"
#include "yaMonsterFactoryScript.h"
#include "yaSkillManager.h"
#include "yaMonsterEyeLightScript.h"
#include "yaAudioSource.h"

#define monsterSpeed 2

namespace ya
{
	HubNigguratScript::HubNigguratScript()
		:attackPos{}
		, mCoolTime(0.0f)
		, bAttack(false)
	{

	}
	HubNigguratScript::HubNigguratScript(int hp)
		:MonsterScript(hp,eLayerType::Boss)
		, mCoolTime(0.0f)
		, bAttack(false)
	{

	}
	HubNigguratScript::~HubNigguratScript()
	{

	}
	void HubNigguratScript::Initalize()
	{
		animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"DeathAnimation") = std::bind(&HubNigguratScript::DieMonster, this);
		mColliderSize = GetOwner()->GetComponent<Collider2D>()->GetSize();

		animator->GetCompleteEvent(L"Boss_LeftCharge") = std::bind(&HubNigguratScript::ChargeEnd, this);
		animator->GetCompleteEvent(L"Boss_RightCharge") = std::bind(&HubNigguratScript::ChargeEnd, this);

		animator->GetCompleteEvent(L"Boss_LeftAttack") = std::bind(&HubNigguratScript::AttackEnd, this);
		animator->GetCompleteEvent(L"Boss_RightAttack") = std::bind(&HubNigguratScript::AttackEnd, this);

		animator->GetCompleteEvent(L"m_RightHit") = std::bind(&HubNigguratScript::HitEvent, this);
		animator->GetCompleteEvent(L"m_LeftHit") = std::bind(&HubNigguratScript::HitEvent, this);
	}
	void HubNigguratScript::Update()
	{
		if (SceneManager::GetPlayScene()->GetUIOn())
			return;

		if (bFreeze && bAttack == false)
		{
			mSpeed = 0;
			freezeTime += Time::DeltaTime();

			if (freezeTime >= 0.3f)
			{
				if (bFrostbite)
				{
					int damage = (mMaxHp / 15) + 1;
					TakeDamage(damage);
				}

				Transform* tr = GetOwner()->GetComponent<Transform>();
				tr->GetChiled(0)->GetOwner()->Death();
				bFreeze = false;
				freezeTime = 0;
				mSpeed = monsterSpeed;
				animator->PlayAgain();
			}
		}
		else
		{
			switch (state)
			{
			case ya::HubNigguratScript::States::MOVE:
				Move();
				break;
			case ya::HubNigguratScript::States::CHARGE:
				Charge();
				break;
			case ya::HubNigguratScript::States::ATTACK:
				Attack();
				break;
			}
		}

		if (bIgnition)
		{
			ignitionTime += Time::DeltaTime();

			if (ignitionTime >= 0.2f)
			{
				int damage = (mIgnitionDamage / 10) + 1;
				TakeDamage(damage);
				ignitionCnt++;
				ignitionTime = 0.0f;
				if (ignitionCnt >= 10)
				{
					mIgnitionDamage = 0;
					ignitionCnt = 0;
					bIgnition = false;
				}
			}
		}
	}
	void HubNigguratScript::FixedUpdate()
	{

	}
	void HubNigguratScript::Render()
	{

	}
	void HubNigguratScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			collider->GetOwner()->GetScript<PlayerScript>()->TakeDamage(mDamage);
			ClashwithPlayer();
		}
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Vector3 otherPos = collider->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 mPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		}
	}
	void HubNigguratScript::OnCollisionStay(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Vector3 otherPos = collider->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

			if (mPos.x - otherPos.x < -0.001f)
			{
				mPos.x -= 0.01f;
				GetOwner()->GetComponent<Transform>()->SetPosition(mPos);
			}
			else if (mPos.x - otherPos.x > 0.001f)
			{
				mPos.x += 0.01f;
				GetOwner()->GetComponent<Transform>()->SetPosition(mPos);
			}
			else if (mPos.y - otherPos.y > 0.001f)
			{
				mPos.y += 0.01f;
			}
			else if (mPos.y - otherPos.y < -0.001f)
			{
				mPos.y -= 0.01f;
			}
		}
	}
	void HubNigguratScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void HubNigguratScript::TakeDamage(int damage)
	{
		//if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->AnimationName() == L"Boss_RightMove")
		//{
		//	GetOwner()->GetComponent<Animator>()->Play(L"m_RightHit", false);
		//	GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetRightHit();
		//}
		//else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->AnimationName() == L"Boss_LeftMove")
		//{
		//	GetOwner()->GetComponent<Animator>()->Play(L"m_LeftHit", false);
		//	GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetLeftHit();
		//}

		//mSpeed = 0;

		if (bCurseActivate)
		{
			bCurseActivate = false;
			beCursed = false;
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(1)->GetOwner()->GetScript<CurseScript>()->Reset();

			if (mCurrentHp == NULL)
				return;

			mCurrentHp -= damage * curseMul;
			RitualStack();
			DieChack();
		}
		else
		{
			if (mCurrentHp == NULL)
				return;

			if (beCursed)
			{
				mCurrentHp -= damage * 1.1f + 1;
			}
			else
			{
				mCurrentHp -= damage;
			}

			DieChack();
		}
	}
	void HubNigguratScript::TakeDamage(int damage, eLayerType type)
	{
		if (bCurseActivate)
		{
			bCurseActivate = false;
			beCursed = false;
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(1)->GetOwner()->GetScript<CurseScript>()->Reset();

			if (mCurrentHp == NULL)
				return;

			mCurrentHp -= damage * curseMul;
			RitualStack();
			DieChack(type);
		}
		else
		{
			if (mCurrentHp == NULL)
				return;

			if (beCursed)
			{
				mCurrentHp -= damage * 1.3f + 1;
			}
			else
			{
				mCurrentHp -= damage;
			}

			DieChack(type);
		}
	}
	void HubNigguratScript::DieChack()
	{
		if (mCurrentHp <= 0)
		{
			SceneManager::GetPlayScene()->GetMonsterFactory()->GetScript<MonsterFactoryScript>()->CurrentMonsterCntDec();
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->Death();
			DropExpMarble();
			Animator* ani = GetOwner()->GetComponent<Animator>();
			GetOwner()->GetComponent<Collider2D>()->SetScriptOff(true);
			ani->Play(L"DeathAnimation", false);
			GetOwner()->SetLayerType(eLayerType::None);
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(0)->GetOwner()->Death();
			tr->GetChiled(1)->GetOwner()->GetScript<CurseScript>()->Reset();
			DeadEvent();
			SceneManager::GetPlayScene()->GetMonsterFactory()->GetScript<MonsterFactoryScript>()->SetBossDead();

			if (bKillClip)
			{
				SceneManager::GetPlayScene()->GetWeapon()->GetScript<WeaponScript>()->SetKillCntInc();
				SceneManager::GetPlayScene()->GetReloadUI()[1]->GetScript<ReloadBarScript>()->SetKillClip(0.15f);
			}

			if (bDieBullet)
			{
				DieBullet();
			}
		}
	}
	void HubNigguratScript::DieChack(eLayerType type)
	{
		if (mCurrentHp <= 0 && GetOwner()->GetComponent<Transform>()->GetChiled(0)->GetOwner()->GetState() != GameObject::Dead)
		{
			SceneManager::GetPlayScene()->GetMonsterFactory()->GetScript<MonsterFactoryScript>()->CurrentMonsterCntDec();
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->Death();
			DropExpMarble();
			Animator* ani = GetOwner()->GetComponent<Animator>();
			GetOwner()->GetComponent<Collider2D>()->SetScriptOff(true);
			GetOwner()->SetLayerType(eLayerType::None);
			ani->Play(L"DeathAnimation", false);
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(0)->GetOwner()->Death();
			tr->GetChiled(1)->GetOwner()->GetScript<CurseScript>()->Reset();
			DeadEvent();

			if (bKillClip)
			{
				SceneManager::GetPlayScene()->GetWeapon()->GetScript<WeaponScript>()->SetKillCntInc();
				SceneManager::GetPlayScene()->GetReloadUI()[1]->GetScript<ReloadBarScript>()->SetKillClip(0.15f);
			}

			if (type == eLayerType::Skill_Smite)
				SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->SmiteKillCnt();

			if (bDieBullet)
			{
				DieBullet();
			}
		}
	}
	void HubNigguratScript::ChargeEnd()
	{
		Animation* ani = animator->GetActiveAnimation();
		attackPos = player->GetComponent<Transform>()->GetPosition();

		SceneManager::GetPlayScene()->GetSoundObjects(10)->GetComponent<AudioSource>()->Play();
		state = States::ATTACK;

		if (ani->AnimationName() == L"Boss_RightCharge")
		{
			animator->Play(L"Boss_RightAttack", false);
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetRightAttack();
		}
		else if (ani->AnimationName() == L"Boss_LeftCharge")
		{
			animator->Play(L"Boss_LeftAttack", false);
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetLeftAttack();
		}

		bAttack = true;

		mSpeed = monsterSpeed * 5;
	}
	void HubNigguratScript::AttackEnd()
	{
		Animation* ani = animator->GetActiveAnimation();

		mSpeed = monsterSpeed;

		if (GetOwner()->GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x)
		{
			animator->Play(L"Boss_RightMove", true);
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetRight();
		}
		else if (GetOwner()->GetComponent<Transform>()->GetPosition().x > player->GetComponent<Transform>()->GetPosition().x)
		{
			animator->Play(L"Boss_LeftMove", true);
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetLeft();
		}

		bAttack = false;
	}
	void HubNigguratScript::DieMonster()
	{

	}
	void HubNigguratScript::Idle()
	{

	}
	void HubNigguratScript::Move()
	{
		mCoolTime += Time::DeltaTime();

		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		Animation* ani = animator->GetActiveAnimation();

		if (GetOwner()->GetComponent<Transform>()->GetPosition().x > player->GetComponent<Transform>()->GetPosition().x && ani->AnimationName() == L"Boss_RightMove")
		{
			animator->Play(L"Boss_LeftMove", true);
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetLeft();
		}
		else if (GetOwner()->GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x && ani->AnimationName() == L"Boss_LeftMove")
		{
			animator->Play(L"Boss_RightMove", true);
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetRight();
		}

		if (bClash)
		{
			clashTime += Time::DeltaTime();

			GetDIr();

			pos.x -= mDir.x * mSpeed * Time::DeltaTime();
			pos.y -= mDir.y * mSpeed * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (clashTime >= 0.1f)
			{
				bClash = false;
				mSpeed = monsterSpeed;
				clashTime = 0.0f;
			}
		}
		else
		{
			GetDIr();

			pos.x += mDir.x * mSpeed * Time::DeltaTime();
			pos.y += mDir.y * mSpeed * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}
		if(Distance(pos,player->GetComponent<Transform>()->GetPosition()) <= 7.0f && mCoolTime >= 1.5f)
		{
			mCoolTime = 0;

			if (ani->AnimationName() == L"Boss_RightMove" || ani->AnimationName() == L"Boss_RightHit")
			{
				animator->Play(L"Boss_RightCharge", false);
				GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetRightCharge();
				SceneManager::GetPlayScene()->GetSoundObjects(11)->GetComponent<AudioSource>()->Play();
			}
			else if (ani->AnimationName() == L"Boss_LeftMove" || ani->AnimationName() == L"Boss_LeftHit")
			{
				animator->Play(L"Boss_LeftCharge", false);
				SceneManager::GetPlayScene()->GetSoundObjects(11)->GetComponent<AudioSource>()->Play();
				GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetLeftCharge();
			}

			state = States::CHARGE;
		}

	}
	void HubNigguratScript::Charge()
	{
		if (bFreeze)
		{
			mSpeed = 0;
			freezeTime += Time::DeltaTime();

			if (freezeTime >= 3.0f)
			{
				if (bFrostbite)
				{
					int damage = (mMaxHp / 15) + 1;
					TakeDamage(damage);
				}

				Transform* tr = GetOwner()->GetComponent<Transform>();
				tr->GetChiled(0)->GetOwner()->Death();
				bFreeze = false;
				freezeTime = 0;
				mSpeed = monsterSpeed;
			}
		}

		if (bIgnition)
		{
			ignitionTime += Time::DeltaTime();

			if (ignitionTime >= 0.2f)
			{
				int damage = (mIgnitionDamage / 10) + 1;
				TakeDamage(damage);
				ignitionCnt++;
				ignitionTime = 0.0f;
				if (ignitionCnt >= 10)
				{
					mIgnitionDamage = 0;
					ignitionCnt = 0;
					bIgnition = false;
				}
			}
		}
	}
	void HubNigguratScript::Attack()
	{
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		TargetPosMove(attackPos);

		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		pos.y += mDir.y * mSpeed * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);

		if (Distance(pos, attackPos) <= 0.1f)
		{
			mSpeed = monsterSpeed;	
			state = States::MOVE;
		}
	}
	void HubNigguratScript::HitEvent()
	{
		//if (GetOwner()->GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x)
		//{
		//	animator->Play(L"Boss_RightMove", true);
		//	GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetRight();
		//}
		//else if (GetOwner()->GetComponent<Transform>()->GetPosition().x > player->GetComponent<Transform>()->GetPosition().x)
		//{
		//	animator->Play(L"Boss_LeftMove", true);
		//	GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetLeft();
		//}

		mSpeed = monsterSpeed;
	}
	void HubNigguratScript::Respawn()
	{
		GetOwner()->GetComponent<Collider2D>()->SetSize(mColliderSize);
		Animator* ani = GetOwner()->GetComponent<Animator>();
		GetOwner()->Life();
		mSpeed = monsterSpeed;
		ani->Play(L"Boss_RightMove", true);
		this->GetOwner()->GetComponent<Collider2D>()->SetScriptOff(false);
		GetOwner()->SetLayerType(mLayer);
		GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->Life();
		GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetComponent<Animator>()->Play(L"m_Right", true);
	}
	void HubNigguratScript::GameReset()
	{
		Respawn();
		bFreeze = false;
		bFrostbite = false;
		bCurseActivate = false;
		beCursed = false;
		freezeTime = 0.0f;
		bDieBullet = false;
		curseMul = 2.0f;
		bWitherOn = false;
		bRitualOn = false;
		bIgnition = false;
		ignitionCnt = 0;
		ignitionMaxCnt = 10;
	}
	void HubNigguratScript::GameEnd()
	{
		SceneManager::GetPlayScene()->SurvivalEndUIOn();
	}
	void HubNigguratScript::DeadEvent()
	{
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetBrainMonsters().size(); i++)
		{
			SceneManager::GetPlayScene()->GetBrainMonsters()[i]->GetScript<MonsterScript>()->BossDead();
		}
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetBoomerMonsters().size(); i++)
		{
			SceneManager::GetPlayScene()->GetBoomerMonsters()[i]->GetScript<MonsterScript>()->BossDead();
		}
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetEyeMonsters().size(); i++)
		{
			SceneManager::GetPlayScene()->GetEyeMonsters()[i]->GetScript<MonsterScript>()->BossDead();
		}
		for (size_t i = 0; i < SceneManager::GetPlayScene()->getBigBoomerMonsters().size(); i++)
		{
			SceneManager::GetPlayScene()->getBigBoomerMonsters()[i]->GetScript<MonsterScript>()->BossDead();
		}
	}
}