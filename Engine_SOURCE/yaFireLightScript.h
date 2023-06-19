#pragma once
#include "yaScript.h"
#include "yaPlayer.h"

namespace ya
{
	class FireLightScript : public Script
	{
	public:
		FireLightScript();
		virtual ~FireLightScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void GetPlayer();

	private:
		Player* player;

		Vector3 mPos;
		Vector3 mRot;
		Vector3 mMousePos;

		Transform* mTrans;

		float mTime;
	};
}