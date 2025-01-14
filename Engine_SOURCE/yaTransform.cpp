#include "yaTransform.h"
#include "yaRenderer.h"
#include "yaCamera.h"
#include "yaTime.h"
#include "yaGameObject.h"

namespace ya
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mFoward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mLeft(Vector3::Left)
		, mUp(Vector3::Up)
		, mScale(Vector3::One)
		, mRotation(Vector3::Zero)
		, mPosition(Vector3::One)
		, mParent(nullptr)
		, mChiled{}
		, bFollowParents(false)
	{
		
	}

	Transform::~Transform()
	{

	}

	void Transform::Initalize()
	{

	}

	void Transform::Update()
	{

	}

	void Transform::FixedUpdate()
	{
		//렌더링에 사용될 위치값 업데이트

		// 월드 행렬 생성
		
		// 크기 변환 행렬
		Matrix scale = Matrix::CreateScale(mScale);

		// 회전 변환 행렬
		Matrix rotation;

		//Vector3 radian(mRotation.x * (XM_PI / 180), mRotation.y * (XM_PI / 180),mRotation.z * (XM_PI / 180));

		//rotation = Matrix::CreateRotationX(radian.x);
		//rotation *= Matrix::CreateRotationY(radian.y);
		//rotation *= Matrix::CreateRotationZ(radian.z);

		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		// 이동 변환 행렬
		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;
		mNoScaleWorld = rotation * position;


		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mLeft = Vector3::TransformNormal(Vector3::Left, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		
		// 카메라 컴포넌트에서 세팅
		// 뷰행렬 세팅
		// 프로젝션 행렬 세팅

		if (mParent)
		{
			mWorld *= mParent->mNoScaleWorld;
		}
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		renderer::TransformCB trCb = {};
		trCb.world = mWorld;
		trCb.view = Camera::GetGpuViewMatrix();
		trCb.projection = Camera::GetGpuProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->Setdata(&trCb);
		cb->BindSRV(eShaderStage::VS);
		cb->BindSRV(eShaderStage::HS);
		cb->BindSRV(eShaderStage::DS);
		cb->BindSRV(eShaderStage::GS);
		cb->BindSRV(eShaderStage::PS);
		cb->BindSRV(eShaderStage::CS);
	}
	void Transform::SetParent(Transform* parent)
	{
		mParent = parent;

		if (mParent == nullptr)
			return;

		mParent->SetChiled(this);
	}

	void Transform::LeftMove()
	{
		Vector3 pos = this->GetPosition();
		pos.x -= 3.0f * Time::DeltaTime();
		this->SetPosition(pos);
	}
	void Transform::RightMove()
	{
		Vector3 pos = this->GetPosition();
		pos.x += 3.0f * Time::DeltaTime();
		this->SetPosition(pos);
	}
}
