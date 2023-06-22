#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSceneManager.h"
#include "yaPaintShader.h"
#include "yaParticleShader.h"
#include "yaTime.h"

namespace ya::renderer
{
	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights; 
	StructedBuffer* lightsBuffer = nullptr;

	std::shared_ptr<Texture> postProcessTexture = nullptr;

	void LoadMesh()
	{
#pragma region POINT MESH
		//Point mesh
		Vertex v = {};
		std::shared_ptr<Mesh> pointMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"PointMesh", pointMesh);
		pointMesh->CreateVertexBuffer(&v, 1);
		UINT pointIndex = 0;
		pointMesh->CreateIndexBuffer(&pointIndex, 1);
#pragma endregion
#pragma region RECT MESH
		//RECT
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes, 4);


		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
#pragma endregion
#pragma region DEBUG RECTMESH
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> debugmesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugmesh);
		debugmesh->CreateVertexBuffer(vertexes, 4);
		debugmesh->CreateIndexBuffer(indexes.data(), indexes.size());

#pragma endregion
#pragma region CIRCLE MESH
		// Circle Mesh
		std::vector<Vertex> circleVtxes;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, -0.00001f, 1.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2::Zero;

		circleVtxes.push_back(center);

		int iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;


		for (size_t i = 0; i < iSlice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4
			(
				fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, -0.00001f, 1.0f
			);
			vtx.color = center.color;

			circleVtxes.push_back(vtx);
		}
		indexes.clear();
		for (size_t i = 0; i < iSlice - 2; i++)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		// Crate Mesh
		std::shared_ptr<Mesh> cirlceMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"CircleMesh", cirlceMesh);
		cirlceMesh->CreateVertexBuffer(circleVtxes.data(), circleVtxes.size());
		cirlceMesh->CreateIndexBuffer(indexes.data(), indexes.size());

#pragma endregion
	}

	void LoadShader()
	{
#pragma region DEFAULT TRIANGLE SHADER
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");

		Resources::Insert<Shader>(L"RectShader", shader);
#pragma endregion
#pragma region SPRITE SHADER
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		spriteShader->SetRSState(eRSType::SolidNone);
		Resources::Insert<Shader>(L"SpriteShader", spriteShader);
#pragma endregion
#pragma region UI SHADER
		//std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		//uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		//uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		//Resources::Insert<Shader>(L"UIShader", uiShader);

		std::shared_ptr<Shader> uiSpriteShader = std::make_shared<Shader>();
		uiSpriteShader->Create(eShaderStage::VS, L"UISpriteVS.hlsl", "main");
		uiSpriteShader->Create(eShaderStage::PS, L"UISpritePS.hlsl", "main");
		uiSpriteShader->SetRSState(eRSType::SolidNone);
		Resources::Insert<Shader>(L"UISpriteShader", uiSpriteShader);
#pragma endregion


#pragma region GRID SHADER
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"GridShader", gridShader);
#pragma endregion
#pragma region DEBUG SHADER
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::NoWrite);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Resources::Insert<Shader>(L"DebugShader", debugShader);
#pragma endregion
#pragma region PAINT SHADER
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		Resources::Insert<PaintShader>(L"PaintShader", paintShader);
#pragma endregion
#pragma region PARTICLE SHADER
		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		Resources::Insert<Shader>(L"ParticleShader", particleShader);

		std::shared_ptr<ParticleShader> particleCS = std::make_shared<ParticleShader>();
		Resources::Insert<ParticleShader>(L"ParticleCS", particleCS);
		particleCS->Create(L"ParticleCS.hlsl", "main");
#pragma endregion
#pragma region PLAYER SHADER
		std::shared_ptr<Shader> playerShader = std::make_shared<Shader>();
		playerShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		playerShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"PlayerShader", playerShader);
#pragma endregion
#pragma region MONSTER SHADER
		std::shared_ptr<Shader> monsterShader = std::make_shared<Shader>();
		monsterShader->Create(eShaderStage::VS, L"MonsterVS.hlsl", "main");
		monsterShader->Create(eShaderStage::PS, L"MonsterPS.hlsl", "main");

		Resources::Insert<Shader>(L"MonsterShader", monsterShader);
#pragma endregion
#pragma region LEAVES SHADER
		std::shared_ptr<Shader> leavesShader = std::make_shared<Shader>();
		leavesShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		leavesShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"LeavesShader", leavesShader);
#pragma endregion
#pragma region WEAPON SHADER
		std::shared_ptr<Shader> weaponShader = std::make_shared<Shader>();
		weaponShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		weaponShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"WeaponShader", weaponShader);
#pragma endregion
#pragma region BULLET SHADER
		std::shared_ptr<Shader> bulletShader = std::make_shared<Shader>();
		bulletShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		bulletShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"BulletShader", bulletShader);

		// FadeInOut
		std::shared_ptr<Shader> fadeShader = std::make_shared<Shader>();
		fadeShader->Create(eShaderStage::VS, L"FadeEffectVS.hlsl", "main");
		fadeShader->Create(eShaderStage::PS, L"FadeEffectPS.hlsl", "main");

		Resources::Insert<Shader>(L"FadeShader", fadeShader);


#pragma region POST PROCESS SHADER
		std::shared_ptr<Shader> postProcessShader = std::make_shared<Shader>();
		postProcessShader->Create(eShaderStage::VS, L"PostProcessVS.hlsl", "main");
		postProcessShader->Create(eShaderStage::PS, L"PostProcessPS.hlsl", "main");
		postProcessShader->SetDSState(eDSType::NoWrite);
		Resources::Insert<Shader>(L"PostProcessShader", postProcessShader);
#pragma endregion
	}

	void SetUpState()
	{
#pragma region INPUT LAYOUT
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;


		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());

		//std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		//GetDevice()->CreateInputLayout(arrLayoutDesc, 3
		//	, uiShader->GetVSBlobBufferPointer()
		//	, uiShader->GetVSBlobBufferSize()
		//	, uiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> uiSpriteShader = Resources::Find<Shader>(L"UISpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, uiSpriteShader->GetVSBlobBufferPointer()
			, uiSpriteShader->GetVSBlobBufferSize()
			, uiSpriteShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, gridShader->GetVSBlobBufferPointer()
			, gridShader->GetVSBlobBufferSize()
			, gridShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, debugShader->GetVSBlobBufferPointer()
			, debugShader->GetVSBlobBufferSize()
			, debugShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, particleShader->GetVSBlobBufferPointer()
			, particleShader->GetVSBlobBufferSize()
			, particleShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> playerShader = Resources::Find<Shader>(L"PlayerShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, playerShader->GetVSBlobBufferPointer()
			, playerShader->GetVSBlobBufferSize()
			, playerShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> monsterShader = Resources::Find<Shader>(L"MonsterShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, monsterShader->GetVSBlobBufferPointer()
			, monsterShader->GetVSBlobBufferSize()
			, monsterShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> leavesShader = Resources::Find<Shader>(L"LeavesShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, leavesShader->GetVSBlobBufferPointer()
			, leavesShader->GetVSBlobBufferSize()
			, leavesShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> weaponShader = Resources::Find<Shader>(L"WeaponShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, weaponShader->GetVSBlobBufferPointer()
			, weaponShader->GetVSBlobBufferSize()
			, weaponShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> bulletShader = Resources::Find<Shader>(L"BulletShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, bulletShader->GetVSBlobBufferPointer()
			, bulletShader->GetVSBlobBufferSize()
			, bulletShader->GetInputLayoutAddressOf());

		// FadeInOut
		std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, fadeShader->GetVSBlobBufferPointer()
			, fadeShader->GetVSBlobBufferSize()
			, fadeShader->GetInputLayoutAddressOf());


		std::shared_ptr<Shader> postProcessShader = Resources::Find<Shader>(L"PostProcessShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, postProcessShader->GetVSBlobBufferPointer()
			, postProcessShader->GetVSBlobBufferSize()
			, postProcessShader->GetInputLayoutAddressOf());


#pragma endregion
#pragma region SAMPLER STATE
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;


		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Point].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf()
		);

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point
			, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear
			, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic
			, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer state
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());

#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		blendStates[(UINT)eBSType::Default] = nullptr;

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;

		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());
