#include "GaleScript.h"
#include "yaTime.h"
#include "yaGameObject.h"
#include "yaMonsterScript.h"

namespace ya
{
	GaleScript::GaleScript()
		:mDamage(10)
		,mSpeed(7.0f)
		,mTime(0.0f)
		,mDir{}
	{

	}
	GaleScript::~GaleScript()
	{

	}
	void GaleScript::Initalize()
	{

	}
	void GaleScript::Update()
	{
		mTime += Time::DeltaTime();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (mTime >= 3.0f)
		{
			GetOwner()->Death();
			Reset();
		}

		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		pos.y += mDir.y * mSpeed * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
	}
	void GaleScript::Render()
	{

	}
	void GaleScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage);
		}
	}
	void GaleScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void GaleScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void GaleScript::Start()
	{

	}
	void GaleScript::Action()
	{

	}
	void GaleScript::End()
	{

	}
	void GaleScript::TakeDamage(int damage)
	{

	}
	void GaleScript::Reset()
	{
		mTime = 0;
		mSpeed = 7;
		mDamage = 10;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
	}
}