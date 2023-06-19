#include "yaTreePosScript.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaPlayScene.h"

namespace ya
{
	TreePosScript::TreePosScript()
		:savedPos{}
		, originPos{}
		,mTransform(NULL)
	{

	}
	TreePosScript::~TreePosScript()
	{

	}
	void TreePosScript::Initalize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		originPos = mTransform->GetPosition();
		savedPos = mTransform->GetPosition();
	}
	void TreePosScript::Update()
	{
		Vector3 currentPos =  SceneManager::GetPlayScene()->GetPlayer()->GetComponent<Transform>()->GetPosition();

		if (currentPos.x - savedPos.x < -30)
		{
			float posX = currentPos.x - 15;
			
			GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(posX, savedPos.y, 0.0f));
			savedPos.x = posX;
		}
		else if (currentPos.x - savedPos.x > 30)
		{
			float posX = currentPos.x + 15;

			GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(posX, savedPos.y, 0.0f));
			savedPos.x = posX;
		}
		else if (currentPos.y - savedPos.y < -18)
		{
			float posY = currentPos.y - 9;

			GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(savedPos.x, posY, 0.0f));
			savedPos.y = posY;
		}
		else if (currentPos.y - savedPos.y > 18)
		{
			float posY = currentPos.y + 9;

			GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(savedPos.x, posY, 0.0f));
			savedPos.y = posY;
		}
	}

	float TreePosScript::Distance(Vector3 myPos, Vector3 targetPos)
	{
		Vector3 dir = targetPos - myPos;

		Vector3 fabsDir = Vector3(dir.x, dir.y, 0);

		float value = sqrt(pow(fabsDir.x, 2) + pow(fabsDir.y, 2));

		return value;
	}
}