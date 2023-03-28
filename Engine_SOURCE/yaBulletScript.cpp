#include "yaBulletScript.h"
#include "yaTime.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaPlayScene.h"
#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	BulletScript::BulletScript()
		:mSpeed(20.0f)
	{

	}
	BulletScript::~BulletScript()
	{

	}
	void BulletScript::Initalize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Scene* scene = SceneManager::GetPlaySCene();
		Player* player = dynamic_cast<PlayScene*>(scene)->GetPlayer();
	}
	void BulletScript::Update()
	{
		
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