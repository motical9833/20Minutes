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

		// 게임 로직 캐릭터 이동 등등
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
		//GraphicDevice_DX11를통해 GPU에게 데이터를 넘겨주고
		//세팅,정보를 가르켜 주는 작업을 한다.
		//unique_ptr을 이용하면 하나만 만들 수 있다.(게임은 주로 그래픽 카드 하나만 사용하기 떄문)
		std::unique_ptr<graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		HDC mHdc;
		UINT mHeight;
		UINT mWidth;
	};
}
