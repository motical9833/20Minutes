#include "yaMonsterScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaPlayerScript.h"
#include "yaTime.h"
#include "yaCurseScript.h"

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
	{
	}
	MonsterScript::~MonsterScript()
	{
	}
	void MonsterScript::Initalize()
	{
		if (mMaxHp == NULL)
			return;

		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"DeathAnimation") = std::bind(&MonsterScript::End, this);
		mColliderSize = GetOwner()->GetComponent<Collider2D>()->GetSize();
	}
	void MonsterScript::Update()
	{
		if (bFreeze)
		{
			mSpeed = 0;
			freezeTime += Time::DeltaTime();

			if (freezeTime >= 1.0f)
			{
				Transform* tr = GetOwner()->GetComponent<Transform>();
				tr->GetChiled(0)->GetOwner()->Death();
				bFreeze = false;
				freezeTime = 0;
				mSpeed = 5;
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
		if (mCurrentHp == NULL)
			return;

		mCurrentHp -= damage;

		if (bCurse)
		{
			bCurse = false;
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(1)->GetOwner()->Death();
		}

		if (mCurrentHp <= 0)
		{
			Animator* ani = GetOwner()->GetComponent<Animator>();
			this->GetOwner()->GetComponent<Collider2D>()->SetScriptOff(true);
			this->GetOwner()->SetLayerType(eLayerType::None);
			ani->Play(L"DeathAnimation", false);
			Transform* tr = GetOwner()->GetComponent<Transform>();
			tr->GetChiled(0)->GetOwner()->Death();
		}
	}
	void MonsterScript::Reset()
	{
		GetOwner()->GetComponent<Collider2D>()->SetSize(mColliderSize);
		Animator* ani = GetOwner()->GetComponent<Animator>();
		mCurrentHp = mMaxHp;
		this->GetOwner()->Life();
		mSpeed = 5;
		ani->Play(L"m_Idle", true);
		this->GetOwner()->GetComponent<Collider2D>()->SetScriptOff(false);
		this->GetOwner()->SetLayerType(eLayerType::Monster);
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
}