#pragma once
#include "yaScript.h"
#include "yaCamera.h"

namespace ya
{
	class FadeScript : public Script
	{
	public:
		FadeScript();
		virtual ~FadeScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetCamera(Camera* camera) { mCamera = camera; }
		void SetFadeTime(float time) { mFadeTime = time; }

	private:
		Camera* mCamera;
		bool mIsFadeOut;
		float mDeltaTime;
		float mFadeTime;
		
		float currentTime;
	};
}