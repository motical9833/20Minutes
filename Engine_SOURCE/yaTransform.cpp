#include "yaTransform.h"
#include "yaRenderer.h"
#include "yaCamera.h"

namespace ya
{
	Transform::Transform()
		:Component(eComponentType::Transform)
		,mForward(Vector3::Forward) //-1
		,mRight(Vector3::Right)
		,mUp(Vector3::Up)
		,mScale(Vector3::One)
		,mRotation(Vector3::Zero)
		,mPosition(Vector3::One)
		,mParent(nullptr)
	{

	}
	Transform::~Transform()
	{

	}
	void Transform::Initalize()
	{
		//cos(180)
	}
	void Transform::Update()
	{
		 //실제 로직상 캐릭터이동 처리
	}
	void Transform::FixedUpdate()
	{
		// 렌더링에 사용될 위치값들을 업데이트

		// 크기 변환 행렬
		Matrix scale = Matrix::CreateScale(mScale);

		// 회전변환 행렬
		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);


		// 이동 변환 행렬
		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mForward = Vector3::TransformNormal(mForward, rotation);
		mRight = Vector3::TransformNormal(mRight, rotation);
		mUp = Vector3::TransformNormal(mUp, rotation);

		// 월드 행렬 생성


		// 카메라 컴포넌트에서 세팅해준다.
		// 뷰 행렬 세팅
		// 프로젝션 행렬 세팅
		
		
		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}

	}
	void Transform::Render()
	{

	}
	void Transform::SetConstantBuffer()
	{
		// 상수버퍼를 가져와서 해당 상수버퍼에
		//SetConstantBuffer(eShaderStage::VS, eCBType::Transform, renderer::triangleConstantBuffer.Get());
		//예시처럼 값을 세팅해줘야 한다.

		renderer::TransformCB trCb = {};
		trCb.world = mWorld;
		trCb.view = Camera::GetViewMatrix();
		trCb.projection = Camera::GetProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->Bind(&trCb);
		cb->SetPipline(eShaderStage::VS);
	}
}