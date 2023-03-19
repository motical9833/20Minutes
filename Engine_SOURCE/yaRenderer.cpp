#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSceneManager.h"

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

	void LoadMesh()
	{
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

		// 
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
	}

	void SetUpState()
	{
#pragma region Input layout
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

#pragma endregion
#pragma region sampler state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		//D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
		//D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
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
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));
	}

	void LoadShader()
	{
		// Default
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");

		Resources::Insert<Shader>(L"RectShader", shader);

		// Sprite
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"SpriteShader", spriteShader);

		// UI
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"UIShader", uiShader);

		// Grid Shader
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"GridShader", gridShader);

		// Debug Shader
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::NoWrite);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Resources::Insert<Shader>(L"DebugShader", debugShader);

		// Player
		std::shared_ptr<Shader> playerShader = std::make_shared<Shader>();
		playerShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		playerShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"PlayerShader", playerShader);

		// Monster
		std::shared_ptr<Shader> monsterShader = std::make_shared<Shader>();
		monsterShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		monsterShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"MonsterShader", monsterShader);

		// leaves
		std::shared_ptr<Shader> leavesShader = std::make_shared<Shader>();
		leavesShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		leavesShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"LeavesShader", leavesShader);

		// Weapon
		std::shared_ptr<Shader> weaponShader = std::make_shared<Shader>();
		weaponShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		weaponShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"WeaponShader", weaponShader);
	}

	void LoadTexture()
	{
		Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
		Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
		Resources::Load<Texture>(L"PlayerSprite", L"Player\\Player.png");
		Resources::Load<Texture>(L"TitleLevesLeftSprite", L"T_TitleLeavesLeft.png");
		Resources::Load<Texture>(L"TitleLevesRightSprite", L"T_TitleLeavesRight.png");
		Resources::Load<Texture>(L"BackGroundTexture", L"BackGround.png");
		Resources::Load<Texture>(L"LogoTexture", L"Logo.png");
		Resources::Load<Texture>(L"MonsterSprite", L"BrainMonster_0.png");
		Resources::Load<Texture>(L"TreeSprite", L"Monster\\T_TreeMonster.png");
		Resources::Load<Texture>(L"EyeMonsterSprite", L"Monster\\EyeMonster.png");
		Resources::Load<Texture>(L"BoomerMonsterSprite", L"Monster\\BigBoomer.png");
		Resources::Load<Texture>(L"W_RevolverSprite", L"Weapon\\T_Revolver_SS.png");
		Resources::Load<Texture>(L"HPHeart", L"UI\\T_HeartAnimation.png");
	}

	void LoadMaterial()
	{

		// Default
		std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"SmileTexture");
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>(); 
		material->SetShader(shader);
		material->SetTexture(texture);
		Resources::Insert<Material>(L"RectMaterial", material);

		// Sprite
		std::shared_ptr <Texture> spriteTexture= Resources::Find<Texture>(L"DefaultSprite");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(spriteShader);
		spriteMaterial->SetTexture(spriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);

		// UI
		std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"HPBarTexture");
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
		uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		uiMaterial->SetShader(uiShader);
		uiMaterial->SetTexture(uiTexture);
		Resources::Insert<Material>(L"UIMaterial", uiMaterial);

		// Grid
		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
		gridMaterial->SetShader(gridShader);
		Resources::Insert<Material>(L"GridMaterial", gridMaterial);

		// Debug
		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		debugMaterial->SetShader(debugShader);
		Resources::Insert<Material>(L"DebugMaterial", debugMaterial);

		// Player
		std::shared_ptr<Texture> playerTexture = Resources::Find<Texture>(L"PlayerSprite");
		std::shared_ptr<Shader> playerShader = Resources::Find<Shader>(L"PlayerShader");
		std::shared_ptr<Material> playerMaterial = std::make_shared<Material>();
		playerMaterial->SetRenderingMode(eRenderingMode::Transparent);
		playerMaterial->SetShader(playerShader);
		playerMaterial->SetTexture(playerTexture);

		Resources::Insert<Material>(L"PlayerMaterial", playerMaterial);

		//Monster
		std::shared_ptr<Texture> monsterTexture = Resources::Find<Texture>(L"MonsterSprite");
		std::shared_ptr<Shader> monsterShader = Resources::Find<Shader>(L"MonsterShader");
		std::shared_ptr<Material> monsterMaterial = std::make_shared<Material>();
		monsterMaterial->SetRenderingMode(eRenderingMode::Transparent);
		monsterMaterial->SetShader(monsterShader);
		monsterMaterial->SetTexture(monsterTexture);

		Resources::Insert<Material>(L"MonsterMaterial", monsterMaterial);

		// TreeMonster
		std::shared_ptr<Texture> treeTexture = Resources::Find<Texture>(L"TreeSprite");
		std::shared_ptr<Shader> treeShader = Resources::Find<Shader>(L"MonsterShader");
		std::shared_ptr<Material> treeMaterial = std::make_shared<Material>();
		treeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		treeMaterial->SetShader(treeShader);
		treeMaterial->SetTexture(treeTexture);

		Resources::Insert<Material>(L"TreeMaterial", treeMaterial);

		// EyeMonster
		std::shared_ptr<Texture> m_EyeTexture = Resources::Find<Texture>(L"EyeMonsterSprite");
		std::shared_ptr<Shader> m_EyeShader = Resources::Find<Shader>(L"MonsterShader");
		std::shared_ptr<Material> m_EyeMaterial = std::make_shared<Material>();
		m_EyeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		m_EyeMaterial->SetShader(m_EyeShader);
		m_EyeMaterial->SetTexture(m_EyeTexture);

		Resources::Insert<Material>(L"EyeMonsterMaterial", m_EyeMaterial);

		// BoomerMonster
		std::shared_ptr<Texture> mBoomerTexture = Resources::Find<Texture>(L"BoomerMonsterSprite");
		std::shared_ptr<Shader> mBoomerShader = Resources::Find<Shader>(L"MonsterShader");
		std::shared_ptr<Material> mBoomerMaterial = std::make_shared<Material>();
		mBoomerMaterial->SetRenderingMode(eRenderingMode::Transparent);
		mBoomerMaterial->SetShader(mBoomerShader);
		mBoomerMaterial->SetTexture(mBoomerTexture);

		Resources::Insert<Material>(L"BoomerMonsterMaterial", mBoomerMaterial);



		//Weapon
		{
			// Revolver
			std::shared_ptr<Texture> revolverTexture = Resources::Find<Texture>(L"W_RevolverSprite");
			std::shared_ptr<Shader> weaponShader = Resources::Find<Shader>(L"WeaponShader");
			std::shared_ptr<Material> revolverMaterial = std::make_shared<Material>();
			revolverMaterial->SetRenderingMode(eRenderingMode::Transparent);
			revolverMaterial->SetShader(weaponShader);
			revolverMaterial->SetTexture(revolverTexture);

			Resources::Insert<Material>(L"RevolverMaterial", revolverMaterial);
		}

		// UI
		{
			std::shared_ptr<Texture> titleLevesLeft = Resources::Find<Texture>(L"TitleLevesLeftSprite");
			std::shared_ptr<Shader> levesShder_L = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> leavsLeftMat = std::make_shared<Material>();
			leavsLeftMat->SetRenderingMode(eRenderingMode::Transparent);
			leavsLeftMat->SetShader(levesShder_L);
			leavsLeftMat->SetTexture(titleLevesLeft);

			Resources::Insert<Material>(L"leavsLeftMaterial", leavsLeftMat);

			std::shared_ptr<Texture> titleLevesright = Resources::Find<Texture>(L"TitleLevesRightSprite");
			std::shared_ptr<Shader> levesShder_R = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> leavsRightMat = std::make_shared<Material>();
			leavsRightMat->SetRenderingMode(eRenderingMode::Transparent);
			leavsRightMat->SetShader(levesShder_R);
			leavsRightMat->SetTexture(titleLevesright);

			Resources::Insert<Material>(L"leavsRightMaterial", leavsRightMat);


			std::shared_ptr<Texture> backgroundTex = Resources::Find<Texture>(L"BackGroundTexture");
			std::shared_ptr<Shader> backgroundShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> backgroundMat = std::make_shared<Material>();
			backgroundMat->SetRenderingMode(eRenderingMode::Transparent);
			backgroundMat->SetShader(backgroundShader);
			backgroundMat->SetTexture(backgroundTex);

			Resources::Insert<Material>(L"backgroundMaterial", backgroundMat);

			std::shared_ptr<Texture> logoTexture = Resources::Find<Texture>(L"LogoTexture");
			std::shared_ptr<Shader> logoShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> logoMaterial = std::make_shared<Material>();
			logoMaterial->SetRenderingMode(eRenderingMode::Transparent);
			logoMaterial->SetShader(logoShader);
			logoMaterial->SetTexture(logoTexture);

			Resources::Insert<Material>(L"LogoMaterial", logoMaterial);


			std::shared_ptr<Texture> hpTexture = Resources::Find<Texture>(L"HPHeart");
			std::shared_ptr<Shader> hpShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> hpMaterial = std::make_shared<Material>();
			hpMaterial->SetRenderingMode(eRenderingMode::Transparent);
			hpMaterial->SetShader(hpShader);
			hpMaterial->SetTexture(hpTexture);

			Resources::Insert<Material>(L"HpMaterial", hpMaterial);
		}
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
	}

	void Render()
	{
		//std::vector<Camera*> cameras[(UINT)eSceneType::End];
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
	}
}