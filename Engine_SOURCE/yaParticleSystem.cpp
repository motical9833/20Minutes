#include "yaParticleSystem.h"
#include "yaMesh.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaStructedBuffer.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTexture.h"
#include "yaTime.h"

namespace ya
{
	ParticleSystem::ParticleSystem()
		: BaseRenderer(eComponentType::ParticleSystem)
		, mMaxParticles(100)
		, mStartSize(Vector4(1.0f, 1.0f, 1.0f, 1.0f))
		, mStartColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f))
		, mStartLifeTime(3.0f)
		, mFrequency(10.0f)
		, mTime(0.0f)
		, mCBData{}
		, mSimulationSpace(eSimulationSpace::World)
		, mRadius(1.0f)
		, mStartSpeed(1.0f)
		, mElapsedTime(0.0f)

	{

	}

	ParticleSystem::~ParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;

		delete mSharedBuffer;
		mSharedBuffer = nullptr;
	}

	void ParticleSystem::Initalize()
	{
		mCS = Resources::Find<ParticleShader>(L"ParticleCS");

		std::shared_ptr<Mesh> point = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(point);

		// Material 세팅
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		std::shared_ptr<Texture> tex = Resources::Find<Texture>(L"CartoonSmoke");
		material->SetTexture(eTextureSlot::T0, tex);

		Particle particles[100] = {};
		Vector4 startPos = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		for (size_t i = 0; i < mMaxParticles; i++)
		{
			particles[i].position = Vector4(0.0f, 0.0f, 20.0f, 1.0f);
			particles[i].active = 0;
			particles[i].direction =
				Vector4(cosf((float)i * (XM_2PI / (float)mMaxParticles))
					, sin((float)i * (XM_2PI / (float)mMaxParticles)), 0.0f, 1.0f);

			particles[i].speed = 100.0f;
		}

		mBuffer = new StructedBuffer();
		mBuffer->Create(sizeof(Particle), mMaxParticles, eSRVType::UAV, particles);

		mSharedBuffer = new StructedBuffer();
		mSharedBuffer->Create(sizeof(ParticleShared), 1, eSRVType::UAV, nullptr, true);
	}

	void ParticleSystem::Update()
	{

	}

	void ParticleSystem::FixedUpdate()
	{
		//파티클 생성 시간
		float aliveTime = 1.0f / mFrequency;
		//누적시간
		mTime += Time::DeltaTime();
		if (aliveTime < mTime)
		{
			float f = (mTime / aliveTime);
			UINT iAliveCount = (UINT)f;
			mTime = f - std::floor(f);

			ParticleShared shared = { 5, };
			mSharedBuffer->Setdata(&shared, 1);
		}
		else
		{
			ParticleShared shared = {  };
			mSharedBuffer->Setdata(&shared, 1);
		}

		mMaxParticles = mBuffer->GetStride();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		mCBData.worldPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		mCBData.maxParticles = mMaxParticles;
		mCBData.radius = mRadius;
		mCBData.simulationSpace = (UINT)mSimulationSpace;
		mCBData.startSpeed = mStartSpeed;
		mCBData.startSize = mStartSize;
		mCBData.startColor = mStartColor;
		mCBData.startLifeTime = mStartLifeTime;
		mCBData.deltaTime = Time::DeltaTime();
		mCBData.elapsedTime += Time::DeltaTime();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->Setdata(&mCBData);
		cb->BindSRV(eShaderStage::ALL);

		mCS->SetSharedStrutedBuffer(mSharedBuffer);
		mCS->SetStrcutedBuffer(mBuffer);
		mCS->OnExcute();
	}

	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();
		mBuffer->BindSRV(eShaderStage::GS, 15);

		GetMaterial()->BindSRV();
		GetMesh()->RenderInstanced(mMaxParticles);

		mBuffer->Clear();
	}
}