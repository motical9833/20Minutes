#include "yaDragonFireScript.h"
#include "yaGameObject.h"
#include "yaMonsterScript.h"
#include "yaAnimator.h"
#include "yaTime.h"

namespace ya
{
	DragonFireScript::DragonFireScript()
		:mDamage(10)
		, mSpeed(5.0f)
		, mTime(0.0f)
		, crashTime(0.0f)
		, mDamageMul(0.0f)
		, mDir{}
		, bCrash(false)
		, bDragonBond(false)
	{

	}
	DragonFireScript::~DragonFireScript()
	{

	}
	void DragonFireScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetEndEvent(L"BulletAni") = std::bind(&DragonFireScript::End, this);
	}
	void DragonFireScript::Update()
	{
		mTime += Time::DeltaTime();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (mTime >= 5.0f && bCrash == false)
		{
			GetOwner()->Death();
			Reset();
		}
		else if (bCrash)
		{
			crashTime += Time::DeltaTime();
			if (crashTime >= 0.01f)
			{
				Reset();
				this->GetOwner()->Death();
			}
		}

		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		pos.y += mDir.y * mSpeed * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
	}
	void DragonFireScript::Render()
	{

	}
	void DragonFireScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			int damage = mDamage;

			if (bDragonBond)
				damage = (mDamage * mDamageMul) + 1;

			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"BulletAni", false);
			animator->Start();

			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(damage);
		}
	}
	void DragonFireScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void DragonFireScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void DragonFireScript::Start()
	{

	}
	void DragonFireScript::Action()
	{

	}
	void DragonFireScript::End()
	{
		bCrash = true;
	}
	void DragonFireScript::TakeDamage(int damage)
	{

	}
	void DragonFireScript::Reset()
	{
		mTime = 0;
		mSpeed = 5;
		crashTime = 0.0f;
		GetOwner()->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
		bCrash = false;
	}
	void DragonFireScript::GameReset()
	{
		mTime = 0;
		mSpeed = 5;
		mDamage = 10;
		crashTime = 0.0f;
		GetOwner()->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
		bCrash = false;
	}
}