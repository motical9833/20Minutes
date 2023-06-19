#include "yaBommerSoundEffectScript.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaPlayerScript.h"
#include "yaMonsterScript.h"

namespace ya
{
	BommerSoundEffectScript::BommerSoundEffectScript()
		:mTime(0.0f)
	{

	}
	BommerSoundEffectScript::~BommerSoundEffectScript()
	{

	}
	void BommerSoundEffectScript::Initalize()
	{

	}
	void BommerSoundEffectScript::Update()
	{
		mTime += Time::DeltaTime();

		if (mTime > 0.5f)
		{
			GetOwner()->Death();
			mTime = 0.0f;
		}
	}
	void BommerSoundEffectScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			collider->GetOwner()->GetScript<PlayerScript>()->TakeDamage(1);
		}
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster || 
			collider->GetOwner()->GetLayerType() == eLayerType::MonsterBoomer|| 
			collider->GetOwner()->GetLayerType() == eLayerType::Boss)
		{
			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(40);
		}
	}
	void BommerSoundEffectScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void BommerSoundEffectScript::OnCollisionExit(Collider2D* collider)
	{

	}
}