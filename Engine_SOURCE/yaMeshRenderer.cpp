#include "yaMeshRenderer.h"
#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	MeshRenderer::MeshRenderer()
		:BaseRenderer(eComponentType::MeshRenerer)
	{

	}
	MeshRenderer::~MeshRenderer()
	{

	}
	void MeshRenderer::Initalize()
	{

	}
	void MeshRenderer::Update()
	{

	}
	void MeshRenderer::FixedUpdate()
	{

	}
	//�� ���ӿ�����Ʈ���� ������ ȣ��ȴ�.
	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->Bind();

		//�������� �ε��� ���� ����
		GetMesh()->BindBuffer();

		//ȭ�鿡 ������ �ε��� ���۷� �׷��ش�.
		GetMesh()->Render();

		GetMaterial()->Clear();
	}
}