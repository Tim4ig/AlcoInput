
#include "Keyboard.hpp"

namespace alco::input
{
	Key::KeyboardCodes Keyboard::GetLastKey() const
	{
		return m_lastKey;
	}

	bool Keyboard::GetKeyStatus(Key::KeyboardCodes code) const
	{
		return m_keyboard[code];
	}

	const char* Keyboard::GetKeyName(Key::KeyboardCodes code) const
	{
		auto it = g_KeyboardNameMap.find(code);
		if (it == g_KeyboardNameMap.end()) return "Unknown";
		return it->second;
	}
}
