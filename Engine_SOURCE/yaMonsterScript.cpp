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
#include "yaReloadBarScript.h"
#include "yaMonsterFactoryScript.h"
#include "yaConstantBuffer.h"
#include "yaRenderer.h"
#include "yaAudioSource.h"
#include "yaMonsterEyeLightScript.h"
#include "yaSoundObjectScript.h"

#define monsterSpeed 1.7f

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
		, clashTime(0.0f)
		, bDieBullet(false)
		, bKillClip(false)
		, bRitualOn(false)
		, bIgnition(false)
		, bClash(false)
		, curseMul(2.0f)
		, mTime(0.0f)
		, ignitionCnt(0)
		, ignitionMaxCnt(10)
		, mDir{}
		, player(nullptr)
	{

	}
	MonsterScript::MonsterScript(int hp,eLayerType layer)
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
		, clashTime(0.0f)
		, bDieBullet(false)
		, bKillClip(false)
		, bRitualOn(false)
		, bIgnition(false)
		, bClash(false)
		, curseMul(2.0f)
		, mTime(0.0f)
		, ignitionCnt(0)
		, ignitionMaxCnt(10)
		, mDir{}
		, player(nullptr)
		, mLayer(layer)
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

		if (GetOwner()->GetLayerType() == eLayerType::Tree)
			return;

		animator->GetCompleteEvent(L"m_RightHit") = std::bind(&MonsterScript::HitEvent, this);
		animator->GetCompleteEvent(L"m_LeftHit") = std::bind(&MonsterScript::HitEvent, this);
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

				if (GetOwner()->GetComponent<Transform>()->GetPosition().x > player->GetComponent<Transform>()->GetPosition().x
					&& GetOwner()->GetLayerType() != eLayerType::Tree)
				{
					animator->Play(L"m_Left", true);
					GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetLeft();
				}
				else if (GetOwner()->GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x
					&& GetOwner()->GetLayerType() != eLayerType::Tree)
				{
					animator->Play(L"m_Right", true);
					GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetRight();
				}

				animator->PlayAgain();
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
			if (GetOwner()->GetComponent<Transform>()->GetPosition().x > player->GetComponent<Transform>()->GetPosition().x 
				&& ani->AnimationName() == L"m_Right"
				&& GetOwner()->GetLayerType() != eLayerType::Tree)
			{
				animator->Play(L"m_Left",true);
				GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetScript<MonsterEyeLightScript>()->SetLeft();
			}
			else if (GetOwner()->GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x 
				&& ani->AnimationName() == L"m_Left" 
				&& GetOwner()->GetLayerType() != eLayerType::Tree)
			{
				animator->Play(L"m_Right", true);
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
			ClashwithPlayer();
		}
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Vector3 otherPos = collider->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 mPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		}
	}
	void MonsterScript::OnCollisionStay(Collider2D* collider)
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
		this->GetOwner()->Death();
	}
	void MonsterScript::TakeDamage(int damage)
	{
		mSpeed = 0;

		if (GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->AnimationName() == L"m_Right")
				GetOwner()->GetComponent<Animator>()->Play(L"m_RightHit", false);
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->AnimationName() == L"m_Left")
				GetOwner()->GetComponent<Animator>()->Play(L"m_LeftHit", false);
		}

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
		mSpeed = 0;

		if (GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->AnimationName() == L"m_Right")
				GetOwner()->GetComponent<Animator>()->Play(L"m_RightHit", false);
			else if (GetOwner()->GetComponent<Animator>()->GetActiveAnimation()->AnimationName() == L"m_Left")
				GetOwner()->GetComponent<Animator>()->Play(L"m_LeftHit", false);
		}

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
		GetOwner()->SetLayerType(mLayer);

		if (GetOwner()->GetLayerType() != eLayerType::Tree)
		{
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->Life();
			GetOwner()->GetComponent<Transform>()->GetChiled(2)->GetOwner()->GetComponent<Animator>()->Play(L"m_Right", true);
		}
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


			if (mLayer == eLayerType::MonsterBoomer)
			{
				for (size_t i = 0; i < SceneManager::GetPlayScene()->GetBoomerExplosions().size(); i++)
				{
					if (SceneManager::GetPlayScene()->GetBoomerExplosions()[i]->IsDead() == false)
						continue;

					SceneManager::GetPlayScene()->GetBoomerExplosions()[i]->Life();
					SceneManager::GetPlayScene()->GetBoomerExplosions()[i]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
					SceneManager::GetPlayScene()->GetBoomerSound()[i]->GetScript<SoundObjectScript>()->ObjectOn();
					break;
				}
			}

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
	void MonsterScript::DieChack(eLayerType type)
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

			if (mLayer == eLayerType::MonsterBoomer)
			{
				for (size_t i = 0; i < SceneManager::GetPlayScene()->GetBoomerExplosions().size(); i++)
				{
					if (SceneManager::GetPlayScene()->GetBoomerExplosions()[i]->IsDead() == false)
						continue;

					SceneManager::GetPlayScene()->GetBoomerExplosions()[i]->Life();
					SceneManager::GetPlayScene()->GetBoomerExplosions()[i]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
					SceneManager::GetPlayScene()->GetBoomerSound()[i]->GetScript<SoundObjectScript>()->ObjectOn();

					break;
				}
			}


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
	void MonsterScript::Freeze()
	{
		bFreeze = true;
		animator->Pause();
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
			SceneManager::GetPlayScene()->GetBullet()[i]->GetComponent<Animator>()->ResetStop();
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
	void MonsterScript::TargetPosMove(Vector3 targetPos)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 a = tr->GetPosition();

		Vector3 dir = targetPos - a;

		Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

		double value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2)); //피타고라스 R값

		Vector3 dirValue = Vector3(fabsDir.x / value, fabsDir.y / value, 0);

		mDir = dirValue;
	}
	float MonsterScript::Distance(Vector3 myPos,Vector3 targetPos)
	{
		Vector3 dir = targetPos - myPos;

		Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

		float value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2)); //피타고라스 R값

		return value;
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
	void MonsterScript::ClashwithPlayer()
	{
		if (mCurrentHp == NULL)
			return;

		bClash = true;
		mSpeed = 15.0f;
	}
	void MonsterScript::HitEvent()
	{
		if (GetOwner()->GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x)
		{
			animator->Play(L"m_Right", true);
		}
		else if (GetOwner()->GetComponent<Transform>()->GetPosition().x > player->GetComponent<Transform>()->GetPosition().x)
		{
			animator->Play(L"m_Left", true);
		}

		mSpeed = monsterSpeed;
	}
}