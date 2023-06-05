#pragma once
#include "yaScript.h"


namespace ya
{
	class CursorUIScript : public Script
	{
	public:
		CursorUIScript();
		virtual ~CursorUIScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


	private:
		Transform* mTrans;

		Vector3 mPos;
		Vector3 mRot;
	};
}