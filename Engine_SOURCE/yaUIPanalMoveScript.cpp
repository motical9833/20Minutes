#include "yaUIPanalMoveScript.h"
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	UIPanalMoveScript::UIPanalMoveScript(Vector3 pos)
		:bStop(true)
		,bMove(false)
		,originPos()
		,targetPos(pos)
	{

	}
	UIPanalMoveScript::~UIPanalMoveScript()
	{

	}
	void UIPanalMoveScript::Initalize()
	{
		originPos = GetOwner()->GetComponent<Transform>()->GetPosition();
	}
	void UIPanalMoveScript::Update()
	{
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (bStop == false && bMove == false)
		{
			Vector3 distance = targetPos - pos;

			float a = std::abs(distance.x);
			float b = std::abs(distance.y);

			Vector3 dir = SetMoveDirection(targetPos);


			pos += 20 * dir * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (a <= 0.01f && b <= 0.01f)
			{
				GetOwner()->GetComponent<Transform>()->SetPosition(targetPos);
				bStop = true;
			}
		}
		else if (bStop == false && bMove)
		{
			Vector3 distance = originPos - pos;

			float a = std::abs(distance.x);
			float b = std::abs(distance.y);

			Vector3 dir = SetMoveDirection(originPos);


			pos += 20 * dir * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (a <= 0.01f && b <= 0.01f)
			{
				GetOwner()->GetComponent<Transform>()->SetPosition(originPos);
				bStop = true;
			}
		}
	}
	void UIPanalMoveScript::FixedUpdate()
	{

	}
	void UIPanalMoveScript::Render()
	{

	}
	Vector3 UIPanalMoveScript::SetMoveDirection(Vector3 pos)
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
	void UIPanalMoveScript::Next()
	{
		bStop = false;
		bMove = false;
	}
	void UIPanalMoveScript::Back()
	{
		bStop = false;
		bMove = true;
	}
}