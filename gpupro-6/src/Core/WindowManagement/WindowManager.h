#pragma once
class WindowManager
{
public:
    static void InitializeWindow();
    static void ShutdownWindow();
    
    static HWND& GetHWND();
    static UINT GetWindowWidth();
    static UINT GetWindowHeight();

private:
    WindowManager() = delete;
    WindowManager(const WindowManager&) = delete;
    ~WindowManager() = delete;

    static UINT s_windowWidth;
    static UINT s_windowHeight;

    static HWND s_hwnd;
    static LPCWSTR s_applicationName;
    static HINSTANCE s_hInstance;
};

