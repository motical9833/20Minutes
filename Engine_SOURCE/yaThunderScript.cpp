#include "yaThunderScript.h"
#include "yaAnimator.h"
#include "yaGameObject.h"
#include "yaMonsterScript.h"
#include "yaWeaponScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTime.h"

namespace ya
{
	ThunderScript::ThunderScript()
		:mDamage(22)
		, bEnergized(false)
		, time(0.0f)
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

			if (bEnergized)
			{
				srand((unsigned int)std::time(NULL));

				int random = rand() & 100 + 1;

				if (random <= 20)
				{
					SceneManager::GetPlayScene()->GetWeapon()->GetScript<WeaponScript>()->BulletSupply(3);
				}
			}
		}
	}
	void ThunderScript::OnCollisionStay(Collider2D* collider)
	{
		int a = 0;
	}
	void ThunderScript::OnCollisionExit(Collider2D* collider)
	{
		int a = 0;
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
		this->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(1.0f, 5.0f, 1.0f));
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"ThunderAni", false);
		time = 0;
	}
	void ThunderScript::GameReset()
	{
		this->GetOwner()->Death();
		this->GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		this->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(1.0f, 5.0f, 1.0f));
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"ThunderAni", false);
		time = 0;
		bEnergized = false;
	}
}