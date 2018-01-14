#include "stdafx.h"
#include "Engine/Core/Input\KeyboardInput.h"
#include "..\Utilities\Logging.h"


KeyboardInput::KeyboardInput()
{
}

void KeyboardInput::HandleInput(MSG msg)
{
	if (msg.message == WM_KEYDOWN)
	{
		if (IsKeyboardKeypress(msg.wParam))
		{
			InputKey ik = static_cast<InputKey>(msg.wParam);
			m_keyPressesThisFrame[ik] = true;
		}
	}
	else if (msg.message == WM_KEYUP)
	{
		if (IsKeyboardKeypress(msg.wParam))
		{
			InputKey ik = static_cast<InputKey>(msg.wParam);
			m_keyPressesThisFrame[ik] = false;
		}
	}
}

bool KeyboardInput::GetKey(InputKey key) const
{
	return m_keyPressesThisFrame.count(key) && m_keyPressesThisFrame.at(key);
}

bool KeyboardInput::GetKeyDownThisFrame(InputKey key) const
{
	return m_keyPressesThisFrame.count(key) && m_keyPressesThisFrame.at(key) && 
		(!m_keyPressesLastFrame.count(key) || !m_keyPressesLastFrame.at(key));
}

bool KeyboardInput::GetKeyUpThisFrame(InputKey key) const
{
	return m_keyPressesThisFrame.count(key) && !m_keyPressesThisFrame.at(key) && 
		m_keyPressesLastFrame.count(key) && m_keyPressesLastFrame.at(key);
}

bool KeyboardInput::IsKeyboardKeypress(WPARAM param) const
{
	return param >= kInputKey_A && param <= kInputKey_Z;
}

void KeyboardInput::AdvanceFrame()
{
    m_keyPressesLastFrame = m_keyPressesThisFrame;
}

KeyboardInput::~KeyboardInput()
{
}
