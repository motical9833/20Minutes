#include "yaFadeScript.h"
#include "yaRenderer.h"
#include "yaMaterial.h"
#include "yaGameObject.h"
#include "yaTime.h"
#include "yaInput.h"

namespace ya
{
	FadeScript::FadeScript()
		:bFade(false)
	{

	}
	FadeScript::~FadeScript()
	{

	}
	void FadeScript::Initalize()
	{
		
	}
	void FadeScript::Update()
	{
		float time = Time::DeltaTime();

		ConstantBuffer* cbBuffer = renderer::constantBuffers[(UINT)eCBType::FadeInOut];
		renderer::FadeInOutCB fadeData;

		if (fadeData.alpha < 1 && bFade == false)
		{
			currentTime += time / 2;
			fadeData.alpha = currentTime;

			if (fadeData.alpha > 1)
				bFade = true;
		}
		else
		{
			currentTime -= time / 2;
			fadeData.alpha = currentTime;

			if (fadeData.alpha < 0)
				bFade = false;
		}


		cbBuffer->Bind(&fadeData);
		cbBuffer->SetPipline(eShaderStage::VS);
		cbBuffer->SetPipline(eShaderStage::PS);
	}
	void FadeScript::FixedUpdate()
	{

	}
	void FadeScript::Render()
	{

	}
}