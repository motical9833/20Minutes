#include "yaBulletScript.h"
#include "yaTime.h"
#include "yaGameObject.h"
#include "yaPlayScene.h"
#include "yaSceneManager.h"
#include "yaWeapon.h"
#include "yaScene.h"
#include "yaTransform.h"
#include "yaInput.h"

namespace ya
{
	BulletScript::BulletScript()
		:mSpeed(10.0f)
		, time(0.0f)
		,direction{}
		,mTr(nullptr)
		,mWeapon(nullptr)
		,playScene(nullptr)
	{

	}
	BulletScript::~BulletScript()
	{

	}
	void BulletScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		playScene = SceneManager::GetPlaySCene();
		mWeapon = dynamic_cast<PlayScene*>(playScene)->GetWeapon();

		mTr->SetParent(mWeapon->GetComponent<Transform>());
		mTr->SetPosition(Vector3::Zero);
		GetOwner()->Death();
	}
	void BulletScript::Update()
	{
		time += Time::DeltaTime();
		Vector3 pos = mTr->GetPosition();

		if (time >= 3.0f)
		{
			GetOwner()->Death();
			time = 0;
			mTr->SetPosition(Vector3::Zero);
		}

		pos.x += direction.x * mSpeed * Time::DeltaTime();
		pos.y += direction.y * mSpeed * Time::DeltaTime();


		mTr->SetPosition(pos);

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
	void BulletScript::Reset()
	{
		time = 0.0f;
		mSpeed = 10.0f;
		mTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		mTr->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		mTr->SetScale(Vector3(2.0f, 2.0f, 0.0f));
	}
}