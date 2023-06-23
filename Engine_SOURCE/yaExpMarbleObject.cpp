#include "yaExpMarbleObject.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaPlayerLevelScript.h"
#include "yaPlayScene.h"
#include "yaAudioSource.h"

namespace ya
{
	ExpMarbleObject::ExpMarbleObject()
		:bTarget(false)
		, mTime(0.0f)
		, mSpeed(10.0f)
		, mDir{}
		,mTarget(nullptr)
		,btricky(false)
	{

	}
	ExpMarbleObject::~ExpMarbleObject()
	{

	}
	void ExpMarbleObject::Initalize()
	{

	}
	void ExpMarbleObject::Update()
	{

		if (bTarget == false)
		{
			Vector3 playerPos = SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();

			if (Distance(GetOwner()->GetComponent<Transform>()->GetPosition(), playerPos) <= 3.0f)
			{
				bTarget == true;
				mTarget = SceneManager::GetPlayScene()->GetPlayer();
			}
		}

		if (bTarget == false && mTarget == nullptr)
			return;

		Move(btricky);

	}
	void ExpMarbleObject::FixedUpdate()
	{

	}
	void ExpMarbleObject::Render()
	{

	}
	void ExpMarbleObject::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			SceneManager::GetPlayScene()->GetLevelManager()->GetScript<PlayerLevelScript>()->GetExp();
			SceneManager::GetPlayScene()->GetSoundObjects(0)->GetComponent<AudioSource>()->Play();
			GetOwner()->Death();
			Reset();
		}
	}
	void ExpMarbleObject::OnCollisionStay(Collider2D* collider)
	{

	}
	void ExpMarbleObject::OnCollisionExit(Collider2D* collider)
	{

	}
	void ExpMarbleObject::Move(bool& bValue)
	{
		if (bValue == false)
		{
			mTime += Time::DeltaTime();

			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			Transform* tr = GetOwner()->GetComponent<Transform>();

			Vector3 a = tr->GetPosition();

			Vector3 b = mTarget->GetComponent<Transform>()->GetPosition();

			Vector3 dir = b - a;

			Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

			double value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2));

			Vector3 dirValue = Vector3(fabsDir.x / value, fabsDir.y / value, 0);

			mDir = dirValue;


			pos.x -= mDir.x * mSpeed * Time::DeltaTime();
			pos.y -= (mDir.y + -0.5f) * mSpeed * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (mTime >= 0.1f)
			{
				bValue = true;
				mTime = 0;
			}
		}
		else
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			Transform* tr = GetOwner()->GetComponent<Transform>();

			Vector3 a = tr->GetPosition();

			Vector3 b = mTarget->GetComponent<Transform>()->GetPosition();

			Vector3 dir = b - a;

			Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

			double value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2));

			Vector3 dirValue = Vector3(fabsDir.x / value, fabsDir.y / value, 0);

			mDir = dirValue;


			pos.x += mDir.x * mSpeed * Time::DeltaTime();
			pos.y += mDir.y * mSpeed * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);
		}
	}
	void ExpMarbleObject::Start()
	{

	}
	void ExpMarbleObject::Action()
	{

	}
	void ExpMarbleObject::End()
	{

	}
	void ExpMarbleObject::GameReset()
	{
		mTime = 0.0f;
		mSpeed = 10.0f;
		mDir = Vector3::Zero;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		mTarget = nullptr;
		bTarget = false;
		btricky = false;
	}
	void ExpMarbleObject::Reset()
	{
		mDir = Vector3::Zero;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		mTarget = nullptr;
		bTarget = false;
		btricky = false;
	}
	float ExpMarbleObject::Distance(Vector3 myPos, Vector3 targetPos)
	{
		Vector3 dir = targetPos - myPos;

		Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

		float value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2));

		return value;
	}
}