
#pragma once

#include <unordered_map>

namespace alco::input
{
    struct Key
    {
        enum MouseCodes
        {
            NONE_MB = 0x00,         // Undefined
            LEFT_MOUSE = 0x01,      // VK_LBUTTON
            RIGHT_MOUSE = 0x02,     // VK_RBUTTON
            MIDDLE_MOUSE = 0x04,    // VK_MBUTTON
            X1_MOUSE = 0x05,        // VK_XBUTTON1
            X2_MOUSE = 0x06,        // VK_XBUTTON2
            WHEEL_UP = 0x0E,        // WHEEL_UP
            WHEEL_DOWN = 0x0F       // WHEEL_DOWN
        };

        enum KeyboardCodes
        {
            NONE_KB = 0x00,         // Undefined
            BACKSPACE = 0x08,       // VK_BACK
            TAB = 0x09,             // VK_TAB
            CLEAR = 0x0C,           // VK_CLEAR
            ENTER = 0x0D,           // VK_RETURN
            SHIFT = 0x10,           // VK_SHIFT
            CTRL = 0x11,            // VK_CONTROL
            ALT = 0x12,             // VK_MENU
            PAUSE = 0x13,           // VK_PAUSE
            CAPS_LOCK = 0x14,       // VK_CAPITAL
            ESCAPE = 0x1B,          // VK_ESCAPE
            SPACE = 0x20,           // VK_SPACE
            PAGE_UP = 0x21,         // VK_PRIOR
            PAGE_DOWN = 0x22,       // VK_NEXT
            END = 0x23,             // VK_END
            HOME = 0x24,            // VK_HOME
            LEFT = 0x25,            // VK_LEFT
            UP = 0x26,              // VK_UP
            RIGHT = 0x27,           // VK_RIGHT
            DOWN = 0x28,            // VK_DOWN
            SELECT = 0x29,          // VK_SELECT
            INSERT = 0x2D,          // VK_INSERT
            DEL = 0x2E,             // VK_DELETE
            KEY_0 = 0x30,           // 0 key
            KEY_1 = 0x31,           // 1 key
            KEY_2 = 0x32,           // 2 key
            KEY_3 = 0x33,           // 3 key
            KEY_4 = 0x34,           // 4 key
            KEY_5 = 0x35,           // 5 key
            KEY_6 = 0x36,           // 6 key
            KEY_7 = 0x37,           // 7 key
            KEY_8 = 0x38,           // 8 key
            KEY_9 = 0x39,           // 9 key
            KEY_A = 0x41,           // A key
            KEY_B = 0x42,           // B key
            KEY_C = 0x43,           // C key
            KEY_D = 0x44,           // D key
            KEY_E = 0x45,           // E key
            KEY_F = 0x46,           // F key
            KEY_G = 0x47,           // G key
            KEY_H = 0x48,           // H key
            KEY_I = 0x49,           // I key
            KEY_J = 0x4A,           // J key
            KEY_K = 0x4B,           // K key
            KEY_L = 0x4C,           // L key
            KEY_M = 0x4D,           // M key
            KEY_N = 0x4E,           // N key
            KEY_O = 0x4F,           // O key
            KEY_P = 0x50,           // P key
            KEY_Q = 0x51,           // Q key
            KEY_R = 0x52,           // R key
            KEY_S = 0x53,           // S key
            KEY_T = 0x54,           // T key
            KEY_U = 0x55,           // U key
            KEY_V = 0x56,           // V key
            KEY_W = 0x57,           // W key
            KEY_X = 0x58,           // X key
            KEY_Y = 0x59,           // Y key
            KEY_Z = 0x5A,           // Z key
            NUMPAD0 = 0x60,         // VK_NUMPAD0
            NUMPAD1 = 0x61,         // VK_NUMPAD1
            NUMPAD2 = 0x62,         // VK_NUMPAD2
            NUMPAD3 = 0x63,         // VK_NUMPAD3
            NUMPAD4 = 0x64,         // VK_NUMPAD4
            NUMPAD5 = 0x65,         // VK_NUMPAD5
            NUMPAD6 = 0x66,         // VK_NUMPAD6
            NUMPAD7 = 0x67,         // VK_NUMPAD7
            NUMPAD8 = 0x68,         // VK_NUMPAD8
            NUMPAD9 = 0x69,         // VK_NUMPAD9
            MULTIPLY = 0x6A,        // VK_MULTIPLY
            ADD = 0x6B,             // VK_ADD
            SEPARATOR = 0x6C,       // VK_SEPARATOR
            SUBTRACT = 0x6D,        // VK_SUBTRACT
            DECIMAL = 0x6E,         // VK_DECIMAL
            DIVIDE = 0x6F,          // VK_DIVIDE
            F1 = 0x70,              // VK_F1
            F2 = 0x71,              // VK_F2
            F3 = 0x72,              // VK_F3
            F4 = 0x73,              // VK_F4
            F5 = 0x74,              // VK_F5
            F6 = 0x75,              // VK_F6
            F7 = 0x76,              // VK_F7
            F8 = 0x77,              // VK_F8
            F9 = 0x78,              // VK_F9
            F10 = 0x79,             // VK_F10
            F11 = 0x7A,             // VK_F11
            F12 = 0x7B,             // VK_F12
            LEFT_SHIFT = 0xA0,      // VK_LSHIFT
            RIGHT_SHIFT = 0xA1,     // VK_RSHIFT
            LEFT_CTRL = 0xA2,       // VK_LCONTROL
            RIGHT_CTRL = 0xA3,      // VK_RCONTROL
            LEFT_ALT = 0xA4,        // VK_LMENU
            RIGHT_ALT = 0xA5,       // VK_RMENU
            GRAVE = 0xC0,           // VK_OEM_3 (`)
            MINUS = 0xBD,           // VK_OEM_MINUS (-)
            EQUALS = 0xBB,          // VK_OEM_PLUS (=)
            LBRACKET = 0xDB,        // VK_OEM_4 ([)
            RBRACKET = 0xDD,        // VK_OEM_6 (])
            BACKSLASH = 0xDC,       // VK_OEM_5 (\)
            SLASH = 0xBF,           // VK_OEM_2 (/)
            QUOTE = 0xDE,           // VK_OEM_7 (')
            SEMICOLON = 0xBA,       // VK_OEM_1 (;)
            COMMA = 0xBC,           // VK_OEM_COMMA (,)
            PERIOD = 0xBE           // VK_OEM_PERIOD (.)
        };
    };

