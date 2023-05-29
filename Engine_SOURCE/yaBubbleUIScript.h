#pragma once
#include "yaScript.h"



namespace ya
{
	class BubbleUIScript : public Script
	{
	public:
		BubbleUIScript(Vector3 posA,Vector3 posB);
		virtual ~BubbleUIScript();

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