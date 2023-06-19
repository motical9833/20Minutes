#include "yaCameraScript.h"
#include "yaTransform.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaTime.h"


namespace ya
{
	CameraScript::CameraScript()
		: Script()
		, target(nullptr)
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
		tr->SetPosition(target->GetComponent<Transform>()->GetPosition() + Vector3(0.0f, 0.0f, -12.0f));
	}
	void CameraScript::Render()
	{
	}
}