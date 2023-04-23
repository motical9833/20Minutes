#include "yaDragonFireScript.h"
#include "yaGameObject.h"
#include "yaMonsterScript.h"
#include "yaTime.h"

namespace ya
{
	DragonFireScript::DragonFireScript()
		:mDamage(10)
		, mSpeed(5.0f)
		, mTime(0.0f)
		, mDir{}
	{

	}
	DragonFireScript::~DragonFireScript()
	{

	}
	void DragonFireScript::Initalize()
	{

	}
	void DragonFireScript::Update()
	{
		mTime += Time::DeltaTime();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (mTime >= 5.0f)
		{
			GetOwner()->Death();
			Reset();
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
			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage);
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

	}
	void DragonFireScript::TakeDamage(int damage)
	{

	}
	void DragonFireScript::Reset()
	{
		mTime = 0;
		mSpeed = 5;
		mDamage = 10;
		GetOwner()->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
	}
}