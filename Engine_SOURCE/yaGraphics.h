#pragma once
//#include "CommonInclude.h"
#include <wrl.h>
#include "yaMath.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")


#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name

#define CBSLOT_TRANSFORM 0
#define CBSLOT_MATERIAL 1
#define CBSLOT_GRID 2
#define CBSLOT_FADEINOUT 3

namespace ya::graphics
{
	enum class ValidationMode
	{
		Disabled,
		Enabled,
		GPU,
	};

	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		Count,
	};

	enum class eSamplerType
	{
		Point,
		Linear,
		Anisotropic,
		End,
	};

	enum class eRSType
	{
		SolidBack, //기본값
		SolidFront,
		SolidNone,
		WireframeNone,
		End,
	};


	enum class eDSType
	{
		Less, //작았을때 그린다. //기본값
		Greater, //클떄그린다.
		NoWrite, //깊이버퍼 안씀
		None,
		End,
	};

	enum class eBSType
	{
		Default,
		AlphaBlend, // 블랜드 사용 //기본값
		OneOne, // 투명값 사용X 물체색을 더한다.?
		End,
	};

	enum class eRenderingMode
	{
		Opaque, // 투명하지 않은물체
		cutOut, // 반투명이 없고 100% 불투명하거나 보이지 않는다.
		Transparent, //투명한 마티리얼을 사실적으로 렌더링 ex)헬멧 바이저등등...
		End,
	};

	struct GpuBuffer
	{
		enum class eType
		{
			Buffer,
			Texture,
			UnknownType,
		} type = eType::UnknownType;

		D3D11_BUFFER_DESC desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;
	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		FadeInOut,
		End,
	};

	enum class eGPUParam
	{
		Int,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Matrix,
	};
}