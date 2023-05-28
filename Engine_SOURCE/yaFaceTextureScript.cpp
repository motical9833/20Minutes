#include "yaFaceTextureScript.h"
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	FaceTextureScript::FaceTextureScript(Vector3 posA, Vector3 posB)
		:mSpeed(0.05f)
		,bMove(false)
		,bStop(true)
		,targetPosA(posA)
		,targetPosB(posB)
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

		if (pos.y > 1.2f)
		{
			mSpeed = -0.05f;
		}
		else if (pos.y < 1.0f)
		{
			mSpeed = 0.05f;
		}

		pos.y += mSpeed * Time::DeltaTime();

		GetOwner()->GetComponent<Transform>()->SetPosition(pos);


		if (bStop == false && bMove == false)
		{
			Vector3 dir = SetMoveDirection(targetPosA);


			pos.x += 5 * dir.x * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (std::abs(targetPosA.x) >= std::abs(GetOwner()->GetComponent<Transform>()->GetPosition().x))
			{
				bStop = true;
			}
		}
		else if (bStop == false && bMove)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 dir = SetMoveDirection(targetPosB);


			pos.x += 5 * dir.x * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (std::abs(targetPosB.x) <= std::abs(GetOwner()->GetComponent<Transform>()->GetPosition().x))
			{
				bStop = true;
			}
		}
	}
	void FaceTextureScript::FixedUpdate()
	{

	}
	void FaceTextureScript::Render()
	{

	}
	Vector3 FaceTextureScript::SetMoveDirection(Vector3 pos)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 a = tr->GetPosition();

		Vector3 b = pos;

		Vector3 dir = b - a;

		Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

		double value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2));

		Vector3 dirValue = Vector3(fabsDir.x / value, fabsDir.y / value, 0);

		return dirValue;
	}
	void FaceTextureScript::UpDownMove()
	{

	}
	void FaceTextureScript::Next()
	{
		bStop = false;
		bMove = false;
	}
	void FaceTextureScript::Back()
	{
		bStop = false;
		bMove = true;
	}
}