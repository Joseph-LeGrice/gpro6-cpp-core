#pragma once
class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	WindowManager(const WindowManager&) = delete;
	
    HWND& GetHWND();
    UINT GetWindowWidth();
    UINT GetWindowHeight();

private:
	UINT m_windowWidth;
    UINT m_windowHeight;

    HWND m_hwnd;
    LPCWSTR m_applicationName;
    HINSTANCE m_hInstance;
};

