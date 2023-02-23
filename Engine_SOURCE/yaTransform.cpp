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
		 //���� ������ ĳ�����̵� ó��
	}
	void Transform::FixedUpdate()
	{
		// �������� ���� ��ġ������ ������Ʈ

		// ũ�� ��ȯ ���
		Matrix scale = Matrix::CreateScale(mScale);

		// ȸ����ȯ ���
		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);


		// �̵� ��ȯ ���
		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mForward = Vector3::TransformNormal(mForward, rotation);
		mRight = Vector3::TransformNormal(mRight, rotation);
		mUp = Vector3::TransformNormal(mUp, rotation);

		// ���� ��� ����


		// ī�޶� ������Ʈ���� �������ش�.
		// �� ��� ����
		// �������� ��� ����
		
		
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
		// ������۸� �����ͼ� �ش� ������ۿ�
		//SetConstantBuffer(eShaderStage::VS, eCBType::Transform, renderer::triangleConstantBuffer.Get());
		//����ó�� ���� ��������� �Ѵ�.

		renderer::TransformCB trCb = {};
		trCb.world = mWorld;
		trCb.view = Camera::GetViewMatrix();
		trCb.projection = Camera::GetProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->Bind(&trCb);
		cb->SetPipline(eShaderStage::VS);
	}
}