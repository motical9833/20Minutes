#include "yaFaceTextureScript.h"
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	FaceTextureScript::FaceTextureScript()
		:mSpeed(0.05f)
	{

	}
	FaceTextureScript::~FaceTextureScript()
	{

	}
	void FaceTextureScript::Initalize()
	{

	}
	void FaceTextureScript::Update()
	{
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (pos.y > 0.2f)
		{
			mSpeed = -0.05f;
		}
		else if (pos.y < 0.0f)
		{
			mSpeed = 0.05f;
		}

		pos.y += mSpeed * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);
	}
	void FaceTextureScript::FixedUpdate()
	{

	}
	void FaceTextureScript::Render()
	{

	}
	void FaceTextureScript::UpDownMove()
	{

	}
}