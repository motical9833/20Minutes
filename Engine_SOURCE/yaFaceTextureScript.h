#pragma once
#include "yaScript.h"


namespace ya
{
	class FaceTextureScript : public Script
	{
	public:
		FaceTextureScript(Vector3 posA, Vector3 posB);
		virtual ~FaceTextureScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		Vector3 SetMoveDirection(Vector3 pos);
		void UpDownMove();
		void Next();
		void Back();

	private:
		bool bMove;
		bool bStop;

		float mSpeed;

		Vector3 targetPosA;
		Vector3 targetPosB;
	};
}