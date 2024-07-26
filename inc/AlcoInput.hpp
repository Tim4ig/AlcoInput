
#pragma once

#ifndef UNICODE
#define UNICODE 1
#endif // !UNICODE

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <memory>

#include "Key.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace alco::input
{
	class Input
	{
	public:
		~Input();

		enum Device
		{
			UNKNOWN,
			MOUSE,
			KEYBOARD
		};

		void Update();
		void RegisterInput(HWND target);

		Mouse* GetMouse() const;
		Keyboard* GetKeyboard() const;
		Device LastDevice() const;
	private:
		HWND m_target = nullptr;
		WNDPROC m_originalWndProc = nullptr;

		Device m_lastDevice = UNKNOWN;
		mutable std::unique_ptr<Keyboard> m_keyboard;
		mutable std::unique_ptr<Mouse> m_mouse;

		void m_Unregister() const;
		static LRESULT CALLBACK m_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}
