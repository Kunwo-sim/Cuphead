#include "kwImage.h"
#include "kwApplication.h"
#include "kwResources.h"

extern kw::Application application;

namespace kw
{
	Image* Image::Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb)
	{
		if (widht == 0 || height == 0)
			return nullptr;

		Image* image = Resources::Find<Image>(name);
		if (image != nullptr)
			return image;

		image = new Image();
		HDC mainHdc = application.GetHdc();

		image->mBitmap = CreateCompatibleBitmap(mainHdc, widht, height);
		image->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->mWidth = widht;
		image->mHeight = height;

		image->SetKey(name);
		Resources::Insert<Image>(name, image);
		
		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(image->GetHdc(), brush);
		Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		SelectObject(image->GetHdc(), oldBrush);
		DeleteObject(oldBrush);

		return image;
	}

	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{


	}

	Image::~Image()
	{

	}

	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr
			, path.c_str(), IMAGE_BITMAP
			, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
			return E_FAIL;

		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = application.GetHdc();
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(oldBitmap);

		return S_OK;
	}

	COLORREF Image::GetPixel(int x, int y)
	{
		return ::GetPixel(mHdc, x, y);
	}

	void Image::SetPixel(int x, int y, COLORREF color)
	{
		::SetPixel(mHdc, x, y, color);
	}

	void Image::SetBright(int bright)
	{
		for (int x = 0; x < 100; x++)
		{
			for (int y = 0; y < 100; y++)
			{
				int a = 0;
				COLORREF color = GetPixel(x, y);

				//if (color == RGB(255, 0, 255) || color == RGB(255, 255, 255))
				//	continue;
				//else
				//{
				//	int r = GetRValue(color);
				//	int g = GetGValue(color);
				//	int b = GetBValue(color);

				//	r += bright;
				//	g += bright;
				//	b += bright;

				//	r = min(r, 255);
				//	g = min(g, 255);
				//	b = min(b, 255);

				//	COLORREF newColor = RGB(r, g, b);
				//	SetPixel(x, y, newColor);
				//}
			}
		}
	}
}
