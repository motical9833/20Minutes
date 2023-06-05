#pragma once
#include "yaScript.h"


namespace ya
{
	class LeavesScirpt : public Script
	{
	public:
		LeavesScirpt(Vector3 posA,Vector3 posB);
		virtual ~LeavesScirpt();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		Vector3 SetMoveDirection(Vector3 pos);
		void Next();
		void Back();
		void Reset();

	private:
		bool bMove;
		bool bStop;

		int value;
		int mSpeed;

		float rightPosX;
		float leftPosX;

		Vector3 originPos;
		Vector3 targetPos;
	};
}