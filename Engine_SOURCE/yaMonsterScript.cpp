#include "yaMonsterScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaPlayerScript.h"
#include "yaTime.h"
#include "yaCurseScript.h"
#include "yaPlayer.h"
#include "yaBulletScript.h"
#include "yaWeaponScript.h"
#include "yaSkillManager.h"
#include "yaExpBarScript.h"

#define monsterSpeed 0

namespace ya
{
	MonsterScript::MonsterScript()
		:mCurrentHp(NULL)
		, mMaxHp(NULL)
		, mSpeed(NULL)
		, mDamage(1)
		, mIgnitionDamage(0)
		, mColliderSize{}
		, bFreeze(false)
		, bFrostbite(false)
		, bCurseActivate(false)
		, bWitherOn(false)
		, freezeTime(0.0f)
		, ignitionTime(0.0f)
		, bDieBullet(false)
		, bKillClip(false)
		, bRitualOn(false)
		, bIgnition(false)
		, curseMul(2.0f)
		, mTime(0.0f)
		, ignitionCnt(0)
		, ignitionMaxCnt(10)
		, mDir{}
		, player(nullptr)
	{

	}
	MonsterScript::MonsterScript(int hp)
		: mCurrentHp(hp)
		, mMaxHp(hp)
		, mSpeed(monsterSpeed)
		, mDamage(1)
		, mIgnitionDamage(0)
		, mColliderSize{}
		, bFreeze(false)
		, bFrostbite(false)
		, bCurseActivate(false)
		, freezeTime(0.0f)
		, ignitionTime(0.0f)
		, bDieBullet(false)
		, bKillClip(false)
		, bRitualOn(false)
		, bIgnition(false)
		, curseMul(2.0f)
		, mTime(0.0f)
		, ignitionCnt(0)
		, ignitionMaxCnt(10)
		, mDir{}
		, player(nullptr)
	{
	}
	MonsterScript::~MonsterScript()
	{

	}
	void MonsterScript::Initalize()
	{

		animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"DeathAnimation") = std::bind(&MonsterScript::End, this);
		mColliderSize = GetOwner()->GetComponent<Collider2D>()->GetSize();

