#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
//#include "yaConstantBuffer.h"

//리소스 구축

// 텍스쳐

// 샘플러 

// 메테리얼

// 스마트 포인터 변환

// 스크립트

// 게임수학
// World View Projection

// 애니메이션

// 셰이더 효과


// 툴 ( imgui )
namespace ya::renderer
{
	//정점 데이터
	Vertex vertexes[4] = {};

	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)graphics::eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	std::vector <Camera*> cameras;

	void SetUpState()
	{
#pragma region Input layout
		// Input Layout (정점 구조 정보)
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		//레이아웃 종류 구분(버텍스뿐만아니라 픽셀등을 레이아웃으로 만들 수 있기
		//때문에 슬롯의 형태로 나누어 두는것)
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

		// 정점정보를 쉐이더에서 들어온 데이터를 구분할 때 필요
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		//3바이트 뒤(arrLayout[1]의 시작값)에 있으므로 16비트값(1바이트 당 4비트)
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

		// Default
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddressOf());

		// Sprite
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());


		// Player
		std::shared_ptr<Shader> playerShader = Resources::Find<Shader>(L"PlayerShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, playerShader->GetVSBlobBufferPointer()
			, playerShader->GetVSBlobBufferSize()
			, playerShader->GetInputLayoutAddressOf());

		// UI
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, uiShader->GetVSBlobBufferPointer()
			, uiShader->GetVSBlobBufferSize()
			, uiShader->GetInputLayoutAddressOf());

		// Grid
		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, gridShader->GetVSBlobBufferPointer()
			, gridShader->GetVSBlobBufferSize()
			, gridShader->GetInputLayoutAddressOf());

		// FadeInOut
		std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, gridShader->GetVSBlobBufferPointer()
			, gridShader->GetVSBlobBufferSize()
			, gridShader->GetInputLayoutAddressOf());

#pragma endregion

#pragma region sampler state
		// Sampler State
		D3D11_SAMPLER_DESC SamplerDesc = {};
		SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		//D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
		//D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
		SamplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;

		GetDevice()->CreateSamplerState
		(
			&SamplerDesc, samplerStates[(UINT)eSamplerType::Point].GetAddressOf()
		);
		
		SamplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState
		(
			&SamplerDesc, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf()
		);

		SamplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState
		(
			&SamplerDesc, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf()
		);

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point, 
			1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear,
			1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic,
			1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
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

#pragma region Depth stancil State
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

		//알파블랜드 사용X
		blendStates[(UINT)graphics::eBSType::Default] = nullptr;

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

		//알파값이 있든 없든 합친다.
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
		// Create mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes, 4);


		// 인덱스 버퍼
		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());


		// 상수 버퍼
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::FadeInOut] = new ConstantBuffer(eCBType::FadeInOut);
		constantBuffers[(UINT)eCBType::FadeInOut]->Create(sizeof(FadeInOutCB));
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

		// Player
		std::shared_ptr<Shader> playerShader = std::make_shared<Shader>();
		playerShader->Create(eShaderStage::VS, L"PlayerVS.hlsl", "main");
		playerShader->Create(eShaderStage::PS, L"PlayerPS.hlsl", "main");

		Resources::Insert<Shader>(L"PlayerShader", playerShader);

		// UI
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"UIShader", uiShader);

		// Grid
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"GridShader", gridShader);


		// FadeInOut
		std::shared_ptr<Shader> fadeShader = std::make_shared<Shader>();
		fadeShader->Create(eShaderStage::VS, L"FadeVS.hlsl", "main");
		fadeShader->Create(eShaderStage::PS, L"FadePS.hlsl", "main");

		fadeShader->SetRSState(eRSType::SolidNone);
		fadeShader->SetDSState(eDSType::NoWrite);
		fadeShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"FadeShader", fadeShader);

	}

	void LoadTexture()
	{
		Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
		Resources::Load<Texture>(L"PlayerSprite", L"Player.png");
		Resources::Load<Texture>(L"HpBarTexture", L"HpBar.png");
		Resources::Load<Texture>(L"FadeTexture", L"FadeView.png");
	}

	void LoadMaterial()
	{
		std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"SmileTexture");

		// Default
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		Resources::Insert<Material>(L"RectMaterial", material);


		std::shared_ptr <Texture> spriteTexture = Resources::Find<Texture>(L"DefaultSprite");
		// Sprite
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(spriteShader);
		spriteMaterial->SetTexture(spriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);

		// Player
		std::shared_ptr<Texture> playerTexture = Resources::Find<Texture>(L"PlayerSprite");
		std::shared_ptr<Shader> playerShader = Resources::Find<Shader>(L"PlayerShader");
		std::shared_ptr<Material> playerMaterial = std::make_shared<Material>();

		playerMaterial->SetRenderingMode(eRenderingMode::Opaque);
		playerMaterial->SetShader(playerShader);
		playerMaterial->SetTexture(playerTexture);
		Resources::Insert<Material>(L"PlayerMaterial", playerMaterial);

		// UI
		std::shared_ptr<Texture> uiTexture = Resources::Find<Texture>(L"HpBarTexture");
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

		// Fade
		std::shared_ptr<Texture> fadeTexture = Resources::Find<Texture>(L"FadeTexture");
		std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeShader");
		std::shared_ptr<Material> fadeMaterial = std::make_shared<Material>();

		fadeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		fadeMaterial->SetShader(fadeShader);
		fadeMaterial->SetTexture(fadeTexture);
		Resources::Insert<Material>(L"FadeMaterial", fadeMaterial);
	} 


	void Initialize()
	{
		
		//uv값을 실시간으로 조절하면 움직이는 이미지처럼 만들 수 있다
		// 움직이는 백그라운드 이미지
		//RECT
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.5f,1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.5f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.5f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		LoadShader(); 
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}
	void Render()
	{
		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
	}
	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}
	}
}