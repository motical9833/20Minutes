#include "GaleScript.h"
#include "yaTime.h"
#include "yaGameObject.h"
#include "yaMonsterScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaPlayerScript.h"

namespace ya
{
	GaleScript::GaleScript()
		:mDamage(10)
		,mSpeed(7.0f)
		,mTime(0.0f)
		,mEyeoftheTime(0.0f)
		,mDir{}
		, bWindBorne(false)
		, bEyeoftheStorm(false)
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

		mEyeoftheTime += Time::DeltaTime();

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
			if (bWindBorne)
			{
				float speedMul = SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->GetSpeedMul();

				int damage = (mDamage * speedMul) + 1;

				collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(damage);
			}
			else if (bEyeoftheStorm)
			{
				if (mEyeoftheTime <= 1)
				{
					collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage * 2);
				}
			}
			else if(bWindBorne && bEyeoftheStorm)
			{
				float speedMul = SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->GetSpeedMul();

				int damage = (mDamage * speedMul) + 1;

				if (mEyeoftheTime <= 1)
					collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(damage * 2);
				else
					collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(damage);
			}
			else
			{
				collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage);
			}
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
		mEyeoftheTime = 0.0f;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
	}
	void GaleScript::GameReset()
	{
		mTime = 0;
		mSpeed = 7;
		mDamage = 10;
		mEyeoftheTime = 0.0f;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
		bWindBorne = false;
		bEyeoftheStorm = false;
	}
}