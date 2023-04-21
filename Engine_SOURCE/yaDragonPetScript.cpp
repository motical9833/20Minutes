#include "yaDragonPetScript.h"
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	DragonPetScript::DragonPetScript()
		:mSpeed(1.0f)
		,mWidth(1.0f)
	    ,mHeight(1.0f)
		,mTime(0.0f)
	{

	}
	DragonPetScript::~DragonPetScript()
	{

	}
	void DragonPetScript::Initalize()
	{

	}
	void DragonPetScript::Update()
	{
		Circularmotion();
	}
	void DragonPetScript::Render()
	{

	}
	void DragonPetScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void DragonPetScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void DragonPetScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void DragonPetScript::Start()
	{

	}
	void DragonPetScript::Action()
	{

	}
	void DragonPetScript::End()
	{

	}
	void DragonPetScript::Reset()
	{

	}
	void DragonPetScript::Circularmotion()
	{
		mTime += Time::DeltaTime() * mSpeed;

		float x = std::cos(mTime) * mWidth;
		float y = std::sin(mTime) * mHeight;

		float z = 0;

		GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(x, y, z));
	}
}