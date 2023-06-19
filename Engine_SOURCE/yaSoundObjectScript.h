#pragma once
#include "yaScript.h"




namespace ya
{
	class SoundObjectScript : public Script
	{
	public:
		SoundObjectScript();
		virtual ~SoundObjectScript();

		virtual void Initalize();
		virtual void Update();

		void ObjectOn();
	private:
		float mTime;
		GameObject* pSceneCamera;
	};
}