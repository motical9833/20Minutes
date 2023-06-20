#include "yaFireLightScript.h"
#include "yaSceneManager.h"
#include "yaGameObject.h"
#include "yaPlayScene.h"
#include "yaInput.h"
#include "yaTime.h"


namespace ya
{
	FireLightScript::FireLightScript()
		:player(nullptr)
		, mPos{}
		, mRot{}
		, mMousePos{}
		, mTrans(nullptr)
		, mTime(0.0f)
	{

	}
	FireLightScript::~FireLightScript()
	{

	}
	void FireLightScript::Initalize()
	{
		mTrans = GetOwner()->GetComponent<Transform>();
	}
	void FireLightScript::Update()
	{
		mTime += Time::DeltaTime();

		if (mTime >= 0.1f)
		{
			GetOwner()->Death();
			mTime = 0;
		}

		mPos = mTrans->GetPosition() + mTrans->GetParent()->GetPosition();

		Vector3 rot = mTrans->GetRotation();

		mMousePos = Input::GetMousePosition();
		mRot = mTrans->GetRotation();
		mRot.z = atan2(mMousePos.y - mPos.y, mMousePos.x - mPos.x);
		mTrans->SetRotation(mRot);

		Vector3 dir = Input::GetMousePosition() - mPos;

		dir.Normalize();

		GetOwner()->GetComponent<Transform>()->SetPosition(dir / 1.2f + player->GetComponent<Transform>()->GetPosition());
	}
	void FireLightScript::FixedUpdate()
	{

	}
	void FireLightScript::Render()
	{

	}
	void FireLightScript::GetPlayer()
	{
		player = SceneManager::GetPlayScene()->GetPlayer();
	}
}