#include "stdafx.h"
#include "Logging.h"
#include "MouseInput.h"
#include <windowsx.h>

struct MouseButtonTranslate
{
	UINT8 buttonDownCode;
	UINT8 buttonUpCode;
};

const size_t c_numberOfButtons = 3;
const MouseButtonTranslate c_validStates[c_numberOfButtons] = {
	{ WM_LBUTTONDOWN, WM_LBUTTONUP },
	{ WM_RBUTTONDOWN, WM_RBUTTONUP },
	{ WM_MBUTTONDOWN, WM_MBUTTONUP }
};

MouseInput::MouseInput()
{
	m_mousePosition = Vector2::Zero();
	m_thisMouseButtonState = m_lastMouseButtonState = 0;
}

Vector2 MouseInput::GetMousePosition()
{
	return m_mousePosition;
}

Vector2 MouseInput::GetDeltaMousePosition()
{
	return m_deltaMousePosition;
}

bool MouseInput::GetMouseButton(int buttonIndex)
{
	if (buttonIndex < c_numberOfButtons)
	{
		UINT8 flag = 1 << buttonIndex;
		return m_thisMouseButtonState & flag == buttonIndex;
	}
	else
	{
		Log("[MouseInput] Supplied incorrect index for GetMouseButton");
		return false;
	}
}

bool MouseInput::GetMouseButtonDownThisFrame(int buttonIndex)
{
	if (buttonIndex < c_numberOfButtons)
	{
		UINT8 flag = 1 << buttonIndex;
		return m_thisMouseButtonState & flag == flag &&
			m_lastMouseButtonState & flag == 0;
	}
	else
	{
		Log("[MouseInput] Supplied incorrect index for GetMouseButtonDownThisFrame");
		return false;
	}
}

bool MouseInput::GetMouseButtonUpThisFrame(int buttonIndex)
{
	if (buttonIndex < c_numberOfButtons)
	{
		UINT8 flag = 1 << buttonIndex;
		return m_thisMouseButtonState & flag == 0 &&
			m_lastMouseButtonState & flag == flag;
	}
	else
	{
		Log("[MouseInput] Supplied incorrect index for GetMouseButtonUpThisFrame");
		return false;
	}
}

void MouseInput::HandleInput(MSG m)
{
	m_lastMouseButtonState = m_thisMouseButtonState;
	
	for (size_t i = 0; i < c_numberOfButtons; ++i)
	{
		UINT8 flag = 1 << i;
		if ((m_thisMouseButtonState & flag) == flag)
		{
			if (m.message == c_validStates[i].buttonUpCode)
			{
				m_thisMouseButtonState |= flag;
			}
		}
		else
		{
			if (m.message == c_validStates[i].buttonDownCode)
			{
				m_thisMouseButtonState &= ~flag;
			}
		}
	}

	if (m.message == WM_MOUSEMOVE)
	{
		Vector2 thisPosition = {
			GET_X_LPARAM(m.lParam),
			GET_Y_LPARAM(m.lParam)
		};
		m_deltaMousePosition = thisPosition - m_mousePosition;
		m_mousePosition = thisPosition;
	}
}

MouseInput::~MouseInput()
{
}
