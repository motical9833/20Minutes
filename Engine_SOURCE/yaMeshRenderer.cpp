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
	//매 게임오브젝트마나 랜더가 호출된다.
	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->Bind();

		//정점버퍼 인덱스 버퍼 세팅
		GetMesh()->BindBuffer();

		//화면에 정해진 인덱스 버퍼로 그려준다.
		GetMesh()->Render();

		GetMaterial()->Clear();
	}
}