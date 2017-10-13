#pragma once

#include <unordered_map>

enum InputKey
{
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
	kInputKey_Z = 0x5A
};

class KeyboardInput
{
public:
	KeyboardInput();
	~KeyboardInput();
	KeyboardInput(const KeyboardInput&) = delete;
	void HandleInput(MSG msg, bool didAdvanceFrame);
	bool GetKey(InputKey key) const;
	bool GetKeyDownThisFrame(InputKey key) const;
	bool GetKeyUpThisFrame(InputKey key) const;

private:
	std::unordered_map<InputKey, bool> m_keyPressesLastFrame; 
	std::unordered_map<InputKey, bool> m_keyPressesThisFrame;

	bool IsKeyboardKeypress(WPARAM param) const;
};

