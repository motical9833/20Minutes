#pragma once
#include "yaScript.h"


namespace ya
{
	class UIPanalMoveScript : public Script
	{
	public:
		UIPanalMoveScript(Vector3 pos);
		virtual ~UIPanalMoveScript();

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

		Vector3 originPos;
		Vector3 targetPos;
	};
}