#pragma once
#include "kwEngine.h"

namespace kw
{
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		UP, DOWN, LEFT, RIGHT, SPACE,
		LBUTTON, RBUTTON,
		END,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode key;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		inline static eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[(UINT)keyCode].state;
		};

		static __forceinline bool GetKey(eKeyCode keyCode)
		{
			if (mInputEnable)
				return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Pressed;
			else
				return false;
		}

		static __forceinline bool GetKeyDown(eKeyCode keyCode)
		{
			if (mInputEnable)
				return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Down;
			else
				return false;
		}

		static __forceinline bool GetKeyUp(eKeyCode keyCode)
		{
			if (mInputEnable)
				return mKeys[static_cast<UINT>(keyCode)].state == eKeyState::Up;
			else
				return false;
		}

		static __forceinline Vector2 GetMousePos() { return mMousePos; }
		static void SetInputEnable(bool value) { mInputEnable = value; }

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;
		static bool mInputEnable;
	};
}


