#include "yaThunderScript.h"
#include "yaAnimator.h"
#include "yaGameObject.h"
#include "yaMonsterScript.h"

namespace ya
{
	ThunderScript::ThunderScript()
		:mDamage(10)
	{

	}
	ThunderScript::~ThunderScript()
	{

	}
	void ThunderScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"ThunderAni") = std::bind(&ThunderScript::End, this);

	}
	void ThunderScript::Update()
	{

	}
	void ThunderScript::Render()
	{

	}
	void ThunderScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage);
		}
	}
	void ThunderScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void ThunderScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void ThunderScript::Move()
	{

	}
	void ThunderScript::Start()
	{

	}
	void ThunderScript::Action()
	{

	}
	void ThunderScript::End()
	{
		Reset();
	}
	void ThunderScript::Reset()
	{
		this->GetOwner()->Death();
		this->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"ThunderAni", false);
	}
}