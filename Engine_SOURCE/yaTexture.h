#pragma once
#include "yaResource.h"
#include "..\External\DirectTex\Include\DirectXTex.h"
#include "yaGraphicDevice_DX11.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectTex\\lib\\Debug\\DirectxTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectTex\\lib\\Release\\DirectxTex.lib")
#endif

using namespace ya::enums;
namespace ya::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT slot);
		void Clear();

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}