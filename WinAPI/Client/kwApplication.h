#pragma once
#include "kwEngine.h"

namespace kw
{
	class Application
	{
	public:
		Application();
		~Application();
		
		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();
		void SetMenuBar(bool power);

		HWND GetHwnd() { return mHwnd; }
		HWND GetToolHwnd() { return mToolHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

		void SetToolHwnd(HWND hwnd) { mToolHwnd = hwnd; }

	private:
		void clear();

	private:
		// main
		HWND mHwnd;
		HDC mHdc;
		HMENU mMenubar;

		// tool
		HWND mToolHwnd;

		// ¹é¹öÆÛ
		HBITMAP mBackBuffer;
		HDC mBackHdc;

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
	};
}