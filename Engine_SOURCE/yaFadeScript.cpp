#include "yaFadeScript.h"
#include "yaRenderer.h"
#include "yaMaterial.h"
#include "yaGameObject.h"
#include "yaTime.h"

namespace ya
{
	FadeScript::FadeScript()
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

		currentTime += time/2;

		ConstantBuffer* cbBuffer = renderer::constantBuffers[(UINT)eCBType::FadeInOut];
		renderer::FadeInOutCB fadeData;

		if (fadeData.alpha < 1)
		{
			fadeData.alpha = currentTime;
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