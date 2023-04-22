#include "yaScytheScript.h"
#include "yaSceneManager.h"
#include "yaGameObject.h"
#include "yaPlayScene.h"
#include "yaMonsterScript.h"
#include "yaTime.h"

namespace ya
{
	ScytheScript::ScytheScript()
		:mSpeed(2.0f)
		, mWidth(1.5f)
		, mHeight(1.5f)
		, mTime(0.0f)
		, mDamage(20)
	{

	}
	ScytheScript::~ScytheScript()
	{

	}
	void ScytheScript::Initalize()
	{

	}
	void ScytheScript::Update()
	{
		Circularmotion();
	}
	void ScytheScript::Render()
	{

	}
	void ScytheScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			collider->GetOwner()->GetScript<MonsterScript>()->TakeDamage(mDamage);
		}
	}
	void ScytheScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void ScytheScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void ScytheScript::Start()
	{

	}
	void ScytheScript::Action()
	{

	}
	void ScytheScript::End()
	{

	}
	void ScytheScript::Reset()
	{

	}
	void ScytheScript::Circularmotion()
	{
		mTime += Time::DeltaTime() * mSpeed;

		float x = (std::cos(mTime) * mWidth) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().x;
		float y = (std::sin(mTime) * mHeight) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().y;

		float z = 0;

		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(x, y, z));
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3(0, 0, mTime * 3));
	}
}