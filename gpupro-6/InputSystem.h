#pragma once
#include "ISystem.h"

class InputSystem : public ISystem
{
	REGISTER_SUBSYSTEM(InputSystem)
public:
	void SetHWND(HWND hwnd);
	virtual void VariableTick() override;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

private:
	HWND m_hwnd;
};

