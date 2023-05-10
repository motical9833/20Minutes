#include "yaGhostBullet.h"
#include "yaGameObject.h"
#include "yaMonsterScript.h"
#include "yaTime.h"


namespace ya
{
	GhostBullet::GhostBullet()
		:mDamage(10)
		, mSpeed(4.0f)
		, mTime(0.0f)
		, mDamageMul(1.0f)
		, mDir{}
		, bTargetMouse(false)
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
		if (bTargetMouse)
			TargetMouse();
		else
			TargetMonster();
	}
	void GhostBullet::Render()
	{

	}
	void GhostBullet::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			Vector3 a = collider->GetOwner()->GetComponent<Transform>()->GetPosition();

			int	damage = (mDamage * mDamageMul) + 1;

			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(damage);
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
		GetOwner()->GetComponent<Transform>()->SetScale(Vector3(2.0f,2.0f,1.0f));
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
	}
	void GhostBullet::GameReset()
	{
		mTime = 0;
		mSpeed = 5;
		mDamage = 10;
		mDamageMul = 1.0f;
		bTargetMouse = false;
		GetOwner()->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
	}
	void GhostBullet::TargetMouse()
	{
		mTime += Time::DeltaTime();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (mTime >= 5.0f)
		{
			GetOwner()->Death();
			Reset();
		}

		pos += GetOwner()->GetComponent<Transform>()->Right() * mSpeed * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
	}
	void GhostBullet::TargetMonster()
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
}