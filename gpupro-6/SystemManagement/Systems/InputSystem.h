#pragma once
#include "SystemManagement/ISystem.h"
#include "Input/MouseInput.h"
#include "Input/KeyboardInput.h"

class InputSystem : public ISystem
{
public:
    InputSystem();
    InputSystem(const InputSystem&) = delete;
    virtual ~InputSystem();

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

