#pragma once
#include "yaScript.h"

namespace ya
{
	class SelectPanalScript : public Script
	{
	public:
		SelectPanalScript(Vector3 posA,Vector3 posB);
		virtual ~SelectPanalScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		Vector3 SetMoveDirection(Vector3 pos);

		void Next();
		void Back();

	private:
		bool bStop;
		bool bMove;

		Vector3 targetPosA;
		Vector3 targetPosB;
	};
}