    const std::unordered_map<Key::MouseCodes, const char*> g_MouseNameMap =
    {
			{Key::LEFT_MOUSE,       "LBUTTON"},
			{Key::RIGHT_MOUSE,      "RBUTTON"},
			{Key::MIDDLE_MOUSE,     "MBUTTON"},
			{Key::X1_MOUSE,         "XBUTTON1"},
			{Key::X2_MOUSE,         "XBUTTON2"},
            {Key::WHEEL_UP,         "WHEEL_UP"},
            {Key::WHEEL_DOWN,       "WHEEL_DOWN"}
	};

    const std::unordered_map<Key::KeyboardCodes, const char*> g_KeyboardNameMap =
    {
            {Key::BACKSPACE,        "BACK"},
            {Key::TAB,              "TAB"},
            {Key::CLEAR,            "CLEAR"},
            {Key::ENTER,            "RETURN"},
            {Key::SHIFT,            "SHIFT"},
            {Key::CTRL,             "CONTROL"},
            {Key::ALT,              "MENU"},
            {Key::PAUSE,            "PAUSE"},
            {Key::CAPS_LOCK,        "CAPITAL"},
            {Key::ESCAPE,           "ESCAPE"},
            {Key::SPACE,            "SPACE"},
            {Key::PAGE_UP,          "PRIOR"},
            {Key::PAGE_DOWN,        "NEXT"},
            {Key::END,              "END"},
            {Key::HOME,             "HOME"},
            {Key::LEFT,             "LEFT"},
            {Key::UP,               "UP"},
            {Key::RIGHT,            "RIGHT"},
            {Key::DOWN,             "DOWN"},
            {Key::SELECT,           "SELECT"},
            {Key::INSERT,           "INSERT"},
            {Key::DEL,              "DELETE"},
            {Key::KEY_0,            "0"},
            {Key::KEY_1,            "1"},
            {Key::KEY_2,            "2"},
            {Key::KEY_3,            "3"},
            {Key::KEY_4,            "4"},
            {Key::KEY_5,            "5"},
            {Key::KEY_6,            "6"},
            {Key::KEY_7,            "7"},
            {Key::KEY_8,            "8"},
            {Key::KEY_9,            "9"},
            {Key::KEY_A,            "A"},
            {Key::KEY_B,            "B"},
            {Key::KEY_C,            "C"},
            {Key::KEY_D,            "D"},
            {Key::KEY_E,            "E"},
            {Key::KEY_F,            "F"},
            {Key::KEY_G,            "G"},
            {Key::KEY_H,            "H"},
            {Key::KEY_I,            "I"},
            {Key::KEY_J,            "J"},
            {Key::KEY_K,            "K"},
            {Key::KEY_L,            "L"},
            {Key::KEY_M,            "M"},
            {Key::KEY_N,            "N"},
            {Key::KEY_O,            "O"},
            {Key::KEY_P,            "P"},
            {Key::KEY_Q,            "Q"},
            {Key::KEY_R,            "R"},
            {Key::KEY_S,            "S"},
            {Key::KEY_T,            "T"},
            {Key::KEY_U,            "U"},
            {Key::KEY_V,            "V"},
            {Key::KEY_W,            "W"},
            {Key::KEY_X,            "X"},
            {Key::KEY_Y,            "Y"},
            {Key::KEY_Z,            "Z"},
            {Key::NUMPAD0,          "NUMPAD0"},
            {Key::NUMPAD1,          "NUMPAD1"},
            {Key::NUMPAD2,          "NUMPAD2"},
            {Key::NUMPAD3,          "NUMPAD3"},
            {Key::NUMPAD4,          "NUMPAD4"},
            {Key::NUMPAD5,          "NUMPAD5"},
            {Key::NUMPAD6,          "NUMPAD6"},
            {Key::NUMPAD7,          "NUMPAD7"},
            {Key::NUMPAD8,          "NUMPAD8"},
            {Key::NUMPAD9,          "NUMPAD9"},
            {Key::MULTIPLY,         "MULTIPLY"},
            {Key::ADD,              "ADD"},
            {Key::SEPARATOR,        "SEPARATOR"},
            {Key::SUBTRACT,         "SUBTRACT"},
            {Key::DECIMAL,          "DECIMAL"},
            {Key::DIVIDE,           "DIVIDE"},
            {Key::F1,               "F1"},
            {Key::F2,               "F2"},
            {Key::F3,               "F3"},
            {Key::F4,               "F4"},
            {Key::F5,               "F5"},
            {Key::F6,               "F6"},
            {Key::F7,               "F7"},
            {Key::F8,               "F8"},
            {Key::F9,               "F9"},
            {Key::F10,              "F10"},
            {Key::F11,              "F11"},
            {Key::F12,              "F12"},
            {Key::LEFT_SHIFT,       "SHIFT"},
            {Key::RIGHT_SHIFT,      "RSHIFT"},
            {Key::LEFT_CTRL,        "CONTROL"},
            {Key::RIGHT_CTRL,       "RCONTROL"},
            {Key::LEFT_ALT,         "ALT"},
            {Key::RIGHT_ALT,        "RALT"},
            {Key::GRAVE,            "GRAVE"},
            {Key::MINUS,            "MINUS"},
            {Key::EQUALS,           "EQUALS"},
            {Key::LBRACKET,         "LBRACKET"},
            {Key::RBRACKET,         "RBRACKET"},
            {Key::BACKSLASH,        "BACKSLASH"},
            {Key::SLASH,            "SLASH"},
            {Key::QUOTE,            "QUOTE"},
            {Key::SEMICOLON,        "SEMICOLON"},
            {Key::COMMA,            "COMMA"},
            {Key::PERIOD,           "PERIOD"}
    };
}
