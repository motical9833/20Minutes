#include "yaGhostBullet.h"
#include "yaGameObject.h"
#include "yaMonsterScript.h"
#include "yaTime.h"


namespace ya
{
	GhostBullet::GhostBullet()
		:mDamage(10)
		, mSpeed(5.0f)
		, mTime(0.0f)
		, mDir{}
	{

	}
	GhostBullet::~GhostBullet()
	{

	}
	void GhostBullet::Initalize()
	{

	}
	void GhostBullet::Update()
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
	void GhostBullet::Render()
	{

	}
	void GhostBullet::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage);
		}
	}
	void GhostBullet::OnCollisionStay(Collider2D* collider)
	{

	}
	void GhostBullet::OnCollisionExit(Collider2D* collider)
	{

	}
	void GhostBullet::Start()
	{

	}
	void GhostBullet::Action()
	{

	}
	void GhostBullet::End()
	{

	}
	void GhostBullet::TakeDamage(int damage)
	{

	}
	void GhostBullet::Reset()
	{
		mTime = 0;
		mSpeed = 5;
		mDamage = 10;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
	}
}