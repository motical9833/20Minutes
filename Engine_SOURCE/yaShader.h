#pragma once
#include "yaResource.h"
#include "yaGraphics.h"

namespace ya
{
	using namespace graphics;
	class Shader : public Resource
	{
	public:
		Shader();
		~Shader();

		virtual HRESULT Load(const std::wstring& path) override;

		void Create(eShaderStage stage, const std::wstring& file, const std::string& funName);
		void Binds();

		ID3D11InputLayout* GetInputLayout() { return mInputLayout.Get(); }
		ID3D11InputLayout** GetInputLayoutAddressOf() { return mInputLayout.GetAddressOf(); }

		void* GetVSBlobBufferPointer() { return mVSBlob->GetBufferPointer(); }
		SIZE_T GetVSBlobBufferSize() { return mVSBlob->GetBufferSize(); }

		void SetRSState(eRSType state) { mRSType = state; }
		void SetDSState(eDSType state) { mDSType = state; }
		void SetBSState(eBSType state) { mBSType = state; }

	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
		graphics::eShaderStage mStage;

		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;


		//// 래스터라이저 스테이트
		eRSType mRSType;
		//// 뎁스스텐실 스테이트
		eDSType mDSType;
		//// 알파블랜딩
		eBSType mBSType;

		Microsoft::WRL::ComPtr<ID3DBlob> mErrorBlob;
	};
}
