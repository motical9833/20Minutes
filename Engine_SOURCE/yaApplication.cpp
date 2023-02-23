#include "yaApplication.h"
#include "yaRenderer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaResources.h"

namespace ya
{
	using namespace graphics;
	Application::Application()
	{

	}

	Application::~Application()
	{
		SceneManager::Release();
	}

	void Application::Initalize()
	{
		Time::Initialize();
		Input::Initialize();
		renderer::Initialize();
		SceneManager::Initalize();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}

	void Application::FixedUpdate()
	{
		SceneManager::FixedUpdate();
	}

	void Application::Render()
	{
		Time::Render(mHdc);
		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

		//SceneManager::Render();
		//�����۾��� gpu�� �����Ͽ� ���
		//graphicDevice->Render();

		renderer::Render();
		
		graphicDevice->Present();
	}

	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Application::Release()
	{
		Resources::deleteTest();
	}


	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		//SetWindow�� �� ȣ���ؼ� â ũ�⸦ ������ �� �����Ƿ� �ѹ��� ó��
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mHdc = GetDC(mHwnd);
			mWidth = width;
			mHeight = height;


			ValidationMode vaildationMode = ValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicDevice_DX11>();
			graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0,0,(LONG)width,(LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}