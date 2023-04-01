#include "yaBulletScript.h"
#include "yaTime.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaPlayScene.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaInput.h"

namespace ya
{
	BulletScript::BulletScript()
		:mSpeed(20.0f)
		, time(0.0f)
		,direction{}
	{

	}
	BulletScript::~BulletScript()
	{

	}
	void BulletScript::Initalize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Scene* scene = SceneManager::GetPlaySCene();
		Weapon* weapon = dynamic_cast<PlayScene*>(scene)->GetWeapon();

		tr->SetParent(weapon->GetComponent<Transform>());
		tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		GetOwner()->Death();

	}
	void BulletScript::Update()
	{
		time += Time::DeltaTime();
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Scene* scene = SceneManager::GetPlaySCene();
		Weapon* weapon = dynamic_cast<PlayScene*>(scene)->GetWeapon();

		Vector3 pos = tr->GetPosition();

		pos.x += direction.x * 3.0f * Time::DeltaTime();
		pos.y += direction.y * 3.0f * Time::DeltaTime();

		tr->SetPosition(pos);

	}
	void BulletScript::Render()
	{

	}
	void BulletScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void BulletScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void BulletScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void BulletScript::Start()
	{

	}
	void BulletScript::Action()
	{

	}
	void BulletScript::End()
	{

	}
}