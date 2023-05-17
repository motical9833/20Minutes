#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSceneManager.h"
#include "yaPaintShader.h"
#include "yaParticleShader.h"

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
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"UIShader", uiShader);
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
		monsterShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		monsterShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

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

		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, uiShader->GetVSBlobBufferPointer()
			, uiShader->GetVSBlobBufferSize()
			, uiShader->GetInputLayoutAddressOf());

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
		Resources::Load<Texture>(L"Shana", L"Player\\Shana.png");
		Resources::Load<Texture>(L"Abby", L"Player\\T_AbbySprite.png");
		Resources::Load<Texture>(L"Dasher", L"Player\\T_Dasher.png");
		Resources::Load<Texture>(L"Diamond", L"Player\\T_DiamondSprite.png");
		Resources::Load<Texture>(L"Hastur", L"Player\\T_Hastur.png");
		Resources::Load<Texture>(L"Hina", L"Player\\T_HinaSprite.png");
		Resources::Load<Texture>(L"Lilith", L"Player\\T_LilithSprite.png");
		Resources::Load<Texture>(L"Luna", L"Player\\T_Luna.png");
		Resources::Load<Texture>(L"Scarlett", L"Player\\T_Scarlett.png");
		Resources::Load<Texture>(L"Spark", L"Player\\T_Spark.png");
		Resources::Load<Texture>(L"Yuki", L"Player\\T_Yuki.png");

		Resources::Load<Texture>(L"LevelUP", L"Player\\T_LevelUpFX.png");


		Resources::Load<Texture>(L"TitleLevesLeftSprite", L"T_TitleLeavesLeft.png");
		Resources::Load<Texture>(L"TitleLevesRightSprite", L"T_TitleLeavesRight.png");
		Resources::Load<Texture>(L"BackGroundTexture", L"BackGround.png");
		Resources::Load<Texture>(L"LogoTexture", L"Logo.png");
		Resources::Load<Texture>(L"MonsterSprite", L"BrainMonster_0.png");
		Resources::Load<Texture>(L"BrainMonster", L"Monster\\BrainMonster.png");
		Resources::Load<Texture>(L"TreeSprite", L"Monster\\T_TreeMonster.png");
		Resources::Load<Texture>(L"EyeMonsterSprite", L"Monster\\EyeMonster.png");
		Resources::Load<Texture>(L"BoomerMonsterSprite", L"Monster\\BigBoomer.png");
		Resources::Load<Texture>(L"W_RevolverSprite", L"Weapon\\T_Revolver_SS.png");
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



#pragma endregion
#pragma region DYNAMIC TEXTURE
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM
			, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert<Texture>(L"PaintTexture", uavTexture);
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

		CreateMaterial(L"BrainMonster", L"MonsterShader", eRenderingMode::Transparent, L"BrainMonsterMaterial");
#pragma endregion
#pragma region MONSTERS MATERIAL
		// TreeMonster
		CreateMaterial(L"TreeSprite", L"MonsterShader", eRenderingMode::Transparent, L"TreeMaterial");

		// EyeMonster
		CreateMaterial(L"EyeMonsterSprite", L"MonsterShader", eRenderingMode::Transparent, L"EyeMonsterMaterial");

		// BoomerMonster
		CreateMaterial(L"BoomerMonsterSprite", L"MonsterShader", eRenderingMode::Transparent, L"BoomerMonsterMaterial");

#pragma endregion
#pragma region WEAPON MATERIAL
		// Revolver
		CreateMaterial(L"W_RevolverSprite", L"SpriteShader", eRenderingMode::Transparent, L"RevolverMaterial");
		// Bullet
		CreateMaterial(L"BulletTexture", L"SpriteShader", eRenderingMode::Transparent, L"BulletMaterial");
#pragma endregion
#pragma region UI MATERIAL
		CreateMaterial(L"TitleLevesLeftSprite", L"SpriteShader", eRenderingMode::Transparent, L"leavsLeftMaterial");

		CreateMaterial(L"TitleLevesRightSprite", L"SpriteShader", eRenderingMode::Transparent, L"leavsRightMaterial");

		CreateMaterial(L"BackGroundTexture", L"SpriteShader", eRenderingMode::Transparent, L"backgroundMaterial");

		CreateMaterial(L"LogoTexture", L"SpriteShader", eRenderingMode::Transparent, L"LogoMaterial");
#pragma endregion
#pragma region PlayerUI
		CreateMaterial(L"HPHeart", L"SpriteShader", eRenderingMode::Transparent, L"HpMaterial");
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
	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> noise = Resources::Find<Texture>(L"noise_01");
		noise->BindShaderResource(eShaderStage::VS, 16);
		noise->BindShaderResource(eShaderStage::HS, 16);
		noise->BindShaderResource(eShaderStage::DS, 16);
		noise->BindShaderResource(eShaderStage::GS, 16);
		noise->BindShaderResource(eShaderStage::PS, 16);
		noise->BindShaderResource(eShaderStage::CS, 16);

		NoiseCB info = {};
		info.noiseSize.x = noise->GetWidth();
		info.noiseSize.y = noise->GetHeight();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Noise];
		cb->Setdata(&info);
		cb->BindSRV(eShaderStage::VS);
		cb->BindSRV(eShaderStage::HS);
		cb->BindSRV(eShaderStage::DS);
		cb->BindSRV(eShaderStage::GS);
		cb->BindSRV(eShaderStage::PS);
		cb->BindSRV(eShaderStage::CS);
	}
}