
#include "Mouse.hpp"

namespace alco::input
{
	const Position* Mouse::GetOffset() const
	{
		return &m_prevOffset;
	}

	Key::MouseCodes Mouse::GetLastKey() const
	{
		return m_lastKey;
	}

	bool Mouse::GetKeyStatus(Key::MouseCodes code) const
	{
		return m_mouse[code];
	}

	const char* Mouse::GetKeyName(Key::MouseCodes code) const
	{
		auto it = g_MouseNameMap.find(code);
		if (it == g_MouseNameMap.end()) return "Unknown";
		return it->second;
	}
}
