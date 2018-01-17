#pragma once

#include <unordered_map>

enum InputKey
{
    kInputKey_LBUTTON = 0x01,
    kInputKey_RBUTTON = 0x02,
    kInputKey_CANCEL = 0x03,
    kInputKey_MBUTTON = 0x04,
    kInputKey_XBUTTON1 = 0x05,
    kInputKey_XBUTTON2 = 0x06,

    kInputKey_BACK = 0x08,
    kInputKey_TAB = 0x09,

    kInputKey_CLEAR = 0x0C,
    kInputKey_RETURN = 0x0D,

    kInputKey_SHIFT = 0x10,
    kInputKey_CONTROL = 0x11,
    kInputKey_MENU = 0x12,
    kInputKey_PAUSE = 0x13,
    kInputKey_CAPITAL = 0x14,
    kInputKey_KANA = 0x15,
    kInputKey_HANGUEL = 0x15,
    kInputKey_HANGUL = 0x15,

    kInputKey_JUNJA = 0x17,
    kInputKey_FINAL = 0x18,
    kInputKey_HANJA = 0x19,
    kInputKey_KANJI = 0x19,

    kInputKey_ESCAPE = 0x1B,
    kInputKey_CONVERT = 0x1C,
    kInputKey_NONCONVERT = 0x1D,
    kInputKey_ACCEPT = 0x1E,
    kInputKey_MODECHANGE = 0x1F,
    kInputKey_SPACE = 0x20,
    kInputKey_PRIOR = 0x21,
    kInputKey_NEXT = 0x22,
    kInputKey_END = 0x23,
    kInputKey_HOME = 0x24,
    kInputKey_LEFT = 0x25,
    kInputKey_UP = 0x26,
    kInputKey_RIGHT = 0x27,
    kInputKey_DOWN = 0x28,
    kInputKey_SELECT = 0x29,
    kInputKey_PRINT = 0x2A,
    kInputKey_EXECUTE = 0x2B,
    kInputKey_SNAPSHOT = 0x2C,
    kInputKey_INSERT = 0x2D,
    kInputKey_DELETE = 0x2E,
    kInputKey_HELP = 0x2F,

    kInputKey_0 = 0x30,
    kInputKey_1 = 0x31,
    kInputKey_2 = 0x32,
    kInputKey_3 = 0x33,
    kInputKey_4 = 0x34,
    kInputKey_5 = 0x35,
    kInputKey_6 = 0x36,
    kInputKey_7 = 0x37,
    kInputKey_8 = 0x38,
    kInputKey_9 = 0x39,

    kInputKey_A = 0x41,
    kInputKey_B = 0x42,
    kInputKey_C = 0x43,
    kInputKey_D = 0x44,
    kInputKey_E = 0x45,
    kInputKey_F = 0x46,
    kInputKey_G = 0x47,
    kInputKey_H = 0x48,
    kInputKey_I = 0x49,
    kInputKey_J = 0x4A,
    kInputKey_K = 0x4B,
    kInputKey_L = 0x4C,
    kInputKey_M = 0x4D,
    kInputKey_N = 0x4E,
    kInputKey_O = 0x4F,
    kInputKey_P = 0x50,
    kInputKey_Q = 0x51,
    kInputKey_R = 0x52,
    kInputKey_S = 0x53,
    kInputKey_T = 0x54,
    kInputKey_U = 0x55,
    kInputKey_V = 0x56,
    kInputKey_W = 0x57,
    kInputKey_X = 0x58,
    kInputKey_Y = 0x59,
    kInputKey_Z = 0x5A,

    kInputKey_LWIN = 0x5B,
    kInputKey_RWIN = 0x5C,
    kInputKey_APPS = 0x5D,

