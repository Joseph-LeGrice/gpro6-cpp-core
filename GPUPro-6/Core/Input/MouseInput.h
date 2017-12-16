#pragma once
#include "Core/DataStructures\Vector2.h"

class MouseInput
{
public:
	MouseInput();
	~MouseInput();
	MouseInput(const MouseInput&) = delete;

	const Vector2& GetMousePosition() const;
    const Vector2& GetDeltaMousePosition() const;

	bool GetMouseButton(int buttonIndex) const;
	bool GetMouseButtonDownThisFrame(int buttonIndex) const;
	bool GetMouseButtonUpThisFrame(int buttonIndex) const;

	void HandleInput(MSG m);
    void AdvanceFrame();

private:
    Vector2 m_mousePosition, m_deltaMousePosition;
	UINT8 m_thisMouseButtonState, m_lastMouseButtonState;
};

