#include "kwSoundManager.h"
#include "kwApplication.h"

extern kw::Application application;

namespace kw
{
	LPDIRECTSOUND8 SoundManager::mSoundDevice;

	bool SoundManager::Initialize()
	{
		if (FAILED(DirectSoundCreate8(NULL, &mSoundDevice, NULL)))
		{
			MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		// ���� ����̽� �������� ����.
		HWND hWnd = application.GetHwnd();
		if (FAILED(mSoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
		{
			MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		return true;
	}
}