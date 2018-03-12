#include "stdafx.h"
#include "WindowManager.h"
#include "Engine/Core/Input/InputSystem.h"

WindowManager::WindowManager()
{
    //DEVMODE dmScreenSettings;
    int posX, posY;

    m_hInstance = GetModuleHandle(NULL);
    m_applicationName = L"Game";

    WNDCLASSEX wc;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = InputSystem::WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = m_applicationName;
    wc.cbSize = sizeof(WNDCLASSEX);

    RegisterClassEx(&wc);

    m_windowWidth = 800;
    m_windowHeight = 600;

    posX = (GetSystemMetrics(SM_CXSCREEN) - m_windowWidth) / 2;
    posY = (GetSystemMetrics(SM_CYSCREEN) - m_windowHeight) / 2;

    m_hwnd = CreateWindowEx(
        NULL,
        m_applicationName,
        m_applicationName,
        WS_OVERLAPPEDWINDOW,
        posX,
        posY,
        m_windowWidth,
        m_windowHeight,
        NULL,
        NULL,
        m_hInstance,
        NULL);

    ShowWindow(m_hwnd, SW_SHOW);
    SetForegroundWindow(m_hwnd);
    SetFocus(m_hwnd);
}

WindowManager::~WindowManager()
{
    DestroyWindow(m_hwnd);
    m_hwnd = nullptr;

    UnregisterClass(m_applicationName, m_hInstance);
    m_hInstance = nullptr;
}

HWND& WindowManager::GetHWND()
{
    return m_hwnd;
}

UINT WindowManager::GetWindowWidth()
{
    return m_windowWidth;
}

UINT WindowManager::GetWindowHeight()
{
    return m_windowHeight;
}
