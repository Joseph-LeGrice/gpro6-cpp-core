#pragma once
#include "ISystem.h"
#include "MouseInput.h"
#include "KeyboardInput.h"

class InputSystem : public ISystem
{
	REGISTER_SUBSYSTEM(InputSystem);

public:
	void SetHWND(HWND hwnd);
	virtual void VariableTick() override;

	const MouseInput& GetMouse();
	const KeyboardInput& GetKeyboard();

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

private:
	HWND m_hwnd;
	MouseInput m_mouseInput;
	KeyboardInput m_keyboardInput;
};

