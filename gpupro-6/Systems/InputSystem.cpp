#include "stdafx.h"
#include "InputSystem.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::SetHWND(HWND hwnd)
{
	m_hwnd = hwnd;
}

void InputSystem::VariableTick()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			GameSystem::Quit();
		}

		m_mouseInput.HandleInput(msg);
		m_keyboardInput.HandleInput(msg);
	}
}

const MouseInput& InputSystem::GetMouse()
{
	return m_mouseInput;
}

const KeyboardInput& InputSystem::GetKeyboard()
{
	return m_keyboardInput;
}

LRESULT CALLBACK InputSystem::WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
}