#pragma endregion
	}

	void LoadBuffer()
	{
#pragma region CONSTANT BUFFER
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
		constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

		constantBuffers[(UINT)eCBType::ParticleSystem] = new ConstantBuffer(eCBType::ParticleSystem);
		constantBuffers[(UINT)eCBType::ParticleSystem]->Create(sizeof(ParticleSystemCB));

		constantBuffers[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffers[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		constantBuffers[(UINT)eCBType::FadeInOut] = new ConstantBuffer(eCBType::FadeInOut);
		constantBuffers[(UINT)eCBType::FadeInOut]->Create(sizeof(FadeInOutCB));
#pragma endregion
#pragma region STRUCTED BUFFER
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 128, eSRVType::SRV, nullptr, true);
#pragma endregion
	}

	void LoadTexture()
	{
#pragma region STATIC TEXTURE
		Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
		Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
		Resources::Load<Texture>(L"CartoonSmoke", L"particle\\CartoonSmoke.png");
		Resources::Load<Texture>(L"noise_01", L"noise\\noise_01.png");
		Resources::Load<Texture>(L"noise_02", L"noise\\noise_02.png");

		Resources::Load<Texture>(L"PlayerSprite", L"Player\\Player.png");
		Resources::Load<Texture>(L"Player_0", L"Player\\Shana.png");
		Resources::Load<Texture>(L"Player_1", L"Player\\T_DiamondSprite.png");
		Resources::Load<Texture>(L"Player_2", L"Player\\T_Scarlett.png");
		Resources::Load<Texture>(L"Player_3", L"Player\\T_HinaSprite.png");
		Resources::Load<Texture>(L"Player_4", L"Player\\T_Spark.png");
		Resources::Load<Texture>(L"Player_5", L"Player\\T_LilithSprite.png");
		Resources::Load<Texture>(L"Player_6", L"Player\\T_AbbySprite.png");
		Resources::Load<Texture>(L"Player_7", L"Player\\T_Yuki.png");
		Resources::Load<Texture>(L"Player_8", L"Player\\T_Luna.png");
		Resources::Load<Texture>(L"Player_9", L"Player\\T_Dasher.png");
		Resources::Load<Texture>(L"T_TileGrass", L"T_TileGrass.png");

		Resources::Load<Texture>(L"Player_10", L"Player\\T_Hastur.png");

		Resources::Load<Texture>(L"LevelUP", L"Player\\T_LevelUpFX.png");
		Resources::Load<Texture>(L"ExpObj", L"T_SmallCircle.png");

		Resources::Load<Texture>(L"MonsterSprite", L"BrainMonster_0.png");
		Resources::Load<Texture>(L"BrainMonster", L"Monster\\BrainMonster.png");
		Resources::Load<Texture>(L"BrainMonsterEye", L"Monster\\BrainMonsterEye.png");
		Resources::Load<Texture>(L"TreeSprite", L"Monster\\T_TreeMonster.png");
		Resources::Load<Texture>(L"EyeMonsterSprite", L"Monster\\EyeMonster.png");
		Resources::Load<Texture>(L"EyeMonsterEye", L"Monster\\EyeMonsterEye.png");
		Resources::Load<Texture>(L"BoomerMonsterSprite", L"Monster\\BigBoomer.png");
		Resources::Load<Texture>(L"BoomerMonster", L"Monster\\BoomerMonster.png");
		Resources::Load<Texture>(L"BoomerMonsterEye", L"Monster\\BoomerMonsterEye.png");
		Resources::Load<Texture>(L"BoomerExplosion", L"Monster\\ExplosionFX.png");
		Resources::Load<Texture>(L"Boss_ShubNiggurat", L"Monster\\Boss_ShubNiggurat.png");
		Resources::Load<Texture>(L"Boss_ShubNigguratEye", L"Monster\\Boss_ShubNigguratEye.png");
		Resources::Load<Texture>(L"Boss_Shoggoth", L"Monster\\Boss_Shoggoth.png");
		Resources::Load<Texture>(L"Boss_ShoggothLaser", L"Monster\\T_ShoggothLaser.png");
		Resources::Load<Texture>(L"Boss_ShoggothLaserWindup", L"Monster\\T_ShoggothLaserWindup.png");


		Resources::Load<Texture>(L"TitleLevesLeftSprite", L"T_TitleLeavesLeft.png");
		Resources::Load<Texture>(L"TitleLevesRightSprite", L"T_TitleLeavesRight.png");
		Resources::Load<Texture>(L"BackGroundTexture", L"BackGround.png");
		Resources::Load<Texture>(L"LogoTexture", L"Logo.png");
		Resources::Load<Texture>(L"W_RevolverSprite", L"Weapon\\T_Revolver_SS.png");
		Resources::Load<Texture>(L"W_MuzzleFlash", L"Weapon\\MuzzleFlash.png");
		Resources::Load<Texture>(L"HPHeart", L"UI\\T_HeartAnimation.png");
		Resources::Load<Texture>(L"BulletTexture", L"Bullet\\BulletEffect.png");
		Resources::Load<Texture>(L"FireEffect", L"Bullet\\FireEffect.png");
		Resources::Load<Texture>(L"M_DeathFX", L"Monster\\T_DeathFX.png");
		Resources::Load<Texture>(L"S_Thunder", L"Skill\\T_Thunder.png");
		Resources::Load<Texture>(L"S_Gale", L"Skill\\T_Gale.png");
		Resources::Load<Texture>(L"S_GhostPet", L"Skill\\T_GhostPet_SS.png");
		Resources::Load<Texture>(L"S_DragonEgg", L"Skill\\T_DragonEgg.png");
		Resources::Load<Texture>(L"S_Dragon", L"Skill\\T_DragonSS.png");
		Resources::Load<Texture>(L"S_Shield", L"Skill\\T_Shield.png");
		Resources::Load<Texture>(L"S_MagicLens", L"Skill\\T_MagicLens.png");
		Resources::Load<Texture>(L"S_Curse", L"Skill\\T_CurseFX.png");
		Resources::Load<Texture>(L"S_Freeze", L"Skill\\T_FreezeFX.png");
		Resources::Load<Texture>(L"S_HolyShieldIdle", L"Skill\\T_HolyShield.png");
		Resources::Load<Texture>(L"S_HolyShieldIHit", L"Skill\\T_HolyShieldRegen.png");
		Resources::Load<Texture>(L"S_HolyShieldBreak", L"Skill\\T_HolyShieldBreak.png");
		Resources::Load<Texture>(L"S_Scythe", L"Skill\\T_Scythe.png");
		Resources::Load<Texture>(L"S_SmiteFX", L"Skill\\T_SmiteFX.png");
		Resources::Load<Texture>(L"S_Spear", L"Skill\\T_Spear.png");
		Resources::Load<Texture>(L"S_ThunderBug", L"Skill\\T_ElectroBug_SS.png");
		Resources::Load<Texture>(L"S_Icicle", L"Skill\\T_Icicle.png");

		Resources::Load<Texture>(L"Icon_Ability_0", L"UI\\Icon\\Icon_TakeAim_0.png");
		Resources::Load<Texture>(L"Icon_Ability_1", L"UI\\Icon\\Icon_Penetrator_1.png");
		Resources::Load<Texture>(L"Icon_Ability_2", L"UI\\Icon\\Icon_Sniper_2.png");
		Resources::Load<Texture>(L"Icon_Ability_3", L"UI\\Icon\\Icon_Assassin_3.png");
		Resources::Load<Texture>(L"Icon_Ability_4", L"UI\\Icon\\Icon_Powershot_4.png");
		Resources::Load<Texture>(L"Icon_Ability_5", L"UI\\Icon\\Icon_BigShot_5.png");
		Resources::Load<Texture>(L"Icon_Ability_6", L"UI\\Icon\\Icon_Splinter_6.png");
		Resources::Load<Texture>(L"Icon_Ability_7", L"UI\\Icon\\Icon_ReaperRounds_7.png");
		Resources::Load<Texture>(L"Icon_Ability_8", L"UI\\Icon\\Icon_DragonEgg_8.png");
		Resources::Load<Texture>(L"Icon_Ability_9", L"UI\\Icon\\Icon_AgedDragon_9.png");
		Resources::Load<Texture>(L"Icon_Ability_10", L"UI\\Icon\\Icon_TrainedDragon_10.png");
		Resources::Load<Texture>(L"Icon_Ability_11", L"UI\\Icon\\Icon_DragonBond_11.png");
		Resources::Load<Texture>(L"Icon_Ability_12", L"UI\\Icon\\Icon_ElectroMagic_12.png");
		Resources::Load<Texture>(L"Icon_Ability_13", L"UI\\Icon\\Icon_ElectroBug_13.png");
		Resources::Load<Texture>(L"Icon_Ability_14", L"UI\\Icon\\Icon_Energized_14.png");
		Resources::Load<Texture>(L"Icon_Ability_15", L"UI\\Icon\\Icon_ElectroMastery_15.png");
		Resources::Load<Texture>(L"Icon_Ability_16", L"UI\\Icon\\Icon_RapidFire_16.png");
		Resources::Load<Texture>(L"Icon_Ability_17", L"UI\\Icon\\Icon_LightBullet_17.png");
		Resources::Load<Texture>(L"Icon_Ability_18", L"UI\\Icon\\Icon_RubberBullets_18.png");
		Resources::Load<Texture>(L"Icon_Ability_19", L"UI\\Icon\\Icon_Siege_19.png");
		Resources::Load<Texture>(L"Icon_Ability_20", L"UI\\Icon\\Icon_GhostFriend_20.png");
		Resources::Load<Texture>(L"Icon_Ability_21", L"UI\\Icon\\Icon_EnergeticFriend.png");
		Resources::Load<Texture>(L"Icon_Ability_22", L"UI\\Icon\\Icon_GhostWizard_22.png");
		Resources::Load<Texture>(L"Icon_Ability_23", L"UI\\Icon\\Icon_VengefulGhost.png");
		Resources::Load<Texture>(L"Icon_Ability_24", L"UI\\Icon\\Icon_Vitality.png");
		Resources::Load<Texture>(L"Icon_Ability_25", L"UI\\Icon\\Icon_AngerPoint.png");
		Resources::Load<Texture>(L"Icon_Ability_26", L"UI\\Icon\\Icon_Giant.png");
		Resources::Load<Texture>(L"Icon_Ability_27", L"UI\\Icon\\Icon_Regeneration.png");
		Resources::Load<Texture>(L"Icon_Ability_28", L"UI\\Icon\\Icon_HolyShield.png");
		Resources::Load<Texture>(L"Icon_Ability_29", L"UI\\Icon\\Icon_DivineBlessing.png");
		Resources::Load<Texture>(L"Icon_Ability_30", L"UI\\Icon\\Icon_DivineWrath.png");
		Resources::Load<Texture>(L"Icon_Ability_31", L"UI\\Icon\\Icon_StalwartShield.png");
		Resources::Load<Texture>(L"Icon_Ability_32", L"UI\\Icon\\Icon_IceMagic.png");
		Resources::Load<Texture>(L"Icon_Ability_33", L"UI\\Icon\\Icon_FrostBit.png");
		Resources::Load<Texture>(L"Icon_Ability_34", L"UI\\Icon\\Icon_IceShard.png");
		Resources::Load<Texture>(L"Icon_Ability_35", L"UI\\Icon\\Icon_Shatter.png");
		Resources::Load<Texture>(L"Icon_Ability_36", L"UI\\Icon\\Icon_MagicLens.png");
		Resources::Load<Texture>(L"Icon_Ability_37", L"UI\\Icon\\Icon_IgnitingLens.png");
		Resources::Load<Texture>(L"Icon_Ability_38", L"UI\\Icon\\Icon_Refraction.png");
		Resources::Load<Texture>(L"Icon_Ability_39", L"UI\\Icon\\Icon_FocalPoint.png");
		Resources::Load<Texture>(L"Icon_Ability_40", L"UI\\Icon\\Icon_Magnetism.png");
		Resources::Load<Texture>(L"Icon_Ability_41", L"UI\\Icon\\Icon_Recharge.png");
		Resources::Load<Texture>(L"Icon_Ability_42", L"UI\\Icon\\Icon_WatchAndLearn.png");
		Resources::Load<Texture>(L"Icon_Ability_43", L"UI\\Icon\\Icon_Excitement.png");
		Resources::Load<Texture>(L"Icon_Ability_44", L"UI\\Icon\\Icon_Haste.png");
		Resources::Load<Texture>(L"Icon_Ability_45", L"UI\\Icon\\Icon_BlazingSpeed.png");
		Resources::Load<Texture>(L"Icon_Ability_46", L"UI\\Icon\\Icon_RunAndGun.png");
		Resources::Load<Texture>(L"Icon_Ability_47", L"UI\\Icon\\Icon_InTheWind.png");
		Resources::Load<Texture>(L"Icon_Ability_48", L"UI\\Icon\\Icon_DoubleShot.png");
		Resources::Load<Texture>(L"Icon_Ability_49", L"UI\\Icon\\Icon_FanFire.png");
		Resources::Load<Texture>(L"Icon_Ability_50", L"UI\\Icon\\Icon_SplitShot.png");
		Resources::Load<Texture>(L"Icon_Ability_51", L"UI\\Icon\\Icon_Fusillade.png");
		Resources::Load<Texture>(L"Icon_Ability_52", L"UI\\Icon\\Icon_FireStarter.png");
		Resources::Load<Texture>(L"Icon_Ability_53", L"UI\\Icon\\Icon_FireMagic.png");
		Resources::Load<Texture>(L"Icon_Ability_54", L"UI\\Icon\\Icon_IntenseBurn.png");
		Resources::Load<Texture>(L"Icon_Ability_55", L"UI\\Icon\\Icon_SoothingWarmth.png");
		Resources::Load<Texture>(L"Icon_Ability_56", L"UI\\Icon\\Icon_QuickHands.png");
		Resources::Load<Texture>(L"Icon_Ability_57", L"UI\\Icon\\Icon_ArmedAndReady.png");
		Resources::Load<Texture>(L"Icon_Ability_58", L"UI\\Icon\\Icon_FreshClip.png");
		Resources::Load<Texture>(L"Icon_Ability_59", L"UI\\Icon\\Icon_KillClip.png");
		Resources::Load<Texture>(L"Icon_Ability_60", L"UI\\Icon\\Icon_Glare.png");
		Resources::Load<Texture>(L"Icon_Ability_61", L"UI\\Icon\\Icon_IntenseGlare.png");
		Resources::Load<Texture>(L"Icon_Ability_62", L"UI\\Icon\\Icon_SightMagic.png");
		Resources::Load<Texture>(L"Icon_Ability_63", L"UI\\Icon\\Icon_Saccade.png");
		Resources::Load<Texture>(L"Icon_Ability_64", L"UI\\Icon\\Icon_MagicScythe.png");
		Resources::Load<Texture>(L"Icon_Ability_65", L"UI\\Icon\\Icon_ShadowScythe.png");
		Resources::Load<Texture>(L"Icon_Ability_66", L"UI\\Icon\\Icon_Windcutter.png");
		Resources::Load<Texture>(L"Icon_Ability_67", L"UI\\Icon\\Icon_ScytheMastery.png");
		Resources::Load<Texture>(L"Icon_Ability_68", L"UI\\Icon\\Icon_DarkArts.png");
		Resources::Load<Texture>(L"Icon_Ability_69", L"UI\\Icon\\Icon_Doom.png");
		Resources::Load<Texture>(L"Icon_Ability_70", L"UI\\Icon\\Icon_Wither.png");
		Resources::Load<Texture>(L"Icon_Ability_71", L"UI\\Icon\\Icon_Ritual.png");
		Resources::Load<Texture>(L"Icon_Ability_72", L"UI\\Icon\\Icon_HolyArts.png");
		Resources::Load<Texture>(L"Icon_Ability_73", L"UI\\Icon\\Icon_HolyMight.png");
		Resources::Load<Texture>(L"Icon_Ability_74", L"UI\\Icon\\Icon_Justice.png");
		Resources::Load<Texture>(L"Icon_Ability_75", L"UI\\Icon\\Icon_Angelic.png");
		Resources::Load<Texture>(L"Icon_Ability_76", L"UI\\Icon\\Icon_AeroMagic.png");
		Resources::Load<Texture>(L"Icon_Ability_77", L"UI\\Icon\\Icon_Windborne.png");
		Resources::Load<Texture>(L"Icon_Ability_78", L"UI\\Icon\\Icon_EyeOfTheStorm.png");
		Resources::Load<Texture>(L"Icon_Ability_79", L"UI\\Icon\\Icon_AeroMastery.png");
		Resources::Load<Texture>(L"Icon_Ability_80", L"UI\\Icon\\Icon_Evasive.png");
		Resources::Load<Texture>(L"Icon_Ability_81", L"UI\\Icon\\Icon_Nimble.png");
		Resources::Load<Texture>(L"Icon_Ability_82", L"UI\\Icon\\Icon_Tiny.png");
		Resources::Load<Texture>(L"Icon_Ability_83", L"UI\\Icon\\Icon_Reflex.png");
		Resources::Load<Texture>(L"Icon_Ability_84", L"UI\\Icon\\Icon_MagicSpear.png");
		Resources::Load<Texture>(L"Icon_Ability_85", L"UI\\Icon\\Icon_HolySpear.png");
		Resources::Load<Texture>(L"Icon_Ability_86", L"UI\\Icon\\Icon_SoulDrain.png");
		Resources::Load<Texture>(L"Icon_Ability_87", L"UI\\Icon\\Icon_SoulKnight.png");
		Resources::Load<Texture>(L"Icon_Ability_88", L"UI\\Icon\\Icon_SoulReap.png");
		Resources::Load<Texture>(L"Icon_Ability_89", L"UI\\Icon\\Icon_SoulConversion.png");
		Resources::Load<Texture>(L"Icon_Ability_90", L"UI\\Icon\\Icon_SoulPowered.png");
		Resources::Load<Texture>(L"Icon_Ability_91", L"UI\\Icon\\Icon_SoulLink.png");
		Resources::Load<Texture>(L"Icon_Ability_92", L"UI\\Icon\\Icon_Trainer.png");
		Resources::Load<Texture>(L"Icon_Ability_93", L"UI\\Icon\\Icon_PulsingSummons.png");
		Resources::Load<Texture>(L"Icon_Ability_94", L"UI\\Icon\\Icon_FeedTheBeasts.png");
		Resources::Load<Texture>(L"Icon_Ability_95", L"UI\\Icon\\Icon_Bloodsuckers.png");
		Resources::Load<Texture>(L"Icon_Ability_96", L"UI\\Icon\\Icon_Frenzy.png");
		Resources::Load<Texture>(L"Icon_Ability_97", L"UI\\Icon\\Icon_Hellspawns.png");
		Resources::Load<Texture>(L"Icon_Ability_98", L"UI\\Icon\\Icon_Electrospawns.png");
		Resources::Load<Texture>(L"Icon_Ability_99", L"UI\\Icon\\Icon_Culling.png");

		Resources::Load<Texture>(L"Icon_Ability_200", L"UI\\Icon\\Icon_DeathPlague.png");
		Resources::Load<Texture>(L"Icon_Ability_201", L"UI\\Icon\\Icon_DeathRounds.png");
		Resources::Load<Texture>(L"Icon_Ability_202", L"UI\\Icon\\Icon_FrostFire.png");
		Resources::Load<Texture>(L"Icon_Ability_203", L"UI\\Icon\\Icon_Generator.png");
		Resources::Load<Texture>(L"Icon_Ability_204", L"UI\\Icon\\Icon_GunMastery.png");
		Resources::Load<Texture>(L"Icon_Ability_205", L"UI\\Icon\\Icon_Kunoichi.png");
		Resources::Load<Texture>(L"Icon_Ability_206", L"UI\\Icon\\Icon_Miniclip.png");
		Resources::Load<Texture>(L"Icon_Ability_207", L"UI\\Icon\\Icon_Overload.png");
		Resources::Load<Texture>(L"Icon_Ability_208", L"UI\\Icon\\Icon_StandYourGround.png");
		Resources::Load<Texture>(L"Icon_Ability_209", L"UI\\Icon\\Icon_SummonMastery.png");
		Resources::Load<Texture>(L"Icon_Ability_210", L"UI\\Icon\\Icon_SwordAndShield.png");
		Resources::Load<Texture>(L"Icon_Ability_211", L"UI\\Icon\\Icon_Titan.png");

		Resources::Load<Texture>(L"Ability_Text_0", L"UI\\Icon\\Text\\TakeAimText_0.png");
		Resources::Load<Texture>(L"Ability_Text_1", L"UI\\Icon\\Text\\PenetratorText_1.png");
		Resources::Load<Texture>(L"Ability_Text_2", L"UI\\Icon\\Text\\SniperText_2.png");
		Resources::Load<Texture>(L"Ability_Text_3", L"UI\\Icon\\Text\\AssassinText_3.png");
		Resources::Load<Texture>(L"Ability_Text_4", L"UI\\Icon\\Text\\PowershotText_4.png");
		Resources::Load<Texture>(L"Ability_Text_5", L"UI\\Icon\\Text\\BigShotText_5.png");
		Resources::Load<Texture>(L"Ability_Text_6", L"UI\\Icon\\Text\\SplinterText_6.png");
		Resources::Load<Texture>(L"Ability_Text_7", L"UI\\Icon\\Text\\ReaperRoundsText_7.png");
		Resources::Load<Texture>(L"Ability_Text_8", L"UI\\Icon\\Text\\DragonEggText_8.png");
		Resources::Load<Texture>(L"Ability_Text_9", L"UI\\Icon\\Text\\AgedDragonText_9.png");
		Resources::Load<Texture>(L"Ability_Text_10", L"UI\\Icon\\Text\\TrainedDragonText_10.png");
		Resources::Load<Texture>(L"Ability_Text_11", L"UI\\Icon\\Text\\DragonBondText_11.png");
		Resources::Load<Texture>(L"Ability_Text_12", L"UI\\Icon\\Text\\ElectroMagicText_12.png");
		Resources::Load<Texture>(L"Ability_Text_13", L"UI\\Icon\\Text\\ElectroBugText_13.png");
		Resources::Load<Texture>(L"Ability_Text_14", L"UI\\Icon\\Text\\EnergizedText_14.png");
		Resources::Load<Texture>(L"Ability_Text_15", L"UI\\Icon\\Text\\ElectroMasteryText_15.png");
		Resources::Load<Texture>(L"Ability_Text_16", L"UI\\Icon\\Text\\RapidFireText_16.png");
		Resources::Load<Texture>(L"Ability_Text_17", L"UI\\Icon\\Text\\LightBulletText_17.png");
		Resources::Load<Texture>(L"Ability_Text_18", L"UI\\Icon\\Text\\RubberBulletsText_18.png");
		Resources::Load<Texture>(L"Ability_Text_19", L"UI\\Icon\\Text\\SiegeText_19.png");
		Resources::Load<Texture>(L"Ability_Text_20", L"UI\\Icon\\Text\\GhostFriendText_20.png");
		Resources::Load<Texture>(L"Ability_Text_21", L"UI\\Icon\\Text\\EnergeticFriendText_21.png");
		Resources::Load<Texture>(L"Ability_Text_22", L"UI\\Icon\\Text\\GhostWizardText_22.png");
		Resources::Load<Texture>(L"Ability_Text_23", L"UI\\Icon\\Text\\VengefulGhostText_23.png");
		Resources::Load<Texture>(L"Ability_Text_24", L"UI\\Icon\\Text\\VitalityText_24.png");
		Resources::Load<Texture>(L"Ability_Text_25", L"UI\\Icon\\Text\\AngerPointText_25.png");
		Resources::Load<Texture>(L"Ability_Text_26", L"UI\\Icon\\Text\\GiantText_26.png");
		Resources::Load<Texture>(L"Ability_Text_27", L"UI\\Icon\\Text\\RegenerationText_27.png");
		Resources::Load<Texture>(L"Ability_Text_28", L"UI\\Icon\\Text\\HolyShieldText_28.png");
		Resources::Load<Texture>(L"Ability_Text_29", L"UI\\Icon\\Text\\DivineBlessingText_29.png");
		Resources::Load<Texture>(L"Ability_Text_30", L"UI\\Icon\\Text\\DivineWrathText_30.png");
		Resources::Load<Texture>(L"Ability_Text_31", L"UI\\Icon\\Text\\StalwartShieldText_31.png");
		Resources::Load<Texture>(L"Ability_Text_32", L"UI\\Icon\\Text\\IceMagicText_32.png");
		Resources::Load<Texture>(L"Ability_Text_33", L"UI\\Icon\\Text\\FrostBitText_33.png");
		Resources::Load<Texture>(L"Ability_Text_34", L"UI\\Icon\\Text\\IceShardText_34.png");
		Resources::Load<Texture>(L"Ability_Text_35", L"UI\\Icon\\Text\\ShatterText_35.png");
		Resources::Load<Texture>(L"Ability_Text_36", L"UI\\Icon\\Text\\MagicLensText_36.png");
		Resources::Load<Texture>(L"Ability_Text_37", L"UI\\Icon\\Text\\IgnitingLensText_37.png");
		Resources::Load<Texture>(L"Ability_Text_38", L"UI\\Icon\\Text\\RefractionText_38.png");
		Resources::Load<Texture>(L"Ability_Text_39", L"UI\\Icon\\Text\\FocalPointText_39.png");
		Resources::Load<Texture>(L"Ability_Text_40", L"UI\\Icon\\Text\\MagnetismText_40.png");
		Resources::Load<Texture>(L"Ability_Text_41", L"UI\\Icon\\Text\\RechargeText_41.png");
		Resources::Load<Texture>(L"Ability_Text_42", L"UI\\Icon\\Text\\WatchAndLearnText_42.png");
		Resources::Load<Texture>(L"Ability_Text_43", L"UI\\Icon\\Text\\ExcitementText_43.png");
		Resources::Load<Texture>(L"Ability_Text_44", L"UI\\Icon\\Text\\HasteText_44.png");
		Resources::Load<Texture>(L"Ability_Text_45", L"UI\\Icon\\Text\\BlazingSpeedText_45.png");
		Resources::Load<Texture>(L"Ability_Text_46", L"UI\\Icon\\Text\\RunAndGunText_46.png");
		Resources::Load<Texture>(L"Ability_Text_47", L"UI\\Icon\\Text\\InTheWindText_47.png");
		Resources::Load<Texture>(L"Ability_Text_48", L"UI\\Icon\\Text\\DoubleShotText_48.png");
		Resources::Load<Texture>(L"Ability_Text_49", L"UI\\Icon\\Text\\FanFireText_49.png");
		Resources::Load<Texture>(L"Ability_Text_50", L"UI\\Icon\\Text\\SplitShotText_50.png");
		Resources::Load<Texture>(L"Ability_Text_51", L"UI\\Icon\\Text\\FusilladeText_51.png");
		Resources::Load<Texture>(L"Ability_Text_52", L"UI\\Icon\\Text\\FireMagicText_52.png");
		Resources::Load<Texture>(L"Ability_Text_53", L"UI\\Icon\\Text\\FireStarterText_53.png");
		Resources::Load<Texture>(L"Ability_Text_54", L"UI\\Icon\\Text\\IntenseBurnText_54.png");
		Resources::Load<Texture>(L"Ability_Text_55", L"UI\\Icon\\Text\\SoothingWarmthText_55.png");
		Resources::Load<Texture>(L"Ability_Text_56", L"UI\\Icon\\Text\\QuickHandsText_56.png");
		Resources::Load<Texture>(L"Ability_Text_57", L"UI\\Icon\\Text\\ArmedAndReadyText_57.png");
		Resources::Load<Texture>(L"Ability_Text_58", L"UI\\Icon\\Text\\FreshClipText_58.png");
		Resources::Load<Texture>(L"Ability_Text_59", L"UI\\Icon\\Text\\KillClipText_59.png");
		Resources::Load<Texture>(L"Ability_Text_60", L"UI\\Icon\\Text\\GlareText_60.png");
		Resources::Load<Texture>(L"Ability_Text_61", L"UI\\Icon\\Text\\IntenseGlareText_61.png");
		Resources::Load<Texture>(L"Ability_Text_62", L"UI\\Icon\\Text\\SightMagicText_62.png");
		Resources::Load<Texture>(L"Ability_Text_63", L"UI\\Icon\\Text\\SaccadeText_63.png");
		Resources::Load<Texture>(L"Ability_Text_64", L"UI\\Icon\\Text\\MagicScytheText_64.png");
		Resources::Load<Texture>(L"Ability_Text_65", L"UI\\Icon\\Text\\ShadowScytheText_65.png");
		Resources::Load<Texture>(L"Ability_Text_66", L"UI\\Icon\\Text\\WindcutterText_66.png");
		Resources::Load<Texture>(L"Ability_Text_67", L"UI\\Icon\\Text\\ScytheMasteryText_67.png");
		Resources::Load<Texture>(L"Ability_Text_68", L"UI\\Icon\\Text\\DarkArtsText_68.png");
		Resources::Load<Texture>(L"Ability_Text_69", L"UI\\Icon\\Text\\DoomText_69.png");
		Resources::Load<Texture>(L"Ability_Text_70", L"UI\\Icon\\Text\\WitherText_70.png");
		Resources::Load<Texture>(L"Ability_Text_71", L"UI\\Icon\\Text\\RitualText_71.png");
		Resources::Load<Texture>(L"Ability_Text_72", L"UI\\Icon\\Text\\HolyArtsText_72.png");
		Resources::Load<Texture>(L"Ability_Text_73", L"UI\\Icon\\Text\\HolyMightText_73.png");
		Resources::Load<Texture>(L"Ability_Text_74", L"UI\\Icon\\Text\\JusticeText_74.png");
		Resources::Load<Texture>(L"Ability_Text_75", L"UI\\Icon\\Text\\AngelicText_75.png");
		Resources::Load<Texture>(L"Ability_Text_76", L"UI\\Icon\\Text\\AeroMagicText_76.png");
		Resources::Load<Texture>(L"Ability_Text_77", L"UI\\Icon\\Text\\WindborneText_77.png");
		Resources::Load<Texture>(L"Ability_Text_78", L"UI\\Icon\\Text\\EyeOfTheStormText_78.png");
		Resources::Load<Texture>(L"Ability_Text_79", L"UI\\Icon\\Text\\AeroMasteryText_79.png");
		Resources::Load<Texture>(L"Ability_Text_80", L"UI\\Icon\\Text\\EvasiveText_80.png");
		Resources::Load<Texture>(L"Ability_Text_81", L"UI\\Icon\\Text\\NimbleText_81.png");
		Resources::Load<Texture>(L"Ability_Text_82", L"UI\\Icon\\Text\\TinyText_82.png");
		Resources::Load<Texture>(L"Ability_Text_83", L"UI\\Icon\\Text\\ReflexText_83.png");
		Resources::Load<Texture>(L"Ability_Text_84", L"UI\\Icon\\Text\\MagicSpearText_84.png");
		Resources::Load<Texture>(L"Ability_Text_85", L"UI\\Icon\\Text\\HolySpearText_85.png");
		Resources::Load<Texture>(L"Ability_Text_86", L"UI\\Icon\\Text\\SoulDrainText_86.png");
		Resources::Load<Texture>(L"Ability_Text_87", L"UI\\Icon\\Text\\SoulKnightText_87.png");
		Resources::Load<Texture>(L"Ability_Text_88", L"UI\\Icon\\Text\\SoulReapText_88.png");
		Resources::Load<Texture>(L"Ability_Text_89", L"UI\\Icon\\Text\\SoulConversionText_89.png");
		Resources::Load<Texture>(L"Ability_Text_90", L"UI\\Icon\\Text\\SoulPoweredText_90.png");
		Resources::Load<Texture>(L"Ability_Text_91", L"UI\\Icon\\Text\\SoulLinkText_91.png");
		Resources::Load<Texture>(L"Ability_Text_92", L"UI\\Icon\\Text\\TrainerText_92.png");
		Resources::Load<Texture>(L"Ability_Text_93", L"UI\\Icon\\Text\\PulsingSummonsText_93.png");
		Resources::Load<Texture>(L"Ability_Text_94", L"UI\\Icon\\Text\\FeedTheBeastsText_94.png");
		Resources::Load<Texture>(L"Ability_Text_95", L"UI\\Icon\\Text\\BloodsuckersText_95.png");
		Resources::Load<Texture>(L"Ability_Text_96", L"UI\\Icon\\Text\\FrenzyText_96.png");
		Resources::Load<Texture>(L"Ability_Text_97", L"UI\\Icon\\Text\\HellspawnsText_97.png");
		Resources::Load<Texture>(L"Ability_Text_98", L"UI\\Icon\\Text\\ElectrospawnsText_98.png");
		Resources::Load<Texture>(L"Ability_Text_99", L"UI\\Icon\\Text\\CullingText_99.png");



		Resources::Load<Texture>(L"Yiki_Ability_0", L"UI\\Icon\\Icon_ButterflyDance.png");
		Resources::Load<Texture>(L"Yiki_Ability_1", L"UI\\Icon\\Icon_Brittle.png");
		Resources::Load<Texture>(L"Yiki_Ability_2", L"UI\\Icon\\Icon_PairUp.png");
		//Resources::Load<Texture>(L"Hastur_Ability_0", L"UI\\Icon\\Icon_Smash.png");
		//Resources::Load<Texture>(L"Hastur_Ability_1", L"UI\\Icon\\Icon_AbyssalCall.png");
		//Resources::Load<Texture>(L"Hastur_Ability_2", L"UI\\Icon\\Icon_Frenz.png");
		Resources::Load<Texture>(L"Shana_Ability_0", L"UI\\Icon\\Icon_QuickLearner.png");
		Resources::Load<Texture>(L"Shana_Ability_1", L"UI\\Icon\\Icon_Ascension.png");
		Resources::Load<Texture>(L"Shana_Ability_2", L"UI\\Icon\\Icon_Halo_Piece1.png");
		Resources::Load<Texture>(L"Shana_Ability_3", L"UI\\Icon\\Icon_Halo_Piece2.png");
		Resources::Load<Texture>(L"Shana_Ability_4", L"UI\\Icon\\Icon_Halo_Piece3.png");
		Resources::Load<Texture>(L"Shana_Ability_5", L"UI\\Icon\\Icon_Shanas_Halo.png");
		Resources::Load<Texture>(L"Shana_Ability_6", L"UI\\Icon\\Icon_Specialize.png");
		Resources::Load<Texture>(L"Diamond_Ability_0", L"UI\\Icon\\Icon_Berserk.png");
		Resources::Load<Texture>(L"Diamond_Ability_1", L"UI\\Icon\\Icon_Bulk_Up.png");
		Resources::Load<Texture>(L"Diamond_Ability_2", L"UI\\Icon\\Icon_Iron_Will.png");
		Resources::Load<Texture>(L"Abby_Ability_0", L"UI\\Icon\\Icon_Bullet_Storm.png");
		Resources::Load<Texture>(L"Abby_Ability_1", L"UI\\Icon\\Icon_Make_It_Rain.png");
		Resources::Load<Texture>(L"Abby_Ability_2", L"UI\\Icon\\Icon_Whirlwind.png");
		Resources::Load<Texture>(L"Spark_Ability_0", L"UI\\Icon\\Icon_Charged_Up.png");
		Resources::Load<Texture>(L"Spark_Ability_1", L"UI\\Icon\\Icon_Electro_Affinity.png");
		Resources::Load<Texture>(L"Spark_Ability_2", L"UI\\Icon\\Icon_Electrical_fire.png");
		Resources::Load<Texture>(L"Luna_Ability_0", L"UI\\Icon\\Icon_Implosion.png");
		Resources::Load<Texture>(L"Luna_Ability_2", L"UI\\Icon\\Icon_CosmicBurst.png");
		Resources::Load<Texture>(L"Luna_Ability_1", L"UI\\Icon\\Icon_ParallelStar.png");
		Resources::Load<Texture>(L"Dasher_Ability_0", L"UI\\Icon\\Icon_DeerFriend.png");
		Resources::Load<Texture>(L"Dasher_Ability_1", L"UI\\Icon\\Icon_HailBringer.png");
		Resources::Load<Texture>(L"Dasher_Ability_2", L"UI\\Icon\\Icon_NaturesBlessing.png");
		Resources::Load<Texture>(L"Hina_Ability_0", L"UI\\Icon\\Icon_Enhanced_Shadow.png");
		Resources::Load<Texture>(L"Hina_Ability_1", L"UI\\Icon\\Icon_Hidden_Bladee.png");
		Resources::Load<Texture>(L"Hina_Ability_2", L"UI\\Icon\\Icon_Maneuver.png");
		Resources::Load<Texture>(L"Lilith_Ability_0", L"UI\\Icon\\Icon_Undead_Army.png");
		Resources::Load<Texture>(L"Lilith_Ability_1", L"UI\\Icon\\Icon_Necromancer.png");
		Resources::Load<Texture>(L"Lilith_Ability_2", L"UI\\Icon\\Icon_Necrophile.png");
		Resources::Load<Texture>(L"Raven_Ability_0", L"UI\\Icon\\Icon_ShadowFlame.png");
		Resources::Load<Texture>(L"Raven_Ability_1", L"UI\\Icon\\Icon_FlockOfCrows.png");
		Resources::Load<Texture>(L"Raven_Ability_2", L"UI\\Icon\\Icon_ShadowAffinity.png");
		Resources::Load<Texture>(L"Scarlett_Ability_0", L"UI\\Icon\\Icon_Lasting_Flame.png");
		Resources::Load<Texture>(L"Scarlett_Ability_1", L"UI\\Icon\\Icon_Pyromaniac.png");
		Resources::Load<Texture>(L"Scarlett_Ability_2", L"UI\\Icon\\Icon_Pyro_Affinity.png");
		Resources::Load<Texture>(L"Book_Ability_0", L"UI\\Icon\\Icon_TomeOfElasticity.png");
		Resources::Load<Texture>(L"Book_Ability_1", L"UI\\Icon\\Icon_TomeOfElements.png");
		Resources::Load<Texture>(L"Book_Ability_2", L"UI\\Icon\\Icon_TomeOfSpeed.png");
		Resources::Load<Texture>(L"Book_Ability_3", L"UI\\Icon\\Icon_TomePower.png");
		Resources::Load<Texture>(L"Book_Ability_4", L"UI\\Icon\\Icon_TomeRage.png");
		Resources::Load<Texture>(L"Book_Ability_5", L"UI\\Icon\\Icon_TomeSummoning.png");

		Resources::Load<Texture>(L"Cursor", L"UI\\T_CursorSprite.png");
		Resources::Load<Texture>(L"PowerupFrame", L"UI\\Icon\\PowerupFrame.png");
		Resources::Load<Texture>(L"PowerupFrame_Large", L"UI\\Icon\\PowerupFrame_Large.png");
		Resources::Load<Texture>(L"PowerupIconBG", L"UI\\Icon\\PowerupIconBG.png");
		Resources::Load<Texture>(L"UIPanel", L"UI\\T_UIPanel.png");
		Resources::Load<Texture>(L"UIPanelOrigin", L"UI\\T_UIPanelOrigin.png");
		Resources::Load<Texture>(L"LeftDownArrows", L"UI\\T_PowerupTreeArrows_0.png");
		Resources::Load<Texture>(L"RightDownArrows", L"UI\\T_PowerupTreeArrows_1.png");
		Resources::Load<Texture>(L"DownRightArrows", L"UI\\T_PowerupTreeArrows_2.png");
		Resources::Load<Texture>(L"DownLeftArrows", L"UI\\T_PowerupTreeArrows_3.png");
		Resources::Load<Texture>(L"AmmoIcon", L"UI\\T_AmmoIcon.png");
		Resources::Load<Texture>(L"ReloadBar", L"UI\\ReloadBar.png");
		Resources::Load<Texture>(L"ReloadBut", L"UI\\ReloadBut.png");
		Resources::Load<Texture>(L"LevelGaugeZero", L"UI\\LevelGaugeZero.png");
		Resources::Load<Texture>(L"LevelGauge", L"UI\\LevelGauge.png");
		Resources::Load<Texture>(L"T_EyeBlink", L"UI\\T_EyeBlink.png");
		Resources::Load<Texture>(L"T_SelectorBubble", L"UI\\T_SelectorBubble.png");
		Resources::Load<Texture>(L"T_SelectScreenPanelUP", L"UI\\T_SelectScreenPanelUP.png");
		Resources::Load<Texture>(L"T_SelectScreenPanelDown", L"UI\\T_SelectScreenPanelDown.png");
		Resources::Load<Texture>(L"T_UISmallPanel", L"UI\\T_UISmallPanel.png");
		Resources::Load<Texture>(L"T_RoundedRect", L"UI\\T_RoundedRect.png");
		Resources::Load<Texture>(L"T_UILock", L"UI\\T_UILock.png");

		Resources::Load<Texture>(L"StartRedBut", L"UI\\StartRedBut.png");
		Resources::Load<Texture>(L"StartWhiteBut", L"UI\\StartWhiteBut.png");
		Resources::Load<Texture>(L"LanguageRed", L"UI\\LanguageRed.png");
		Resources::Load<Texture>(L"LanguageWhite", L"UI\\LanguageWhite.png");
		Resources::Load<Texture>(L"SettingRedBut", L"UI\\SettingRedBut.png");
		Resources::Load<Texture>(L"SettingWhiteBut", L"UI\\SettingWhiteBut.png");
		Resources::Load<Texture>(L"ExitRedBut", L"UI\\ExitRedBut.png");
		Resources::Load<Texture>(L"ExitWhiteBut", L"UI\\ExitWhiteBut.png");
		Resources::Load<Texture>(L"BackwardsRed", L"UI\\BackwardsRed.png");
		Resources::Load<Texture>(L"BackwardsWhite", L"UI\\BackwardsWhite.png");
		Resources::Load<Texture>(L"BackButRed", L"UI\\BackButRed.png");
		Resources::Load<Texture>(L"BackButWhite", L"UI\\BackButWhite.png");
		Resources::Load<Texture>(L"RefreshRed", L"UI\\RefreshRed.png");
		Resources::Load<Texture>(L"RefreshWhite", L"UI\\RefreshWhite.png");
		Resources::Load<Texture>(L"SelectPanalRed", L"UI\\SelectPanalRed.png");
		Resources::Load<Texture>(L"SelectPanalWhite", L"UI\\SelectPanalWhite.png");
		Resources::Load<Texture>(L"FollowingRed", L"UI\\FollowingRed.png");
		Resources::Load<Texture>(L"FollowingWhite", L"UI\\FollowingWhite.png");
		Resources::Load<Texture>(L"GiveUPRed", L"UI\\GiveUPRed.png");
		Resources::Load<Texture>(L"GiveUpWhite", L"UI\\GiveUpWhite.png");

		Resources::Load<Texture>(L"Survival", L"UI\\Survival.png");
		Resources::Load<Texture>(L"DeadRed", L"UI\\DeadRed.png");
		Resources::Load<Texture>(L"ReStartRed", L"UI\\ReStartRed.png");
		Resources::Load<Texture>(L"ReStartWhite", L"UI\\ReStartWhite.png");
		Resources::Load<Texture>(L"MainMenuRed", L"UI\\MainMenuRed.png");
		Resources::Load<Texture>(L"MainMenuWhite", L"UI\\MainMenuWhite.png");


		Resources::Load<Texture>(L"RuneRed", L"UI\\RuneRed.png");
		Resources::Load<Texture>(L"RuneWhite", L"UI\\RuneWhite.png");
		Resources::Load<Texture>(L"CoinTextBox", L"UI\\CoinTextBox.png");

		Resources::Load<Texture>(L"LevelText", L"UI\\LevelText.png");

		Resources::Load<Texture>(L"BulletText_0", L"UI\\BulletText\\Bullet_Zero.png");
		Resources::Load<Texture>(L"BulletText_1", L"UI\\BulletText\\Bullet_One.png");
		Resources::Load<Texture>(L"BulletText_2", L"UI\\BulletText\\Bullet_Two.png");
		Resources::Load<Texture>(L"BulletText_3", L"UI\\BulletText\\Bullet_three.png");
		Resources::Load<Texture>(L"BulletText_4", L"UI\\BulletText\\Bullet_four.png");
		Resources::Load<Texture>(L"BulletText_5", L"UI\\BulletText\\Bullet_five.png");
		Resources::Load<Texture>(L"BulletText_6", L"UI\\BulletText\\Bullet_six.png");
		Resources::Load<Texture>(L"BulletText_7", L"UI\\BulletText\\Bullet_seven.png");
		Resources::Load<Texture>(L"BulletText_8", L"UI\\BulletText\\Bullet_eight.png");
		Resources::Load<Texture>(L"BulletText_9", L"UI\\BulletText\\Bullet_nine.png");
		Resources::Load<Texture>(L"BulletUISlash", L"UI\\BulletText\\BulletUISlash.png");

		Resources::Load<Texture>(L"Time_0", L"UI\\TimeAndLevel\\Time_0.png");
		Resources::Load<Texture>(L"Time_1", L"UI\\TimeAndLevel\\Time_1.png");
		Resources::Load<Texture>(L"Time_2", L"UI\\TimeAndLevel\\Time_2.png");
		Resources::Load<Texture>(L"Time_3", L"UI\\TimeAndLevel\\Time_3.png");
		Resources::Load<Texture>(L"Time_4", L"UI\\TimeAndLevel\\Time_4.png");
		Resources::Load<Texture>(L"Time_5", L"UI\\TimeAndLevel\\Time_5.png");
		Resources::Load<Texture>(L"Time_6", L"UI\\TimeAndLevel\\Time_6.png");
		Resources::Load<Texture>(L"Time_7", L"UI\\TimeAndLevel\\Time_7.png");
		Resources::Load<Texture>(L"Time_8", L"UI\\TimeAndLevel\\Time_8.png");
		Resources::Load<Texture>(L"Time_9", L"UI\\TimeAndLevel\\Time_9.png");
		Resources::Load<Texture>(L"Time_spot", L"UI\\TimeAndLevel\\Time_spot.png");



		Resources::Load<Texture>(L"Map_0", L"UI\\DarkforestNone.png");
		Resources::Load<Texture>(L"Map_1", L"UI\\DarkforestSelect.png");
		Resources::Load<Texture>(L"Map_2", L"UI\\TempleNone.png");
		Resources::Load<Texture>(L"Map_3", L"UI\\TempleSelect.png");
		Resources::Load<Texture>(L"Map_4", L"UI\\PumpkinNone.png");
		Resources::Load<Texture>(L"Map_5", L"UI\\PumpkinSelect.png");

		Resources::Load<Texture>(L"Face_0", L"UI\\Face\\T_Shana_Portrait.png");
		Resources::Load<Texture>(L"Face_1", L"UI\\Face\\T_Diamond_Portrait.png");
		Resources::Load<Texture>(L"Face_2", L"UI\\Face\\T_Scarlett_Portrait.png");
		Resources::Load<Texture>(L"Face_3", L"UI\\Face\\T_Hina_Portrait.png");
		Resources::Load<Texture>(L"Face_4", L"UI\\Face\\T_Spark_Portrait.png");
		Resources::Load<Texture>(L"Face_5", L"UI\\Face\\T_Lilith_Portrait.png");
		Resources::Load<Texture>(L"Face_6", L"UI\\Face\\T_Abby_Portrait.png");
		Resources::Load<Texture>(L"Face_7", L"UI\\Face\\T_Yuki_Portrait.png");
		Resources::Load<Texture>(L"Face_8", L"UI\\Face\\T_Luna_Portrait.png");
		Resources::Load<Texture>(L"Face_9", L"UI\\Face\\T_Dasher_Portrait.png");

		Resources::Load<Texture>(L"FaceText_0", L"UI\\Face\\ShanaText.png");
		Resources::Load<Texture>(L"FaceText_1", L"UI\\Face\\DiamondText.png");
		Resources::Load<Texture>(L"FaceText_2", L"UI\\Face\\ScarlettText.png");
		Resources::Load<Texture>(L"FaceText_3", L"UI\\Face\\HinaText.png");
		Resources::Load<Texture>(L"FaceText_4", L"UI\\Face\\SparkText.png");
		Resources::Load<Texture>(L"FaceText_5", L"UI\\Face\\LilithText.png");
		Resources::Load<Texture>(L"FaceText_6", L"UI\\Face\\AbbyText.png");
		Resources::Load<Texture>(L"FaceText_7", L"UI\\Face\\YukiText.png");
		Resources::Load<Texture>(L"FaceText_8", L"UI\\Face\\LunaText.png");
		Resources::Load<Texture>(L"FaceText_9", L"UI\\Face\\DasherText.png");

		Resources::Load<Texture>(L"Weapon_0", L"UI\\Weapon\\RevolverStill.png");
		Resources::Load<Texture>(L"Weapon_1", L"UI\\Weapon\\T_Shotgun_SS_0.png");
		Resources::Load<Texture>(L"Weapon_2", L"UI\\Weapon\\T_Crossbow_SS_0.png");
		Resources::Load<Texture>(L"Weapon_3", L"UI\\Weapon\\SMGStill.png");
		Resources::Load<Texture>(L"Weapon_4", L"UI\\Weapon\\T_BatGun_SS_0.png");
		Resources::Load<Texture>(L"Weapon_5", L"UI\\Weapon\\T_FlameCannon_SS_0.png");
		Resources::Load<Texture>(L"Weapon_6", L"UI\\Weapon\\GrenadeLauncherStill.png");
		Resources::Load<Texture>(L"Weapon_7", L"UI\\Weapon\\BowStill.png");

		Resources::Load<Texture>(L"noise_03", L"noise\\noise_03.jpg");
		Resources::Load<Texture>(L"noise_04", L"noise\\noise_04.jpg");

#pragma endregion
#pragma region DYNAMIC TEXTURE
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM
			, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert<Texture>(L"PaintTexture", uavTexture);


		//noise
		postProcessTexture = std::make_shared<Texture>();
		postProcessTexture->Create(1600, 900, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE);
		postProcessTexture->BindShaderResource(eShaderStage::PS, 60);

#pragma endregion
	}

	void LoadMaterial()
	{

#pragma region DEFAULT MATERIAL
		CreateMaterial(L"PaintTexture", L"RectShader", eRenderingMode::Transparent, L"RectMaterial");
#pragma endregion
#pragma region SPRITE MATERIAL
		CreateMaterial(L"DefaultSprite", L"SpriteShader", eRenderingMode::Transparent, L"SpriteMaterial");
#pragma endregion
#pragma region UI MATERIAL
		CreateMaterial(L"HPBarTexture", L"UIShader", eRenderingMode::Transparent, L"UIMaterial");
#pragma endregion
#pragma region GRID MATERIAL
		CreateMaterial(L"GridShader", L"GridMaterial");
#pragma endregion
#pragma region DEBUG MATERIAL
		CreateMaterial(L"DebugShader", eRenderingMode::Transparent, L"DebugMaterial");
#pragma endregion
#pragma region PARTICLE MATERIAL
		CreateMaterial(L"ParticleShader", eRenderingMode::Transparent, L"ParticleMaterial");
#pragma endregion
#pragma region PLAYER MATERIAL
		CreateMaterial(L"PlayerSprite", L"PlayerShader", eRenderingMode::Transparent, L"PlayerMaterial");
#pragma endregion
#pragma region DEFAULT MATERIAL
		CreateMaterial(L"MonsterSprite", L"MonsterShader", eRenderingMode::Transparent, L"MonsterMaterial");

		CreateMaterial(L"BrainMonster", L"MonsterShader", eRenderingMode::Opaque, L"BrainMonsterMaterial");
		CreateMaterial(L"BrainMonsterEye", L"UISpriteShader", eRenderingMode::Transparent, L"BrainMonsterEyeMaterial");
#pragma endregion
#pragma region MONSTERS MATERIAL
		// TreeMonster
		CreateMaterial(L"TreeSprite", L"MonsterShader", eRenderingMode::Transparent, L"TreeMaterial");

		// EyeMonster
		CreateMaterial(L"EyeMonsterSprite", L"MonsterShader", eRenderingMode::Opaque, L"EyeMonsterMaterial");
		CreateMaterial(L"EyeMonsterEye", L"UISpriteShader", eRenderingMode::Transparent, L"EyeMonsterEyeMaterial");

		// BoomerMonster
		CreateMaterial(L"BoomerMonsterSprite", L"MonsterShader", eRenderingMode::Transparent, L"BoomerMonsterMaterial");

		CreateMaterial(L"BoomerMonster", L"MonsterShader", eRenderingMode::Opaque, L"BoomerMaterial");
		CreateMaterial(L"BoomerMonsterEye", L"UISpriteShader", eRenderingMode::Transparent, L"BoomerEyeMaterial");

		//BoomerExplosion
		//Resources::Load<Texture>(L"Boss_ShubNiggurat", L"Monster\\Boss_ShubNiggurat.png");

		CreateMaterial(L"Boss_ShubNiggurat", L"MonsterShader", eRenderingMode::Opaque, L"ShubNigguratMaterial");
		CreateMaterial(L"Boss_ShubNigguratEye", L"UISpriteShader", eRenderingMode::Transparent, L"ShubNigguratEyeMaterial");

		CreateMaterial(L"Boss_Shoggoth", L"MonsterShader", eRenderingMode::Transparent, L"ShoggothMaterial");
		CreateMaterial(L"Boss_ShoggothLaser", L"MonsterShader", eRenderingMode::Transparent, L"LaserMaterial");
		CreateMaterial(L"Boss_ShoggothLaserWindup", L"MonsterShader", eRenderingMode::Transparent, L"LaserWindupMaterial");

#pragma endregion
#pragma region WEAPON MATERIAL
		// Revolver
		CreateMaterial(L"W_RevolverSprite", L"SpriteShader", eRenderingMode::Transparent, L"RevolverMaterial");
		CreateMaterial(L"W_MuzzleFlash", L"SpriteShader", eRenderingMode::Transparent, L"MuzzleFlashMaterial");

		// Bullet
		CreateMaterial(L"BulletTexture", L"SpriteShader", eRenderingMode::Transparent, L"BulletMaterial");

#pragma endregion
#pragma region UI MATERIAL
		CreateMaterial(L"TitleLevesLeftSprite", L"SpriteShader", eRenderingMode::Opaque, L"leavsLeftMaterial");

		CreateMaterial(L"TitleLevesRightSprite", L"SpriteShader", eRenderingMode::Opaque, L"leavsRightMaterial");

		CreateMaterial(L"BackGroundTexture", L"SpriteShader", eRenderingMode::Opaque, L"backgroundMaterial");

		CreateMaterial(L"LogoTexture", L"SpriteShader", eRenderingMode::Opaque, L"LogoMaterial");

		CreateMaterial(L"UIPanel", L"UISpriteShader", eRenderingMode::Opaque, L"PanalMaterial");
		CreateMaterial(L"UIPanelOrigin", L"UISpriteShader", eRenderingMode::Opaque, L"PanelOriginMaterial");

		CreateMaterial(L"StartRedBut", L"UISpriteShader", eRenderingMode::Opaque, L"StartRedMaterial");
		CreateMaterial(L"StartWhiteBut", L"UISpriteShader", eRenderingMode::Opaque, L"StartWhiteMaterial");
		CreateMaterial(L"LanguageRed", L"UISpriteShader", eRenderingMode::Opaque, L"LanguageRedMaterial");
		CreateMaterial(L"LanguageWhite", L"UISpriteShader", eRenderingMode::Opaque, L"LanguageWhiteMaterial");
		CreateMaterial(L"SettingRedBut", L"UISpriteShader", eRenderingMode::Opaque, L"SettingRedMaterial");
		CreateMaterial(L"SettingWhiteBut", L"UISpriteShader", eRenderingMode::Opaque, L"SettingWhiteMaterial");
		CreateMaterial(L"ExitRedBut", L"UISpriteShader", eRenderingMode::Opaque, L"ExitRedMaterial");
		CreateMaterial(L"ExitWhiteBut", L"UISpriteShader", eRenderingMode::Opaque, L"ExitWhiteMaterial");
		CreateMaterial(L"BackwardsRed", L"UISpriteShader", eRenderingMode::Opaque, L"BackwardsRedMaterial");
		CreateMaterial(L"BackwardsWhite", L"UISpriteShader", eRenderingMode::Opaque, L"BackwardsWhiteMaterial");
		CreateMaterial(L"BackButRed", L"UISpriteShader", eRenderingMode::Opaque, L"BackButRedMaterial");
		CreateMaterial(L"BackButWhite", L"UISpriteShader", eRenderingMode::Opaque, L"BackButWhiteMaterial");

		CreateMaterial(L"RefreshRed", L"UISpriteShader", eRenderingMode::Opaque, L"RefreshRedMaterial");
		CreateMaterial(L"RefreshWhite", L"UISpriteShader", eRenderingMode::Opaque, L"RefreshWhiteMaterial");
		CreateMaterial(L"SelectPanalRed", L"UISpriteShader", eRenderingMode::Opaque, L"SelectPanalRedMaterial");
		CreateMaterial(L"SelectPanalWhite", L"UISpriteShader", eRenderingMode::Opaque, L"SelectPanalWhiteMaterial");

		CreateMaterial(L"RuneRed", L"UISpriteShader", eRenderingMode::Opaque, L"RuneRedMaterial");
		CreateMaterial(L"RuneWhite", L"UISpriteShader", eRenderingMode::Opaque, L"RuneWhiteMaterial");
		CreateMaterial(L"CoinTextBox", L"UISpriteShader", eRenderingMode::Opaque, L"CoinTextBoxMaterial");

		CreateMaterial(L"LeftDownArrows", L"UISpriteShader", eRenderingMode::Opaque, L"LeftDownLeaderMaterial");
		CreateMaterial(L"RightDownArrows", L"UISpriteShader", eRenderingMode::Opaque, L"RightDownLeaderMaterial");
		CreateMaterial(L"DownRightArrows", L"UISpriteShader", eRenderingMode::Opaque, L"DownRightLeaderMaterial");
		CreateMaterial(L"DownLeftArrows", L"UISpriteShader", eRenderingMode::Opaque, L"DownLeftLeaderMaterial");
		CreateMaterial(L"PowerupFrame", L"UISpriteShader", eRenderingMode::Opaque, L"PowerupFrameMaterial");

		CreateMaterial(L"PowerupIconBG", L"UISpriteShader", eRenderingMode::Opaque, L"PowerupIconBGMaterial");

		CreateMaterial(L"ReloadBar", L"UISpriteShader", eRenderingMode::Opaque, L"ReloadBarMaterial");
		CreateMaterial(L"ReloadBut", L"UISpriteShader", eRenderingMode::Opaque, L"ReloadButMaterial");

		CreateMaterial(L"LevelGaugeZero", L"UISpriteShader", eRenderingMode::Opaque, L"LevelGaugeZeroMaterial");
		CreateMaterial(L"LevelGauge", L"UISpriteShader", eRenderingMode::Opaque, L"LevelGaugeMaterial");


		CreateMaterial(L"T_EyeBlink", L"SpriteShader", eRenderingMode::Opaque, L"EyeBlinkMaterial");
		CreateMaterial(L"T_SelectorBubble", L"SpriteShader", eRenderingMode::Opaque, L"SelectorBubbleMaterial");
		CreateMaterial(L"T_SelectScreenPanelUP", L"SpriteShader", eRenderingMode::Opaque, L"SelectScreenPanelUPMaterial");
		CreateMaterial(L"T_SelectScreenPanelDown", L"SpriteShader", eRenderingMode::Opaque, L"SelectScreenPanelDownMaterial");
		CreateMaterial(L"T_UISmallPanel", L"SpriteShader", eRenderingMode::Opaque, L"UISmallPanelMaterial");
		CreateMaterial(L"T_RoundedRect", L"SpriteShader", eRenderingMode::Opaque, L"RoundedRectMaterial");
		CreateMaterial(L"T_UILock", L"SpriteShader", eRenderingMode::Opaque, L"UILockMaterial");
		CreateMaterial(L"T_TileGrass", L"SpriteShader", eRenderingMode::Opaque, L"Tile_0Material");


		CreateMaterial(L"Cursor", L"UISpriteShader", eRenderingMode::Transparent, L"CursorMaterial");

		CreateMaterial(L"LevelText", L"UISpriteShader", eRenderingMode::Opaque, L"LevelTextMaterial");
		CreateMaterial(L"FollowingRed", L"UISpriteShader", eRenderingMode::Opaque, L"FollowingRedMaterial");
		CreateMaterial(L"FollowingWhite", L"UISpriteShader", eRenderingMode::Opaque, L"FollowingWhiteMaterial");
		CreateMaterial(L"GiveUPRed", L"UISpriteShader", eRenderingMode::Opaque, L"GiveUPRedMaterial");
		CreateMaterial(L"GiveUpWhite", L"UISpriteShader", eRenderingMode::Opaque, L"GiveUpWhiteMaterial");

		CreateMaterial(L"Survival", L"UISpriteShader", eRenderingMode::Opaque, L"SurvivalMaterial");
		CreateMaterial(L"DeadRed", L"UISpriteShader", eRenderingMode::Opaque, L"DeadRedMaterial");
		CreateMaterial(L"ReStartRed", L"UISpriteShader", eRenderingMode::Opaque, L"ReStartRedMaterial");
		CreateMaterial(L"ReStartWhite", L"UISpriteShader", eRenderingMode::Opaque, L"ReStartWhiteMaterial");
		CreateMaterial(L"MainMenuRed", L"UISpriteShader", eRenderingMode::Opaque, L"MainMenuRedMaterial");
		CreateMaterial(L"MainMenuWhite", L"UISpriteShader", eRenderingMode::Opaque, L"MainMenuWhiteMaterial");

#pragma endregion
#pragma region FACE MATERIAL

		for (size_t i = 0; i < 10; i++)
		{
			const std::wstring faceName = L"Face_" + std::to_wstring(i);

			CreateMaterial(faceName, L"SpriteShader", eRenderingMode::Opaque, faceName + L"Material");
		}
		for (size_t i = 0; i < 10; i++)
		{
			const std::wstring faceText = L"FaceText_" + std::to_wstring(i);

			CreateMaterial(faceText, L"SpriteShader", eRenderingMode::Opaque, faceText + L"Material");
		}
		for (size_t i = 0; i < 8; i++)
		{
			const std::wstring weaponName = L"Weapon_" + std::to_wstring(i);

			CreateMaterial(weaponName, L"SpriteShader", eRenderingMode::Opaque, weaponName + L"Material");
		}

		CreateMaterial(L"T_UILock", L"SpriteShader", eRenderingMode::Opaque, L"UILockMaterial");

#pragma region MAP MATERIAL
		for (size_t i = 0; i < 6; i++)
		{
			const std::wstring mapName = L"Map_" + std::to_wstring(i);

			CreateMaterial(mapName, L"SpriteShader", eRenderingMode::Opaque, mapName + L"Material");
		}
#pragma endregion


#pragma endregion

		for (size_t i = 0; i < 100; i++)
		{
			const std::wstring name = L"Icon_Ability_" + std::to_wstring(i);


			CreateMaterial(name, L"UISpriteShader", eRenderingMode::Opaque, name + L"Material");
		}

		//Ability_Text_99
		for (size_t i = 0; i < 100; i++)
		{
			const std::wstring text = L"Ability_Text_" + std::to_wstring(i);


			CreateMaterial(text, L"UISpriteShader", eRenderingMode::Opaque, text + L"Material");
		}

		for (size_t i = 0; i < 10; i++)
		{
			const std::wstring text = L"BulletText_" + std::to_wstring(i);


			CreateMaterial(text, L"UISpriteShader", eRenderingMode::Opaque, text + L"Material");
		}

		CreateMaterial(L"BulletUISlash", L"UISpriteShader", eRenderingMode::Opaque, L"BulletUISlashMaterial");


		for (size_t i = 0; i < 10; i++)
		{
			const std::wstring text = L"Time_" + std::to_wstring(i);


			CreateMaterial(text, L"UISpriteShader", eRenderingMode::Opaque, text + L"Material");
		}
		CreateMaterial(L"Time_spot", L"UISpriteShader", eRenderingMode::Opaque, L"Time_spotMaterial");



		CreateMaterial(L"AmmoIcon", L"UISpriteShader", eRenderingMode::Opaque, L"AmmoIconMaterial");

#pragma endregion
#pragma region PlayerUI
		CreateMaterial(L"HPHeart", L"UISpriteShader", eRenderingMode::Opaque, L"HpMaterial");
#pragma endregion
#pragma region EFFECT MATERIAL
		CreateMaterial(L"M_DeathFX", L"SpriteShader", eRenderingMode::Transparent, L"M_DeathMaterial");

		CreateMaterial(L"S_Thunder", L"SpriteShader", eRenderingMode::Transparent, L"ThunderMaterial");

		CreateMaterial(L"S_Pulse", L"SpriteShader", eRenderingMode::Transparent, L"PulseMaterial");

		CreateMaterial(L"S_Gale", L"SpriteShader", eRenderingMode::Transparent, L"GaleMaterial");

		CreateMaterial(L"T_HolyShield", L"SpriteShader", eRenderingMode::Transparent, L"HolyShieldMaterial");

		CreateMaterial(L"S_Freeze", L"SpriteShader", eRenderingMode::Transparent, L"FreezeMaterial");

		CreateMaterial(L"S_MagicLens", L"SpriteShader", eRenderingMode::Transparent, L"MagicLensMaterial");

		CreateMaterial(L"S_Curse", L"SpriteShader", eRenderingMode::Transparent, L"CurseMaterial");

		CreateMaterial(L"S_DragonEgg", L"SpriteShader", eRenderingMode::Transparent, L"DragonMaterial");

		CreateMaterial(L"S_Scythe", L"SpriteShader", eRenderingMode::Transparent, L"ScytheMaterial");

		CreateMaterial(L"S_SmiteFX", L"SpriteShader", eRenderingMode::Transparent, L"SmiteFXMaterial");

		CreateMaterial(L"S_Spear", L"SpriteShader", eRenderingMode::Transparent, L"SpearMaterial");

		CreateMaterial(L"S_ThunderBug", L"SpriteShader", eRenderingMode::Transparent, L"ThunderBugMaterial");

		CreateMaterial(L"S_Icicle", L"SpriteShader", eRenderingMode::Transparent, L"IcicleMaterial");

		CreateMaterial(L"LevelUP", L"SpriteShader", eRenderingMode::Transparent, L"LevelUPEffectMaterial");

		CreateMaterial(L"ExpObj", L"SpriteShader", eRenderingMode::Transparent, L"ExpObjectMaterial");

		std::shared_ptr<Shader> postProcessShader = Resources::Find<Shader>(L"PostProcessShader");
		std::shared_ptr<Material> postProcessMaterial = std::make_shared<Material>();
		postProcessMaterial->SetRenderingMode(eRenderingMode::PostProcess);
		postProcessMaterial->SetShader(postProcessShader);
		Resources::Insert<Material>(L"PostProcessMaterial", postProcessMaterial);

#pragma endregion
	}

	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	void CreateMaterial(const std::wstring& textureKey, const std::wstring& keyName)
	{
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(textureKey);
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		Resources::Insert<Material>(keyName, material);
	}

	void CreateMaterial(const std::wstring& shaderKey, eRenderingMode eRenderMode, const std::wstring& keyName)
	{
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(shaderKey);
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetRenderingMode(eRenderingMode::Transparent);
		material->SetShader(shader);
		Resources::Insert<Material>(keyName, material);

	}

	void CreateMaterial(const std::wstring& textureKey, const std::wstring& shaderKey, eRenderingMode eRenderMode, const std::wstring& keyName)
	{
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(textureKey);
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(shaderKey);
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetRenderingMode(eRenderMode);
		material->SetShader(shader);
		material->SetTexture(eTextureSlot::T0, texture);

		Resources::Insert<Material>(keyName, material);
	}

	void Render()
	{
		BindNoiseTexture();
		BindLights();

		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
		renderer::lights.clear();
	}

	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{
		lightsBuffer->Setdata(lights.data(), lights.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);

		renderer::LightCB trCb = {};
		trCb.numberOfLigt = lights.size();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		cb->Setdata(&trCb);
		cb->BindSRV(eShaderStage::VS);
		cb->BindSRV(eShaderStage::PS);
	}

	float noiseTime = 10.0f;
	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> noise = Resources::Find<Texture>(L"noise_04");
		noise->BindShaderResource(eShaderStage::VS, 16);
		noise->BindShaderResource(eShaderStage::HS, 16);
		noise->BindShaderResource(eShaderStage::DS, 16);
		noise->BindShaderResource(eShaderStage::GS, 16);
		noise->BindShaderResource(eShaderStage::PS, 16);
		noise->BindShaderResource(eShaderStage::CS, 16);

		NoiseCB info = {};
		info.noiseSize.x = noise->GetWidth();
		info.noiseSize.y = noise->GetHeight();
		noiseTime -= Time::DeltaTime();
		info.noiseTime = noiseTime;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Noise];
		cb->Setdata(&info);
		cb->BindSRV(eShaderStage::VS);
		cb->BindSRV(eShaderStage::HS);
		cb->BindSRV(eShaderStage::DS);
		cb->BindSRV(eShaderStage::GS);
		cb->BindSRV(eShaderStage::PS);
		cb->BindSRV(eShaderStage::CS);
	}

	void CopyRenderTarget()
	{
		std::shared_ptr<Texture> renderTarget = Resources::Find<Texture>(L"RenderTargetTexture");

		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::PS, 60, &srv);

		ID3D11Texture2D* dest = postProcessTexture->GetTexture().Get();
		ID3D11Texture2D* source = renderTarget->GetTexture().Get();

		GetDevice()->CopyResource(dest, source);

		postProcessTexture->BindShaderResource(eShaderStage::PS, 60);
	}
}