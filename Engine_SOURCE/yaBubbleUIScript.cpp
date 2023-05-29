#include "yaBubbleUIScript.h"
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	BubbleUIScript::BubbleUIScript(Vector3 posA, Vector3 posB)
		: bMove(false)
		, bStop(true)
		, targetPosA(posA)
		, targetPosB(posB)
	{

	}
	BubbleUIScript::~BubbleUIScript()
	{

	}
	void BubbleUIScript::Initalize()
	{

	}
	void BubbleUIScript::Update()
	{
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (bStop == false && bMove == false)
		{
			float distance = pos.x - targetPosA.x;
			Vector3 dir = SetMoveDirection(targetPosA);

			pos.x += 7 * dir.x * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (distance >= 0)
			{
				bStop = true;
			}
		}
		else if (bStop == false && bMove)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			float distance = pos.x - targetPosB.x;
			Vector3 dir = SetMoveDirection(targetPosB);


			pos.x += 7 * dir.x * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (distance <= 0)
			{
				bStop = true;
			}
		}
	}
	void BubbleUIScript::FixedUpdate()
	{

	}
	void BubbleUIScript::Render()
	{

	}
	Vector3 BubbleUIScript::SetMoveDirection(Vector3 pos)
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
	void BubbleUIScript::Next()
	{
		bStop = false;
		bMove = false;
	}
	void BubbleUIScript::Back()
	{
		bStop = false;
		bMove = true;
	}
}