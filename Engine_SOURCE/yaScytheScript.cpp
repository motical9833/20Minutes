#include "yaScytheScript.h"
#include "yaSceneManager.h"
#include "yaGameObject.h"
#include "yaPlayScene.h"
#include "yaMonsterScript.h"
#include "yaTime.h"
#include "yaAudioSource.h"

namespace ya
{
	ScytheScript::ScytheScript()
		:mSpeed(3.5f)
		, mWidth(3.0f)
		, mHeight(3.0f)
		, mTime(0.0f)
		, mDamage(40)
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
		if (SceneManager::GetPlayScene()->GetUIOn())
			return;

		Circularmotion();
	}
	void ScytheScript::Render()
	{

	}
	void ScytheScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			GetOwner()->GetComponent<AudioSource>()->Play();
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
	void ScytheScript::GameReset()
	{
		mSpeed = 3.5f;
		mWidth = 3.0f;
		mHeight = 3.0f;
		mTime = 0.0f;
		mDamage = 40;
		GetOwner()->Death();
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