#include "yaLeavesScirpt.h"
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	LeavesScirpt::LeavesScirpt(Vector3 posA, Vector3 posB)
		: value(1)
		, mSpeed(5)
		, bMove(false)
		, bStop(true)
		, leftPosX(-13.0f)
		, rightPosX(13.0f)
		, originPos(posA)
		, targetPos(posB)
	{

	}
	LeavesScirpt::~LeavesScirpt()
	{

	}
	void LeavesScirpt::Initalize()
	{

	}
	void LeavesScirpt::Update()
	{
		if (bStop == false && bMove == false)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 dir = SetMoveDirection(originPos);


			pos.x += mSpeed * dir.x * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (std::abs(originPos.x) >= std::abs(GetOwner()->GetComponent<Transform>()->GetPosition().x))
			{
				bStop = true;
				GetOwner()->GetComponent<Transform>()->SetPosition(originPos);
			}
		}
		else if (bStop == false && bMove == true)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 dir = SetMoveDirection(targetPos);


			pos.x += mSpeed * dir.x * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (std::abs(targetPos.x) <= std::abs(GetOwner()->GetComponent<Transform>()->GetPosition().x))
			{
				bStop = true;
				GetOwner()->GetComponent<Transform>()->SetPosition(targetPos);
			}
		}
	}
	void LeavesScirpt::FixedUpdate()
	{

	}
	void LeavesScirpt::Render()
	{

	}
	Vector3 LeavesScirpt::SetMoveDirection(Vector3 pos)
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
	void LeavesScirpt::Next()
	{
		bMove = true;
		bStop = false;
	}
	void LeavesScirpt::Back()
	{
		bMove = false;
		bStop = false;
	}
	void LeavesScirpt::Reset()
	{
		bMove = false;
		bStop = false;

		GetOwner()->GetComponent<Transform>()->SetPosition(targetPos);
	}
}