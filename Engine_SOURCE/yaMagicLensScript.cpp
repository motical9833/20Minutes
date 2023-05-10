#include "yaMagicLensScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTime.h"
#include "yaBulletScript.h"

namespace ya
{
	MagicLensScript::MagicLensScript()
		: mSpeed(0.7f)
		, mWidth(0.8f)
		, mHeight(0.8f)
		, mTime(0.0f)
		, bIgnitionLens(false)
		, bRefraction(false)
		, mScaleValue(1.3f)
		, mDamageInc(0.3f)
	{

	}
	MagicLensScript::~MagicLensScript()
	{

	}
	void MagicLensScript::Initalize()
	{

	}
	void MagicLensScript::Update()
	{
		Circularmotion();
		LookPlayer();
	}
	void MagicLensScript::Render()
	{

	}
	void MagicLensScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Bullet && collider->GetOwner()->GetScript<BulletScript>()->GetMagicLensOn() == false)
		{
			collider->GetOwner()->GetScript<BulletScript>()->SetMagicLensOn();

			Vector3 scale = collider->GetOwner()->GetComponent<Transform>()->GetScale();

			collider->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(scale.x * mScaleValue, scale.y * mScaleValue, 1.0f));

			collider->GetOwner()->GetScript<BulletScript>()->SetDamageInc(mDamageInc);

			if (bIgnitionLens)
				collider->GetOwner()->GetScript<BulletScript>()->SetIgnitionBullet();

			if(bRefraction)
				collider->GetOwner()->GetScript<BulletScript>()->SetBounceCntAdd(2);
		}
	}
	void MagicLensScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void MagicLensScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void MagicLensScript::Start()
	{

	}
	void MagicLensScript::Action()
	{

	}
	void MagicLensScript::End()
	{

	}
	void MagicLensScript::GameReset()
	{
		bIgnitionLens = false;
		mScaleValue = 1.3f;
		mDamageInc = 0.3f;
	}
	void MagicLensScript::FocalPoint()
	{
		Vector3 scale = GetOwner()->GetComponent<Transform>()->GetScale();

		Vector3 newScale = Vector3(scale.x / 2, scale.y / 2, scale.z);

		GetOwner()->GetComponent<Transform>()->SetScale(newScale);
		mScaleValue = 1.6f;
		mDamageInc = 0.6f;
	}
	void MagicLensScript::Circularmotion()
	{
		mTime += Time::DeltaTime() * mSpeed;

		float x = (std::cos(mTime) * mWidth) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().x;
		float y = (std::sin(mTime) * mHeight) + SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition().y;

		float z = 0;

		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(x, y, z));
	}
	void MagicLensScript::LookPlayer()
	{
		Transform* mTrans = GetOwner()->GetComponent<Transform>();


		Vector3 mPos = mTrans->GetPosition();
		Vector3 rot = mTrans->GetRotation();

		Vector3 playerPos = SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector3 mRot = mTrans->GetRotation();
		mRot.z = atan2(playerPos.y - mPos.y, playerPos.x - mPos.x);
		mTrans->SetRotation(mRot);
	}
}