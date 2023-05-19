#include "yaExpMarbleObject.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaPlayerLevelScript.h"
#include "yaPlayScene.h"

namespace ya
{
	ExpMarbleObject::ExpMarbleObject()
		:bTarget(false)
		, mTime(0.0f)
		, mSpeed(5.0f)
		, mDir{}
		,mTarget(nullptr)
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
		if (bTarget == false && mTarget == nullptr)
			return;

		mTime += Time::DeltaTime();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 a = tr->GetPosition();

		Vector3 b = mTarget->GetComponent<Transform>()->GetPosition();

		Vector3 dir = b - a;

		Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

		double value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2)); //피타고라스 R값

		Vector3 dirValue = Vector3(fabsDir.x / value, fabsDir.y / value, 0);

		mDir = dirValue;


		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		pos.y += mDir.y * mSpeed * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);

	}
	void ExpMarbleObject::FixedUpdate()
	{

	}
	void ExpMarbleObject::Render()
	{

	}
	void ExpMarbleObject::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::ColliderChack)
		{
			bTarget = true;
			mTarget = collider->GetOwner();
		}

		if (collider->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			SceneManager::GetPlayScene()->GetLevelManager()->GetScript<PlayerLevelScript>()->GetExp();
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
		mDir = Vector3::Zero;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		mTarget = nullptr;
		bTarget = false;
	}
	void ExpMarbleObject::Reset()
	{
		mDir = Vector3::Zero;
		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3::Zero);
		mTarget = nullptr;
		bTarget = false;
	}
}