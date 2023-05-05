#include "yaIcicleScript.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaMonsterScript.h"

namespace ya
{
	IcicleScript::IcicleScript()
		:mSpeed(10.0f)
		,mTime(0.0f)
	{

	}
	IcicleScript::~IcicleScript()
	{

	}
	void IcicleScript::Initalize()
	{

	}
	void IcicleScript::Update()
	{
		mTime += Time::DeltaTime();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (mTime >= 3.0f)
		{
			GetOwner()->Death();
			Reset();
		}

		pos += GetOwner()->GetComponent<Transform>()->Right() * (mSpeed) * Time::DeltaTime();
		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
	}
	void IcicleScript::Render()
	{
	}
	void IcicleScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			collider->GetOwner()->GetScript<MonsterScript>()->Freeze();
			Reset();
		}
	}
	void IcicleScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void IcicleScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void IcicleScript::Start()
	{
	}
	void IcicleScript::Action()
	{
	}
	void IcicleScript::End()
	{
	}
	void IcicleScript::Reset()
	{
		mTime = 0.0f;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
		GetOwner()->Death();
	}
}