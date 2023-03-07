#include "kwApplication.h"
#include "kwSceneManager.h"
#include "kwTime.h"
#include "kwInput.h"
#include "kwCollisionManager.h"

namespace kw
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, mBackBuffer(NULL)
		, mBackHdc(NULL)
		, mWidth(1600)
		, mHeight(900)
	{
	}

	Application::~Application()
	{
		SceneManager::Release();
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);
		mWidth = 1280;
		mHeight = 720;

		// 비트맵 해상도를 설정하기 위한 실제 윈도우 크기를 계산해준다.
		RECT rect = { 0,0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경 및 출력 설정
		SetWindowPos(mHwnd
			, nullptr, 100, 50
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(hWnd, true);

		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP defaultBitmap
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(defaultBitmap);

		Time::Initiailize();
		Input::Initialize();
		SceneManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
		CollisionManager::Update();
	}

	void Application::Render()
	{
		clear();
		// 새로 그리기
		Rectangle(mBackHdc, -1, -1, 1282, 722);

		Time::Render(mBackHdc);
		Input::Render(mBackHdc);
		SceneManager::Render(mBackHdc);
		
		// 백버퍼에 있는 그림을 원본 버퍼에 다시 그리기
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
	}

	void Application::clear()
	{
		HBRUSH grayBrush = CreateSolidBrush(RGB(121, 121, 121));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);
		Rectangle(mBackHdc, -1, -1, 1282, 722);
		SelectObject(mBackHdc, oldBrush);
		DeleteObject(grayBrush);
	}
}
