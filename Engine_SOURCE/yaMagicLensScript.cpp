#include "yaMagicLensScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaTime.h"

namespace ya
{
	MagicLensScript::MagicLensScript()
		:mSpeed(0.7f)
		,mWidth(0.8f)
		,mHeight(0.8f)
		,mTime(0.0f)
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
		if (collider->GetOwner()->GetLayerType() == eLayerType::Bullet)
		{
			Vector3 scale = collider->GetOwner()->GetComponent<Transform>()->GetScale();

			collider->GetOwner()->GetComponent<Transform>()->SetScale(Vector3(scale.x * 1.3f, scale.y * 1.3f, 1.0f));
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
	void MagicLensScript::Reset()
	{

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

		//Vector3 mPos = mTrans->GetPosition() + mTrans->GetParent()->GetPosition();

		Vector3 mPos = mTrans->GetPosition();
		Vector3 rot = mTrans->GetRotation();

		//Vector3 playerPos = mTrans->GetParent()->GetPosition();
		Vector3 playerPos = SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector3 mRot = mTrans->GetRotation();
		mRot.z = atan2(playerPos.y - mPos.y, playerPos.x - mPos.x);
		mTrans->SetRotation(mRot);
	}
}