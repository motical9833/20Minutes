#pragma once

#include "CommonInclude.h"
#include "yaMath.h"
#include "yaGraphicDevice_DX11.h"
#include "yaMesh.h"
#include "yaShader.h"
#include "yaConstantBuffer.h"
#include "yaCamera.h"

using namespace ya::math;
using namespace ya::graphics;

namespace ya::renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};
	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;

		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};
	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};
	CBUFFER(FadeInOutCB, CBSLOT_GRID)
	{
		Vector4 position;
		Vector4 color;
		float alpha;
		float value;
	};


	//정점 데이터
	extern Vertex vertexes[4];

	extern Microsoft::WRL::ComPtr<ID3D11Buffer> triangleConstantBuffer;
	extern ConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector <Camera*> cameras;

	void Initialize();
	void Render();
	void Release();
}