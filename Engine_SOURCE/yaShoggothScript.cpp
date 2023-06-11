#include "yaShoggothScript.h"
#include "yaGameObject.h"
#include "yaPlayerScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaAnimator.h"
#include "yaTime.h"

#define monsterSpeed 2

namespace ya
{
	ShoggothScript::ShoggothScript()
		:attackPos{}
		, mCoolTime(1.0f)
		, bAttack(false)
	{
	}
	ShoggothScript::ShoggothScript(int hp)
		:MonsterScript(hp)
		, mCoolTime(1.0f)
		, bAttack(false)
	{
	}
	ShoggothScript::~ShoggothScript()
	{
	}
	void ShoggothScript::Initalize()
	{
		animator = GetOwner()->GetComponent<Animator>();
		mColliderSize = GetOwner()->GetComponent<Collider2D>()->GetSize();
	}
	void ShoggothScript::Update()
	{
		mTime += Time::DeltaTime();

		if (SceneManager::GetPlayScene()->GetUIOn())
			return;

		if (bFreeze && bAttack == false)
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
				animator->PlayAgain();
			}
		}
		else
		{
			switch (state)
			{
			case ya::ShoggothScript::States::MOVE:
				Move();
				break;
			case ya::ShoggothScript::States::CHARGE:
				Charge();
				break;
			case ya::ShoggothScript::States::ATTACK:
				Attack();
				break;
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
	void ShoggothScript::FixedUpdate()
	{

	}
	void ShoggothScript::Render()
	{

	}
	void ShoggothScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			collider->GetOwner()->GetScript<PlayerScript>()->TakeDamage(mDamage);
			ClashwithPlayer();
		}
	}
	void ShoggothScript::OnCollisionStay(Collider2D* collider)
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
	void ShoggothScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void ShoggothScript::ChargeEnd()
	{

	}
	void ShoggothScript::AttackEnd()
	{

	}
	void ShoggothScript::DieMonster()
	{

	}
	void ShoggothScript::Idle()
	{

	}
	void ShoggothScript::Move()
	{

	}
	void ShoggothScript::Charge()
	{

	}
	void ShoggothScript::Attack()
	{

	}
}