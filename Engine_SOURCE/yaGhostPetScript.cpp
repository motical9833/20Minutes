#include "yaGhostPetScript.h"
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	GhostPetScript::GhostPetScript()
		:mSpeed(1.5f)
		, mWidth(1.1f)
		, mHeight(1.1f)
		, mTime(0.0f)
	{

	}
	GhostPetScript::~GhostPetScript()
	{

	}
	void GhostPetScript::Initalize()
	{

	}
	void GhostPetScript::Update()
	{
		Circularmotion();
	}
	void GhostPetScript::Render()
	{

	}
	void GhostPetScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void GhostPetScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void GhostPetScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void GhostPetScript::Start()
	{

	}
	void GhostPetScript::Action()
	{

	}
	void GhostPetScript::End()
	{

	}
	void GhostPetScript::Reset()
	{

	}
	void GhostPetScript::Circularmotion()
	{
		mTime += Time::DeltaTime() * mSpeed;

		float x = std::cos(mTime) * mWidth;
		float y = std::sin(mTime) * mHeight;

		float z = 0;

		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(x, y, z));
	}
}