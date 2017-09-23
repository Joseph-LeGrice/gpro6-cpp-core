#pragma once
#include "Vector2.h"

class MouseInput
{
public:
	MouseInput();
	~MouseInput();
	MouseInput(const MouseInput&) = delete;

	//Vector2 GetMousePosition();
	//bool GetMouseButton(int buttonIndex);
	//bool GetMouseButtonDownThisFrame(int buttonIndex);
	//bool GetMouseButtonUpThisFrame(int buttonIndex);

	void HandleInput(MSG m);

private:
	Vector2 m_mousePosition;
	UINT8 m_thisMouseButtonState, m_lastMouseButtonState;
};