    kInputKey_SLEEP = 0x5F,
    kInputKey_NUMPAD0 = 0x60,
    kInputKey_NUMPAD1 = 0x61,
    kInputKey_NUMPAD2 = 0x62,
    kInputKey_NUMPAD3 = 0x63,
    kInputKey_NUMPAD4 = 0x64,
    kInputKey_NUMPAD5 = 0x65,
    kInputKey_NUMPAD6 = 0x66,
    kInputKey_NUMPAD7 = 0x67,
    kInputKey_NUMPAD8 = 0x68,
    kInputKey_NUMPAD9 = 0x69,
    kInputKey_MULTIPLY = 0x6A,
    kInputKey_ADD = 0x6B,
    kInputKey_SEPARATOR = 0x6C,
    kInputKey_SUBTRACT = 0x6D,
    kInputKey_DECIMAL = 0x6E,
    kInputKey_DIVIDE = 0x6F,
    kInputKey_F1 = 0x70,
    kInputKey_F2 = 0x71,
    kInputKey_F3 = 0x72,
    kInputKey_F4 = 0x73,
    kInputKey_F5 = 0x74,
    kInputKey_F6 = 0x75,
    kInputKey_F7 = 0x76,
    kInputKey_F8 = 0x77,
    kInputKey_F9 = 0x78,
    kInputKey_F10 = 0x79,
    kInputKey_F11 = 0x7A,
    kInputKey_F12 = 0x7B,
    kInputKey_F13 = 0x7C,
    kInputKey_F14 = 0x7D,
    kInputKey_F15 = 0x7E,
    kInputKey_F16 = 0x7F,
    kInputKey_F17 = 0x80,
    kInputKey_F18 = 0x81,
    kInputKey_F19 = 0x82,
    kInputKey_F20 = 0x83,
    kInputKey_F21 = 0x84,
    kInputKey_F22 = 0x85,
    kInputKey_F23 = 0x86,
    kInputKey_F24 = 0x87,

    kInputKey_NUMLOCK = 0x90,
    kInputKey_SCROLL = 0x91,

    kInputKey_LSHIFT = 0xA0,
    kInputKey_RSHIFT = 0xA1,
    kInputKey_LCONTROL = 0xA2,
    kInputKey_RCONTROL = 0xA3,
    kInputKey_LMENU = 0xA4,
    kInputKey_RMENU = 0xA5,
    kInputKey_BROWSER_BACK = 0xA6,
    kInputKey_BROWSER_FORWARD = 0xA7,
    kInputKey_BROWSER_REFRESH = 0xA8,
    kInputKey_BROWSER_STOP = 0xA9,
    kInputKey_BROWSER_SEARCH = 0xAA,
    kInputKey_BROWSER_FAVORITES = 0xAB,
    kInputKey_BROWSER_HOME = 0xAC,
    kInputKey_VOLUME_MUTE = 0xAD,
    kInputKey_VOLUME_DOWN = 0xAE,
    kInputKey_VOLUME_UP = 0xAF,
    kInputKey_MEDIA_NEXT_TRACK = 0xB0,
    kInputKey_MEDIA_PREV_TRACK = 0xB1,
    kInputKey_MEDIA_STOP = 0xB2,
    kInputKey_MEDIA_PLAY_PAUSE = 0xB3,
    kInputKey_LAUNCH_MAIL = 0xB4,
    kInputKey_LAUNCH_MEDIA_SELECT = 0xB5,
    kInputKey_LAUNCH_APP1 = 0xB6,
    kInputKey_LAUNCH_APP2 = 0xB7,

    kInputKey_OEM_1 = 0xBA,
    kInputKey_OEM_PLUS = 0xBB,
    kInputKey_OEM_COMMA = 0xBC,
    kInputKey_OEM_MINUS = 0xBD,
    kInputKey_OEM_PERIOD = 0xBE,
    kInputKey_OEM_2 = 0xBF,
    kInputKey_OEM_3 = 0xC0,

    kInputKey_OEM_4 = 0xDB,
    kInputKey_OEM_5 = 0xDC,
    kInputKey_OEM_6 = 0xDD,
    kInputKey_OEM_7 = 0xDE,
    kInputKey_OEM_8 = 0xDF,

    kInputKey_OEM_102 = 0xE2,

    kInputKey_PROCESSKEY = 0xE5,

    kInputKey_PACKET = 0xE7,

    kInputKey_ATTN = 0xF6,
    kInputKey_CRSEL = 0xF7,
    kInputKey_EXSEL = 0xF8,
    kInputKey_EREOF = 0xF9,
    kInputKey_PLAY = 0xFA,
    kInputKey_ZOOM = 0xFB,
    kInputKey_NONAME = 0xFC,
    kInputKey_PA1 = 0xFD,
    kInputKey_OEM_CLEAR = 0xFE
};

class KeyboardInput
{
public:
	KeyboardInput();
	~KeyboardInput();
	KeyboardInput(const KeyboardInput&) = delete;
	void HandleInput(MSG msg);
    void AdvanceFrame();

	bool GetKey(InputKey key) const;
	bool GetKeyDownThisFrame(InputKey key) const;
	bool GetKeyUpThisFrame(InputKey key) const;

private:
	std::unordered_map<InputKey, bool> m_keyPressesLastFrame; 
	std::unordered_map<InputKey, bool> m_keyPressesThisFrame;

	bool IsKeyboardKeypress(WPARAM param) const;
};

