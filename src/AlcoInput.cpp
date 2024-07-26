
#include "AlcoInput.hpp"

#include <hidusage.h>
#include <stdexcept>
#include <vector>
#include <iostream>

constexpr auto PROP_KEYBOARD = L"Keyboard";

namespace alco::input
{
	Input::~Input()
	{
		this->m_Unregister();
	}

	void Input::RegisterInput(HWND target)
	{
		this->m_Unregister();

		m_target = target;
		RAWINPUTDEVICE rid[2] = {};
		rid[0].dwFlags = RIDEV_INPUTSINK;
		rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		rid[0].usUsage = HID_USAGE_GENERIC_KEYBOARD;
		rid[0].hwndTarget = m_target;

		rid[1].dwFlags = RIDEV_INPUTSINK;
		rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
		rid[1].usUsage = HID_USAGE_GENERIC_MOUSE;
		rid[1].hwndTarget = m_target;
		if (!RegisterRawInputDevices(rid, _countof(rid), sizeof(RAWINPUTDEVICE))) throw std::runtime_error("Failed to register raw input device");

		m_originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(m_target, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_WndProc)));
		SetProp(m_target, PROP_KEYBOARD, this);

		m_keyboard = std::make_unique<Keyboard>(Keyboard());
		m_mouse = std::make_unique<Mouse>(Mouse());
	}

	Keyboard* Input::GetKeyboard() const
	{
		return m_keyboard.get();
	}

	Mouse* Input::GetMouse() const
	{
		return m_mouse.get();
	}

	void Input::Update()
	{
		m_mouse->m_prevOffset = m_mouse->m_offset;
		m_mouse->m_offset = { 0, 0 };

		if (m_mouse->m_lastKey == Key::WHEEL_UP || m_mouse->m_lastKey == Key::WHEEL_DOWN)
		{
			if (m_mouse->m_wheelHandled)
			{
				m_mouse->m_mouse[m_mouse->m_lastKey] = 0;
				m_mouse->m_lastKey = Key::NONE_MB;
				if (m_lastDevice == MOUSE) m_lastDevice = UNKNOWN;
			}
			else m_mouse->m_wheelHandled = true;
		}

		if (m_keyboard->GetLastKey() == Key::NONE_KB && m_mouse->GetLastKey() == Key::NONE_MB)
		{
			m_lastDevice = UNKNOWN;
		}
	}

	Input::Device Input::LastDevice() const
	{
		return m_lastDevice;
	}

	void Input::m_Unregister() const
	{
		if (m_originalWndProc) SetWindowLongPtr(m_target, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_originalWndProc));
		RemoveProp(m_target, PROP_KEYBOARD);

		m_keyboard = nullptr;
		m_mouse = nullptr;
	}

	LRESULT Input::m_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		auto pthis = reinterpret_cast<Input*>(GetProp(hwnd, PROP_KEYBOARD));
		if (!pthis) throw std::runtime_error("Failed to get Keyboard instance");

		switch (msg)
		{
		case WM_INPUT:
		{
			if (wParam == RIM_INPUTSINK) return 0;

			UINT dwSize = 0;
			GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));

			std::vector<BYTE> lpb(dwSize);
			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, lpb.data(), &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
				throw std::runtime_error("GetRawInputData does not return correct size");

			auto* raw = reinterpret_cast<RAWINPUT*>(lpb.data());

			if (raw->header.dwType == RIM_TYPEKEYBOARD)
			{
				auto& rawKB = raw->data.keyboard;

				if (rawKB.Message == WM_KEYDOWN)
				{
					auto virtualKey = rawKB.VKey;
					pthis->m_keyboard->m_keyboard[virtualKey] = 1;
					pthis->m_keyboard->m_lastKey = static_cast<Key::KeyboardCodes>(virtualKey);
					pthis->m_lastDevice = KEYBOARD;
				}

				else if (rawKB.Message == WM_KEYUP)
				{
					auto virtualKey = rawKB.VKey;
					pthis->m_keyboard->m_keyboard[virtualKey] = 0;
					if (pthis->m_keyboard->m_lastKey == static_cast<Key::KeyboardCodes>(virtualKey))
					{
						pthis->m_keyboard->m_lastKey = Key::NONE_KB;
						if (pthis->m_lastDevice == KEYBOARD) pthis->m_lastDevice = UNKNOWN;
					}
				}
			}

			else if (raw->header.dwType == RIM_TYPEMOUSE)
			{
				auto& rawMS = raw->data.mouse;
				pthis->m_mouse->m_offset.x = rawMS.lLastX;
				pthis->m_mouse->m_offset.y = rawMS.lLastY;
				for (int i = 0; i < 5; ++i)
				{
					char status = ((rawMS.ulButtons >> (i * 2)) & 3);
					if (status)
					{
						int key = i + 1 + (i > 1);
						if (status & 1)
						{
							pthis->m_mouse->m_mouse[key] = 1;
							pthis->m_mouse->m_lastKey = static_cast<Key::MouseCodes>(key);
							pthis->m_lastDevice = MOUSE;
						}
						else
						{
							pthis->m_mouse->m_mouse[key] = 0;
							if (pthis->m_mouse->m_lastKey == static_cast<Key::MouseCodes>(key))
							{
								pthis->m_mouse->m_lastKey = Key::NONE_MB;
								if (pthis->m_lastDevice == MOUSE) pthis->m_lastDevice = UNKNOWN;
							}
						}
					}
				}

				if (rawMS.usButtonFlags & RI_MOUSE_WHEEL)
				{
					if (static_cast<short>(rawMS.usButtonData) > 0)
					{
						pthis->m_mouse->m_mouse[Key::WHEEL_UP] = 1;
						pthis->m_mouse->m_lastKey = static_cast<Key::MouseCodes>(Key::WHEEL_UP);
					}
					else 
					{
						pthis->m_mouse->m_mouse[Key::WHEEL_DOWN] = 1;
						pthis->m_mouse->m_lastKey = static_cast<Key::MouseCodes>(Key::WHEEL_DOWN);
					}
					pthis->m_lastDevice = MOUSE;
					pthis->m_mouse->m_wheelHandled = false;
				}
			}

			return 0;
		}
		}

		return CallWindowProcW(pthis->m_originalWndProc, hwnd, msg, wParam, lParam);
	}
}
