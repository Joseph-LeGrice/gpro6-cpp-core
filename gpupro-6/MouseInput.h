#pragma once
#include "Vector2.h"

class MouseInput
{
public:
	MouseInput();
	~MouseInput();
	MouseInput(const MouseInput&) = delete;

	Vector2 GetMousePosition();
	Vector2 GetDeltaMousePosition();
	bool GetMouseButton(int buttonIndex);
	bool GetMouseButtonDownThisFrame(int buttonIndex);
	bool GetMouseButtonUpThisFrame(int buttonIndex);

	void HandleInput(MSG m);

private:
	Vector2 m_mousePosition, m_deltaMousePosition;
	UINT8 m_thisMouseButtonState, m_lastMouseButtonState;
};

