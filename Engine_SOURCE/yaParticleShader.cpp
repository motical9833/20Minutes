#include "yaParticleShader.h"
#include "yaRenderer.h"
#include "yaConstantBuffer.h"
#include "yaTime.h"

namespace ya::graphics
{
	ParticleShader::ParticleShader()
		:ComputeShader(128,1,1)
		,mBuffer(nullptr)
		, mSharedBuffer(nullptr)
	{

	}
	ParticleShader::~ParticleShader()
	{

	}
	void ParticleShader::Binds()
	{
		mBuffer->BindUAV(eShaderStage::CS, 0);
		mSharedBuffer->BindUAV(eShaderStage::CS, 1);

		mGroupX = mBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}
	void ParticleShader::Clear()
	{
		mBuffer->Clear();
		mSharedBuffer->Clear();
	}
	//void ParticleShader::SetStrcutedBuffer(StructedBuffer* buffer)
	//{
	//	mBuffer = buffer;

	//	renderer::ParticleSystemCB info = {};
	//	info.elementCount = mBuffer->GetStride();
	//	info.deltaTime = Time::DeltaTime();

	//	ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
	//	cb->Setdata(&info);
	//	cb->BindSRV(eShaderStage::CS);
	//}
}