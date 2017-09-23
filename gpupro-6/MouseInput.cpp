#include "stdafx.h"
#include "MouseInput.h"


MouseInput::MouseInput()
{
	m_mousePosition = Vector2::Zero();
	m_thisMouseButtonState = m_lastMouseButtonState = 0;
}


void MouseInput::HandleInput(MSG m)
{

}

MouseInput::~MouseInput()
{
}
