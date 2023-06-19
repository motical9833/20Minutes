#include "yaIcicleScript.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaMonsterScript.h"
#include "yaAudioSource.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"

namespace ya
{
	IcicleScript::IcicleScript()
		:mSpeed(10.0f)
		,mTime(0.0f)
	{

	}
	IcicleScript::~IcicleScript()
	{

	}
	void IcicleScript::Initalize()
	{

	}
	void IcicleScript::Update()
	{
		mTime += Time::DeltaTime();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (mTime >= 3.0f)
		{
			GetOwner()->Death();
			Reset();
		}

		pos += GetOwner()->GetComponent<Transform>()->Right() * (mSpeed) * Time::DeltaTime();
		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
	}
	void IcicleScript::Render()
	{
	}
	void IcicleScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster || collider->GetOwner()->GetLayerType() == eLayerType::MonsterBoomer && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			collider->GetOwner()->GetScript<MonsterScript>()->Freeze();

			for (size_t i = 0; i < SceneManager::GetPlayScene()->GetIcicleSounds().size(); i++)
			{
				if (SceneManager::GetPlayScene()->GetIcicleSounds()[i]->IsDead() == false)
					continue;

				SceneManager::GetPlayScene()->GetIcicleSounds()[i]->Life();
				SceneManager::GetPlayScene()->GetIcicleSounds()[i]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition() + Vector3(0.0f, 0.0f, -11.0f));
				SceneManager::GetPlayScene()->GetIcicleSounds()[i]->GetComponent<AudioSource>()->Play();

				break;
			}
			Reset();
		}
		else if (collider->GetOwner()->GetLayerType() == eLayerType::Boss && collider->GetOwner()->GetState() == (UINT)GameObject::eState::Active)
		{
			collider->GetOwner()->GetScript<MonsterScript>()->Freeze();

			for (size_t i = 0; i < SceneManager::GetPlayScene()->GetIcicleSounds().size(); i++)
			{
				if (SceneManager::GetPlayScene()->GetIcicleSounds()[i]->IsDead() == false)
					continue;

				SceneManager::GetPlayScene()->GetIcicleSounds()[i]->Life();
				SceneManager::GetPlayScene()->GetIcicleSounds()[i]->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition() + Vector3(0.0f, 0.0f, -11.0f));
				SceneManager::GetPlayScene()->GetIcicleSounds()[i]->GetComponent<AudioSource>()->Play();

				break;
			}
			Reset();
		}

	}
	void IcicleScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void IcicleScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void IcicleScript::Start()
	{
	}
	void IcicleScript::Action()
	{
	}
	void IcicleScript::End()
	{
	}
	void IcicleScript::Reset()
	{
		mTime = 0.0f;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		GetOwner()->GetComponent<Transform>()->SetRotation(Vector3::Zero);
		GetOwner()->Death();
	}
}