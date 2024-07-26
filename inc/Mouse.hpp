
#pragma once

#include "Key.hpp"

namespace alco::input
{
	struct Position
	{
		int x, y;
	};

	class Mouse
	{
	public:
		const Position* GetOffset() const;
		Key::MouseCodes GetLastKey() const;
		bool GetKeyStatus(Key::MouseCodes code) const;
		const char* GetKeyName(Key::MouseCodes code) const;
	private:
		Mouse() = default;

		char m_mouse[16] = {};
		bool m_wheelHandled = false;
		Key::MouseCodes m_lastKey = Key::NONE_MB;

		Position m_offset = {};
		Position m_prevOffset = {};

		friend class Input;
	};
}
