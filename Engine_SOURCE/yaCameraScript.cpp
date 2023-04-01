#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"

namespace ya
{
	CameraScript::CameraScript()
		: Script()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initalize()
	{
	}

	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Transform* pTr = tr->GetParent();

		tr->SetPosition(pTr->GetPosition() + Vector3(0.0f, 0.0f, -10.0f));

	}
	void CameraScript::Render()
	{
	}
}