#include "yaSmiteScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaMonsterScript.h"

namespace ya
{
	SmiteScript::SmiteScript()
		:mDamage(20)
		, bHolyMightOn(false)
	{

	}
	SmiteScript::~SmiteScript()
	{

	}
	void SmiteScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		animator->GetCompleteEvent(L"Smite") = std::bind(&SmiteScript::End, this);
	}
	void SmiteScript::Update()
	{

	}
	void SmiteScript::Render()
	{

	}
	void SmiteScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			eLayerType type = GetOwner()->GetLayerType();
			if (bHolyMightOn)
			{
				int add = collider->GetOwner()->GetScript<MonsterScript>()->GetCurrentHP() / 20 + 1;
				collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage + add, type);
			}
			else
				collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage, type);
		}
	}
	void SmiteScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void SmiteScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void SmiteScript::Start()
	{

	}
	void SmiteScript::Action()
	{

	}
	void SmiteScript::End()
	{
		Reset();
	}
	void SmiteScript::Reset()
	{
		this->GetOwner()->Death();
		this->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"Smite", false);
	}
	void SmiteScript::GameReset()
	{
		this->GetOwner()->Death();
		this->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"Smite", false);
		bHolyMightOn = false;
	}
}