#include "yaSelectPanalScript.h"
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	SelectPanalScript::SelectPanalScript(Vector3 posA, Vector3 posB)
		:bStop(true)
		,bMove(false)
		, targetPosA(posA)
		, targetPosB(posB)
	{

	}
	SelectPanalScript::~SelectPanalScript()
	{

	}
	void SelectPanalScript::Initalize()
	{

	}
	void SelectPanalScript::Update()
	{
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (bStop == false && bMove == false)
		{
			Vector3 dir = SetMoveDirection(targetPosA);


			pos.y += 3 * dir.y * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (std::abs(targetPosA.y) >= std::abs(GetOwner()->GetComponent<Transform>()->GetPosition().y))
			{
				bStop = true;
			}
		}
		else if (bStop == false && bMove)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 dir = SetMoveDirection(targetPosB);


			pos.y += 3 * dir.y * Time::DeltaTime();

			GetOwner()->GetComponent<Transform>()->SetPosition(pos);

			if (std::abs(targetPosB.y) <= std::abs(GetOwner()->GetComponent<Transform>()->GetPosition().y))
			{
				bStop = true;
			}
		}
	}
	void SelectPanalScript::FixedUpdate()
	{

	}
	void SelectPanalScript::Render()
	{

	}
	Vector3 SelectPanalScript::SetMoveDirection(Vector3 pos)
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
	void SelectPanalScript::Next()
	{
		bStop = false;
		bMove = false;
	}
	void SelectPanalScript::Back()
	{
		bStop = false;
		bMove = true;
	}
}