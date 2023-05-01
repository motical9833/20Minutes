#pragma once
#include "yaBaseRenderer.h"
#include "yaParticleShader.h"

namespace ya
{
	class ParticleSystem : public BaseRenderer
	{
	public:
		ParticleSystem();
		virtual ~ParticleSystem();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		class StructedBuffer* mBuffer;
		class StructedBuffer* mSharedBuffer;

		std::shared_ptr<ParticleShader>mCS;
		renderer::ParticleSystemCB mCBData;

		UINT mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float mStartLifeTime;
		float mFrequency;
		float mTime;

	};
}