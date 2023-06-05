#include "yaCursorUIScript.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaRenderer.h"

namespace ya
{
	CursorUIScript::CursorUIScript()
		:mTrans(nullptr)
		,mPos{}
		,mRot{}
	{

	}
	CursorUIScript::~CursorUIScript()
	{

	}
	void CursorUIScript::Initalize()
	{
		mTrans = GetOwner()->GetComponent<Transform>();
	}
	void CursorUIScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPosition();
		Vector3 forward = tr->Foward();

		Vector2 mMousPosition = Input::GetMouseWorldPosition();
		Camera* camera = renderer::mainCamera;
		math::Matrix mProjection = camera->GetProjectionMatrix();
		math::Matrix mView = camera->GetViewMatrix();

		mMousPosition.x = mMousPosition.x / mProjection._11;
		mMousPosition.y = mMousPosition.y / mProjection._22;
		mMousPosition.x = mMousPosition.x * 8.0f;
		mMousPosition.y = mMousPosition.y * 8.35f;

		tr->SetPosition(Vector3(mMousPosition) + Vector3(1.0f,0.8f,9.0f));
	}
	void CursorUIScript::FixedUpdate()
	{

	}
	void CursorUIScript::Render()
	{

	}
}