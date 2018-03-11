#pragma once

//#include <memory>

#include "Engine/Core/SystemManagement/ISystem.h"
#include "Engine/Core/Input/MouseInput.h"
#include "Engine/Core/Input/KeyboardInput.h"

class GameLoop;

class InputSystem : public ISystem
{
public:
	InputSystem::InputSystem() { }
	//InputSystem::InputSystem(std::shared_ptr<GameLoop> gameLoop) : m_gameLoop(gameLoop) { } // FIXME
    InputSystem(const InputSystem&) = delete;

	void SetHWND(HWND hwnd);
	virtual void VariableTick() override;

	const MouseInput& GetMouse();
	const KeyboardInput& GetKeyboard();

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

private:
	HWND m_hwnd;
	//std::shared_ptr<GameLoop> m_gameLoop;
	MouseInput m_mouseInput;
	KeyboardInput m_keyboardInput;
};

