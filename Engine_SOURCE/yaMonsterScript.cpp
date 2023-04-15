#include "yaMonsterScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"

namespace ya
{
	MonsterScript::MonsterScript(int hp)
		:mCurrentHp(hp)
		,mMaxHp(hp)
		,mSpeed(5)
		,mColliderSize{}
	{
	}
	MonsterScript::~MonsterScript()
	{
	}
	void MonsterScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"DeathAnimation") = std::bind(&MonsterScript::End, this);

		mColliderSize = GetOwner()->GetComponent<Collider2D>()->GetSize();
	}
	void MonsterScript::Update()
	{
	}
	void MonsterScript::Render()
	{
	}
	void MonsterScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Bullet)
		{
			mCurrentHp--;

			if (mCurrentHp <= 0)
			{
				Animator* ani = GetOwner()->GetComponent<Animator>();
				this->GetOwner()->GetComponent<Collider2D>()->SetScriptOff(true);
				this->GetOwner()->SetLayerType(eLayerType::None);
				ani->Play(L"DeathAnimation", false);
			}
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
		mCurrentHp -= damage;

		if (mCurrentHp <= 0)
		{
			Animator* ani = GetOwner()->GetComponent<Animator>();
			ani->Play(L"DeathAnimation", false);
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
}