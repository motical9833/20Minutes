#include "yaTransform.h"
#include "yaRenderer.h"
#include "yaCamera.h"
#include "yaTime.h"

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
	{
		
	}

	Transform::~Transform()
	{

	}

	void Transform::Initalize()
	{
		//cos(180);
	}

	void Transform::Update()
	{
		//���� ������ ĳ�����̵� ó��
	}

	void Transform::FixedUpdate()
	{
		//�������� ���� ��ġ������ ������Ʈ

		// ���� ��� ����
		
		// ũ�� ��ȯ ���
		Matrix scale = Matrix::CreateScale(mScale);

		// ȸ�� ��ȯ ���
		Matrix rotation;

		//Vector3 radian(mRotation.x * (XM_PI / 180), mRotation.y * (XM_PI / 180),mRotation.z * (XM_PI / 180));

		//rotation = Matrix::CreateRotationX(radian.x);
		//rotation *= Matrix::CreateRotationY(radian.y);
		//rotation *= Matrix::CreateRotationZ(radian.z);

		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		// �̵� ��ȯ ���
		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;
		mNoScaleWorld = rotation * position;


		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mLeft = Vector3::TransformNormal(Vector3::Left, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		
		// ī�޶� ������Ʈ���� �������ش�
		// ����� ����
		// �������� ��� ����

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

		mParent->setChiled(this);
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
