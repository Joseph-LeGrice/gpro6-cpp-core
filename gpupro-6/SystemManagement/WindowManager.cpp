#include "stdafx.h"
#include "WindowManager.h"
#include "SystemManagement/Systems/InputSystem.h"

int WindowManager::s_windowWidth = 0;
int WindowManager::s_windowHeight = 0;
HWND WindowManager::s_hwnd = nullptr;
LPCWSTR WindowManager::s_applicationName = nullptr;
HINSTANCE WindowManager::s_hInstance = nullptr;

void WindowManager::InitializeWindow()
{
    //DEVMODE dmScreenSettings;
    int posX, posY;

    s_hInstance = GetModuleHandle(NULL);
    s_applicationName = L"Game";

    WNDCLASSEX wc;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = InputSystem::WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = s_hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = s_applicationName;
    wc.cbSize = sizeof(WNDCLASSEX);

    RegisterClassEx(&wc);

    s_windowWidth = 800;
    s_windowHeight = 600;

    posX = (GetSystemMetrics(SM_CXSCREEN) - s_windowWidth) / 2;
    posY = (GetSystemMetrics(SM_CYSCREEN) - s_windowHeight) / 2;

    s_hwnd = CreateWindowEx(
        NULL,
        s_applicationName,
        s_applicationName,
        WS_OVERLAPPEDWINDOW,
        posX,
        posY,
        s_windowWidth,
        s_windowHeight,
        NULL,
        NULL,
        s_hInstance,
        NULL);

    ShowWindow(s_hwnd, SW_SHOW);
    SetForegroundWindow(s_hwnd);
    SetFocus(s_hwnd);
}

void WindowManager::ShutdownWindow()
{
    DestroyWindow(s_hwnd);
    s_hwnd = nullptr;

    UnregisterClass(s_applicationName, s_hInstance);
    s_hInstance = nullptr;
}

HWND& WindowManager::GetHWND()
{
    return s_hwnd;
}

int WindowManager::GetWindowWidth()
{
    return s_windowWidth;
}

int WindowManager::GetWindowHeight()
{
    return s_windowHeight;
}
