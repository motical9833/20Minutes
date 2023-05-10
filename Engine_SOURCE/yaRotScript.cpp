#include "yaRotScript.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"


namespace ya
{
	RotScript::RotScript()
	{

	}
	RotScript::~RotScript()
	{

	}
	void RotScript::Initalize()
	{

	}
	void RotScript::Update()
	{
		Rotate();

		Vector3 pos = SceneManager::GetPlayScene()->GetGhostPet()->GetComponent<Transform>()->GetPosition();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
	}
	void RotScript::Render()
	{

	}
	void RotScript::OnCollisionEnter(Collider2D* collider)
	{

	}
	void RotScript::OnCollisionStay(Collider2D* collider)
	{

	}
	void RotScript::OnCollisionExit(Collider2D* collider)
	{

	}
	void RotScript::Rotate()
	{
		Vector3 mPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		Vector3 rot = GetOwner()->GetComponent<Transform>()->GetRotation() + SceneManager::GetPlayScene()->GetGhostPet()->GetComponent<Transform>()->GetRotation();

		Vector3 mMousePos = Input::GetMousePosition();
		Vector3 mRot = GetOwner()->GetComponent<Transform>()->GetRotation();
		mRot.z = atan2(mMousePos.y - mPos.y, mMousePos.x - mPos.x);
		GetOwner()->GetComponent<Transform>()->SetRotation(mRot);

		Vector3 dir = Input::GetMousePosition() - mPos;

		dir.Normalize();

		GetOwner()->GetComponent<Transform>()->SetPosition(dir);
	}
}