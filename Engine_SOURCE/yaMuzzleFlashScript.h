#pragma once
#include "yaScript.h"
#include "yaPlayer.h"
namespace ya
{
	class MuzzleFlashScript : public Script
	{
	public:
		MuzzleFlashScript();
		virtual ~MuzzleFlashScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void GetPlayer();
		void FireSound();
	private:
		Player* player;

		Vector3 mPos;
		Vector3 mRot;
		Vector3 mMousePos;

		Transform* mTrans;

		float mTime;
	};
}

