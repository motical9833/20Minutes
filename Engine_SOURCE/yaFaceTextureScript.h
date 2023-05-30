#pragma once
#include "yaScript.h"


namespace ya
{
	class FaceTextureScript : public Script
	{
	public:
		FaceTextureScript();
		virtual ~FaceTextureScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		void UpDownMove();

	private:
		float mSpeed;

	};
}