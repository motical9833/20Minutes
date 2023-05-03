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

namespace ya
{
	MonsterScript::MonsterScript()
		:mCurrentHp(NULL)
		, mMaxHp(NULL)
		, mSpeed(NULL)
		, mDamage(1)
		, mColliderSize{}
		, bFreeze(false)
		, bCurse(false)
		, freezeTime(0.0f)
		, bDieBullet(false)
		, bKillClip(false)
	{

	}
	MonsterScript::MonsterScript(int hp)
		:mCurrentHp(hp)
		,mMaxHp(hp)
		,mSpeed(5)
		,mDamage(1)
		,mColliderSize{}
		, bFreeze(false)
		, bCurse(false)
		, freezeTime(0.0f)
		, bDieBullet(false)
		, bKillClip(false)
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
		if (bFreeze)
		{
			mSpeed = 0;
			freezeTime += Time::DeltaTime();

			if (freezeTime >= 3.0f)
			{
				Transform* tr = GetOwner()->GetComponent<Transform>();
				tr->GetChiled(0)->GetOwner()->Death();
				bFreeze = false;
				freezeTime = 0;
				mSpeed = 5;
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
		if (bCurse)
		{
			bCurse = false;
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(1)->GetOwner()->GetScript<CurseScript>()->Reset();
			this->TakeDamage(mDamage);
		}

		if (mCurrentHp == NULL)
			return;

		mCurrentHp -= damage;

		if (mCurrentHp <= 0)
		{
			Animator* ani = GetOwner()->GetComponent<Animator>();
			this->GetOwner()->GetComponent<Collider2D>()->SetScriptOff(true);
			this->GetOwner()->SetLayerType(eLayerType::None);
			ani->Play(L"DeathAnimation", false);
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(0)->GetOwner()->Death();
			tr->GetChiled(1)->GetOwner()->GetScript<CurseScript>()->Reset();

			if(bKillClip)
			SceneManager::GetPlayScene()->GetWeapon()->GetScript<WeaponScript>()->SetKillCntInc();

			if (bDieBullet)
			{
				DieBullet();
			}
		}
	}
	void MonsterScript::Respawn()
	{
		GetOwner()->GetComponent<Collider2D>()->SetSize(mColliderSize);
		Animator* ani = GetOwner()->GetComponent<Animator>();
		mCurrentHp = mMaxHp;
		this->GetOwner()->Life();
		mSpeed = 5;
		ani->Play(L"m_Right", true);
		this->GetOwner()->GetComponent<Collider2D>()->SetScriptOff(false);
		this->GetOwner()->SetLayerType(eLayerType::Monster);
	}
	void MonsterScript::GameReset()
	{
		Respawn();
		bFreeze = false;
		bCurse = false;
		freezeTime = 0.0f;
		bDieBullet = false;

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

			//SceneManager::GetPlayScene()->GetBullet()[i]->GetScript<BulletScript>()->Reset();
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
}