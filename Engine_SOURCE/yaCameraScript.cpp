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

		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::D))
		{
			pos += 100.0f * tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			pos += 100.0f * -tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::W))
		{
			pos += 100.0f * tr->Foward() * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			pos += 100.0f * -tr->Foward() * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::Q))
		{
			pos += 100.0f * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::E))
		{
			pos += 100.0f * -tr->Up() * Time::DeltaTime();
		}

		//tr->SetPosition(pos);
	}
	void CameraScript::Render()
	{
	}
}