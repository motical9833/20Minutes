#pragma once
#include "yaScript.h"


namespace ya
{
	class TreePosScript : public Script
	{
	public:
		TreePosScript();
		virtual ~TreePosScript();

		virtual void Initalize();
		virtual void Update();

		float Distance(Vector3 myPos, Vector3 targetPos);

	private:
		Transform* mTransform;
		Vector3 savedPos;
		Vector3 originPos;
		Vector3 pos;
	};
}