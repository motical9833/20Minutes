#pragma once
#include "yaEngine.h"
#include "yaGraphics.h"
#include "yaGraphicDevice_DX11.h"

namespace ya
{
	class Application
	{
	public:
		Application();
		~Application();

		// Running main engin loop
		virtual void Initalize();

		// ���� ���� ĳ���� �̵� ���
		// CPU UPDATE
		virtual void Update();

		// GPU UPDATE
		virtual void FixedUpdate();

		virtual void Render();

		void Run();
		void Release();


		void SetWindow(HWND hwnd, UINT width, UINT height);

		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() { return mHwnd; }

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		bool Initialized = false;
		//GraphicDevice_DX11������ GPU���� �����͸� �Ѱ��ְ�
		//����,������ ������ �ִ� �۾��� �Ѵ�.
		//unique_ptr�� �̿��ϸ� �ϳ��� ���� �� �ִ�.(������ �ַ� �׷��� ī�� �ϳ��� ����ϱ� ����)
		std::unique_ptr<graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		HDC mHdc;
		UINT mHeight;
		UINT mWidth;
	};
}
