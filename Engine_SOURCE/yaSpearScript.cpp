#include "yaSpearScript.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaColliderCheckScript.h"
#include "yaMonsterScript.h"
#include "yaSkillManager.h"
#include "yaInput.h"
#include "yaPlayerScript.h"

namespace ya
{
	SpearScript::SpearScript(int cnt)
		:mSpeed(2.0f)
		, mFireSpeed(9.0f)
		, mWidth(1.1f)
		, mHeight(1.1f)
		, mTime(0.0f)
		, mAttackTime(0.0f)
		, mDamage(20)
		, value(cnt)
		, bAttack(false)
		, bHolySpear(false)
		, mDir{}
	{

	}
	SpearScript::~SpearScript()
	{

	}
	void SpearScript::Initalize()
	{

	}
	void SpearScript::Update()
	{
		Circularmotion();
		LookPayer();

		if (bAttack)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			mAttackTime += Time::DeltaTime();

			pos += GetOwner()->GetComponent<Transform>()->Up() * mFireSpeed * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (mAttackTime >= 3.0f)
			{
				mAttackTime = 0;
				bAttack = false;
			}
		}
	}
	void SpearScript::Render()
	{

	}
	void SpearScript::OnCollisionEnter(Collider2D* collider)
	{
		if (bAttack == false)
			return;



		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active && bHolySpear && bSoulKnight)
		{
			int maxHP = collider->GetOwner()->GetScript<MonsterScript>()->GetMaxHP() / 10 + 1;

			int damageUP = 3 * SceneManager::GetPlayScene()->GetPlayer()->GetScript<PlayerScript>()->GetMaxHP();

			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(damageUP + maxHP + mDamage);
		}
		else if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active && bHolySpear)
		{
			int maxHP = collider->GetOwner()->GetScript<MonsterScript>()->GetMaxHP() / 10 + 1;

			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(maxHP + mDamage);
		}
		else if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage);
		}

	}
	void SpearScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void SpearScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void SpearScript::Start()
	{

	}
	void SpearScript::Action()
	{

	}
	void SpearScript::End()
	{

	}
	void SpearScript::GameReset()
	{
		bHolySpear = false;
		bAttack = false;
	}

	void SpearScript::Attack()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();
		Vector3 dir = Input::GetMousePosition() - pos;

		dir.Normalize();

		this->SetDir(dir);
		bAttack = true;
	}

	void SpearScript::Circularmotion()
	{
		if (bAttack)
			return;

		mTime += Time::DeltaTime() * mSpeed;

		float x = (std::cos(mTime + value) * mWidth) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().x;
		float y = (std::sin(mTime + value) * mHeight) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().y;

		float z = 0;

		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(x, y, z));
	}
	void SpearScript::LookPayer()
	{
		if (bAttack)
			return;

		Transform* mTrans = GetOwner()->GetComponent<Transform>();


		Vector3 mPos = mTrans->GetPosition();
		Vector3 rot = mTrans->GetRotation();

		Vector3 playerPos = SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector3 mRot = mTrans->GetRotation();
		mRot.z = atan2(playerPos.y - mPos.y, playerPos.x - mPos.x);
		mTrans->SetRotation(mRot);
	}
}
