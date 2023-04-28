#include "yaMeshRenderer.h"
#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	MeshRenderer::MeshRenderer()
		: BaseRenderer(eComponentType::MeshRenerer)
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

	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->BindSRV();
		GetMesh()->SetData();

		GetMesh()->Render();

		GetMaterial()->Clear();
	}
}
