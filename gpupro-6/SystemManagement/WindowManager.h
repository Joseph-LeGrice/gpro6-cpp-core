#pragma once
class WindowManager
{
public:
    static void InitializeWindow();
    static void ShutdownWindow();
    
    static HWND& GetHWND();
    static int GetWindowWidth();
    static int GetWindowHeight();

private:
    WindowManager() = delete;
    WindowManager(const WindowManager&) = delete;
    ~WindowManager() = delete;

    static int s_windowWidth;
    static int s_windowHeight;

    static HWND s_hwnd;
    static LPCWSTR s_applicationName;
    static HINSTANCE s_hInstance;
};

