#include "yaHubNigguratScript.h"
#include "yaGameObject.h"
#include "yaPlayerScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaAnimator.h"
#include "yaTime.h"

#define monsterSpeed 2

namespace ya
{
	HubNigguratScript::HubNigguratScript()
	{

	}
	HubNigguratScript::HubNigguratScript(int hp)
		:MonsterScript(hp)
	{

	}
	HubNigguratScript::~HubNigguratScript()
	{

	}
	void HubNigguratScript::Initalize()
	{
		animator = GetOwner()->GetComponent<Animator>();
		animator->GetCompleteEvent(L"DeathAnimation") = std::bind(&HubNigguratScript::DieMonster, this);
		mColliderSize = GetOwner()->GetComponent<Collider2D>()->GetSize();

	}
	void HubNigguratScript::Update()
	{
		mTime += Time::DeltaTime();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (SceneManager::GetPlayScene()->GetUIOn())
			return;

		if (bFreeze)
		{
			mSpeed = 0;
			freezeTime += Time::DeltaTime();

			if (freezeTime >= 3.0f)
			{
				if (bFrostbite)
				{
					int damage = (mMaxHp / 15) + 1;
					TakeDamage(damage);
				}

				Transform* tr = GetOwner()->GetComponent<Transform>();
				tr->GetChiled(0)->GetOwner()->Death();
				bFreeze = false;
				freezeTime = 0;
				mSpeed = monsterSpeed;
			}
		}
		else
		{
			Animation* ani = animator->GetActiveAnimation();
			int a = 0;
			if (GetOwner()->GetComponent<Transform>()->GetPosition().x > player->GetComponent<Transform>()->GetPosition().x && ani->AnimationName() == L"Boss_RightMove")
			{
				animator->Play(L"Boss_LeftMove", true);
			}
			else if (GetOwner()->GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x && ani->AnimationName() == L"Boss_LeftMove")
			{
				animator->Play(L"Boss_RightMove", true);
			}

			if (bClash)
			{
				clashTime += Time::DeltaTime();

				GetDIr();

				pos.x -= mDir.x * mSpeed * Time::DeltaTime();
				pos.y -= mDir.y * mSpeed * Time::DeltaTime();

				GetOwner()->GetComponent<Transform>()->SetPosition(pos);

				if (clashTime >= 0.1f)
				{
					bClash = false;
					mSpeed = monsterSpeed;
					clashTime = 0.0f;
				}
			}
			else
			{
				GetDIr();

				pos.x += mDir.x * mSpeed * Time::DeltaTime();
				pos.y += mDir.y * mSpeed * Time::DeltaTime();

				GetOwner()->GetComponent<Transform>()->SetPosition(pos);
			}
		}

		if (bIgnition)
		{
			ignitionTime += Time::DeltaTime();

			if (ignitionTime >= 0.2f)
			{
				int damage = (mIgnitionDamage / 10) + 1;
				TakeDamage(damage);
				ignitionCnt++;
				ignitionTime = 0.0f;
				if (ignitionCnt >= 10)
				{
					mIgnitionDamage = 0;
					ignitionCnt = 0;
					bIgnition = false;
				}
			}
		}
	}
	void HubNigguratScript::FixedUpdate()
	{

	}
	void HubNigguratScript::Render()
	{

	}
	void HubNigguratScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			collider->GetOwner()->GetScript<PlayerScript>()->TakeDamage(mDamage);
			ClashwithPlayer();
		}
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Vector3 otherPos = collider->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 mPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		}
	}
	void HubNigguratScript::OnCollisionStay(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			Vector3 otherPos = collider->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

			if (mPos.x - otherPos.x < -0.001f)
			{
				mPos.x -= 0.01f;
				GetOwner()->GetComponent<Transform>()->SetPosition(mPos);
			}
			else if (mPos.x - otherPos.x > 0.001f)
			{
				mPos.x += 0.01f;
				GetOwner()->GetComponent<Transform>()->SetPosition(mPos);
			}
			else if (mPos.y - otherPos.y > 0.001f)
			{
				mPos.y += 0.01f;
			}
			else if (mPos.y - otherPos.y < -0.001f)
			{
				mPos.y -= 0.01f;
			}
		}
	}
	void HubNigguratScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void HubNigguratScript::ChargeEnd()
	{

	}
	void HubNigguratScript::AttackEnd()
	{

	}
	void HubNigguratScript::DieMonster()
	{
	}
}