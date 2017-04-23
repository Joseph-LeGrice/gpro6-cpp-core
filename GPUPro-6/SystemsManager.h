#pragma once

#include "GraphicsSystem.h"


class SystemsManager
{
public:
	SystemsManager();
	~SystemsManager();
	bool InitializeAllSystems();
	void ShutdownAllSystems();
	int Run();

private:
	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();
	
	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	GraphicsSystem* m_graphicsSystem;
};
