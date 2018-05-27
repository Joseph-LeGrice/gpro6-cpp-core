#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"
#include "Engine/Core/Input/MouseInput.h"
#include "Engine/Core/Input/KeyboardInput.h"

class GameLoop;

class InputSystem : public ISystem
{
public:
	InputSystem::InputSystem(GameLoop& gameLoop) : m_gameLoop(gameLoop) { }
    InputSystem(const InputSystem&) = delete;

	void SetHWND(HWND hwnd);
	virtual void VariableTick() override;

	const MouseInput& GetMouse();
	const KeyboardInput& GetKeyboard();

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

private:
	HWND m_hwnd;
	GameLoop& m_gameLoop;
	MouseInput m_mouseInput;
	KeyboardInput m_keyboardInput;
};

