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
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		void clear();

	private:
		HWND mHwnd;
		HDC mHdc;
		HMENU mMenubar;

		// ¹é¹öÆÛ
		HBITMAP mBackBuffer;
		HDC mBackHdc;

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
	};
}