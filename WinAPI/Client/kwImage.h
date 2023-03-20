#pragma once
#include "kwResource.h"

namespace kw
{
	class Image : public Resource
	{
	public:
		static Image* Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb = RGB(255, 255, 255));

		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		HBITMAP GetBitmap() { return mBitmap; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}
