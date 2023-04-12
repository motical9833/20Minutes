#include "yaMonsterScript.h"
#include "yaGameObject.h"

namespace ya
{
	MonsterScript::MonsterScript(int hp)
		:mHp(hp)
		,mSpeed(5)
	{
	}
	MonsterScript::~MonsterScript()
	{
	}
	void MonsterScript::Initalize()
	{
	}
	void MonsterScript::Update()
	{
	}
	void MonsterScript::Render()
	{
	}
	void MonsterScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Bullet)
		{
			mHp--;

			if (mHp <= 0)
				this->GetOwner()->Death();
		}
	}
	void MonsterScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MonsterScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MonsterScript::Start()
	{
	}
	void MonsterScript::Action()
	{
	}
	void MonsterScript::End()
	{
	}
	void MonsterScript::HitBullet(int damage)
	{
		mHp -= damage;

		if (mHp <= 0)
		{
			this->GetOwner()->Death();
		}
	}
}