
#pragma once

#include "Key.hpp"

namespace alco::input
{
	class Keyboard
	{
	public:
		Key::KeyboardCodes GetLastKey() const;
		bool GetKeyStatus(Key::KeyboardCodes code) const;
		const char* GetKeyName(Key::KeyboardCodes code) const;
	private:
		Keyboard() = default;

		char m_keyboard[255] = {};
		Key::KeyboardCodes m_lastKey = Key::NONE_KB;

		friend class Input;
	};
}