		player = SceneManager::GetPlayScene()->GetPlayer();
	}
	void MonsterScript::Update()
	{
		mTime += Time::DeltaTime();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (SceneManager::GetPlayScene()->GetUIOn())
			return;

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
		else
		{
			Animation* ani = animator->GetActiveAnimation();
			if (GetOwner()->GetComponent<Transform>()->GetPosition().x > player->GetComponent<Transform>()->GetPosition().x && ani->AnimationName() == L"m_Right")
			{
				animator->Play(L"m_Left",true);
			}
			else if (GetOwner()->GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x && ani->AnimationName() == L"m_Left")
			{
				animator->Play(L"m_Right", true);
			}

			GetDIr();

			pos.x += mDir.x * mSpeed * Time::DeltaTime();
			pos.y += mDir.y * mSpeed * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
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
	void MonsterScript::Render()
	{

	}
	void MonsterScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			collider->GetOwner()->GetScript<PlayerScript>()->TakeDamage(mDamage);
		}
	}
	void MonsterScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void MonsterScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void MonsterScript::Start()
	{

	}
	void MonsterScript::Action()
	{

	}
	void MonsterScript::End()
	{
		GetOwner()->GetComponent<Collider2D>()->SetSize(mColliderSize);
		mCurrentHp = mMaxHp;
		this->GetOwner()->Death();
	}
	void MonsterScript::TakeDamage(int damage)
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
			DieChack();
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

			DieChack();
		}
	}
	void MonsterScript::TakeDamage(int damage, eLayerType type)
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
	void MonsterScript::RitualStack()
	{
		if (mCurrentHp <= 0 && bRitualOn)
		{
			SceneManager::GetPlayScene()->GetWeapon()->GetScript<WeaponScript>()->SetRitualStack();
		}
	}
	void MonsterScript::Respawn()
	{
		GetOwner()->GetComponent<Collider2D>()->SetSize(mColliderSize);
		Animator* ani = GetOwner()->GetComponent<Animator>();
		mCurrentHp = mMaxHp;
		this->GetOwner()->Life();
		mSpeed = monsterSpeed;
		ani->Play(L"m_Right", true);
		this->GetOwner()->GetComponent<Collider2D>()->SetScriptOff(false);
		this->GetOwner()->SetLayerType(eLayerType::Monster);
	}
	void MonsterScript::GameReset()
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
	void MonsterScript::DieChack()
	{
		if (mCurrentHp <= 0)
		{
			DropExpMarble();
			Animator* ani = GetOwner()->GetComponent<Animator>();
			this->GetOwner()->GetComponent<Collider2D>()->SetScriptOff(true);
			this->GetOwner()->SetLayerType(eLayerType::None);
			ani->Play(L"DeathAnimation", false);
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(0)->GetOwner()->Death();
			tr->GetChiled(1)->GetOwner()->GetScript<CurseScript>()->Reset();

			if (bKillClip)
			{
				SceneManager::GetPlayScene()->GetWeapon()->GetScript<WeaponScript>()->SetKillCntInc();
				SceneManager::GetPlayScene()->GetReloadUI()[1]->GetScript<ExpBarScript>()->SetKillClip(0.15f);
			}

			if (bDieBullet)
			{
				DieBullet();
			}
		}
	}
	void MonsterScript::DieChack(eLayerType type)
	{
		if (mCurrentHp <= 0)
		{
			DropExpMarble();
			Animator* ani = GetOwner()->GetComponent<Animator>();
			this->GetOwner()->GetComponent<Collider2D>()->SetScriptOff(true);
			this->GetOwner()->SetLayerType(eLayerType::None);
			ani->Play(L"DeathAnimation", false);
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(0)->GetOwner()->Death();
			tr->GetChiled(1)->GetOwner()->GetScript<CurseScript>()->Reset();

			if (bKillClip)
			{
				SceneManager::GetPlayScene()->GetWeapon()->GetScript<WeaponScript>()->SetKillCntInc();
				SceneManager::GetPlayScene()->GetReloadUI()[1]->GetScript<ExpBarScript>()->SetKillClip(0.15f);
			}

			if (type == eLayerType::Skill_Smite)
				SceneManager::GetPlayScene()->GetSkillManager()->GetScript<SkillManager>()->SmiteKillCnt();

			if (bDieBullet)
			{
				DieBullet();
			}
		}
	}
	void MonsterScript::Freeze()
	{
		bFreeze = true;
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->GetChiled(0)->GetOwner()->Life();
		freezeTime = 0;
	}
	void MonsterScript::Curse()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->GetChiled(1)->GetOwner()->Life();

		if (bWitherOn)
			beCursed = true;
	}
	void MonsterScript::DieBullet()
	{
		int a = 1;

		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetBullet().size(); i++)
		{
			if(SceneManager::GetPlayScene()->GetBullet()[i]->IsDead() == false)
				continue;

			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 rot = Vector3(0.0f, 0.0f, 0.6f * a);

			SceneManager::GetPlayScene()->GetBullet()[i]->GetComponent<Transform>()->SetParent(nullptr);
			SceneManager::GetPlayScene()->GetBullet()[i]->GetComponent<Transform>()->SetPosition(pos);
			SceneManager::GetPlayScene()->GetBullet()[i]->GetScript<BulletScript>()->Setdir(rot);
			SceneManager::GetPlayScene()->GetBullet()[i]->GetScript<BulletScript>()->SetDieBulletOn();
			SceneManager::GetPlayScene()->GetBullet()[i]->GetComponent<Animator>()->Stop();
			SceneManager::GetPlayScene()->GetBullet()[i]->Life();
			a++;

			if (a > 11)
				break;
		}
	}
	void MonsterScript::Ignition(int damage)
	{
		mIgnitionDamage += damage;
		ignitionCnt = 0;
		ignitionTime = 0.0f;
		bIgnition = true;
	}
	void MonsterScript::GetDIr()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 a = tr->GetPosition();

		Vector3 b = SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();


		Vector3 dir = b - a;

		Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

		double value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2)); //피타고라스 R값

		Vector3 dirValue = Vector3(fabsDir.x / value, fabsDir.y / value, 0);

		mDir = dirValue;
	}
	void MonsterScript::DropExpMarble()
	{
		for (size_t i = 0; i < SceneManager::GetPlayScene()->GetExpMarble().size(); i++)
		{
			if (SceneManager::GetPlayScene()->GetExpMarble()[i]->IsDead() == false)
				continue;

			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			SceneManager::GetPlayScene()->GetExpMarble()[i]->GetComponent<Transform>()->SetPosition(pos);
			SceneManager::GetPlayScene()->GetExpMarble()[i]->Life();
			break;
		}
	}
}