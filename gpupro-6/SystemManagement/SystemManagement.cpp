#include "stdafx.h"
#include "SystemManagement/SystemManagement.h"

SystemManagement* SystemManagement::s_instance = new SystemManagement();

HWND SystemManagement::s_hwnd = nullptr;
HINSTANCE SystemManagement::s_hInstance = nullptr;
LPCWSTR SystemManagement::s_applicationName = nullptr;

SystemManagement::~SystemManagement()
{

}

SystemManagement::SystemManagement()
{

}

void SystemManagement::DoInitialize()
{
    int screenWidth = 0;
    int screenHeight = 0;
    InitializeWindows(screenWidth, screenHeight);

    m_graphicsSystem.SetInfo(s_hwnd, screenWidth, screenHeight);

    m_timeSystem.Initialize();
    m_inputSystem.Initialize();
    m_graphicsSystem.Initialize();
    m_lightingSystem.Initialize();
}

int SystemManagement::DoRunGameLoop()
{
    try
    {
        m_running = true;
        while (m_running)
        {
            while (m_timeSystem.ShouldAdvanceFixedStep())
            {
                m_timeSystem.FixedTick();
                m_inputSystem.FixedTick();
                m_graphicsSystem.FixedTick();
                m_lightingSystem.FixedTick();
            }

            m_timeSystem.VariableTick();
            m_inputSystem.VariableTick();
            m_graphicsSystem.VariableTick();
            m_lightingSystem.VariableTick();

            m_timeSystem.AdvanceFrame();
        }
    }
    catch (...)
    {

    }

    return 0;
}

void SystemManagement::DoDeinitialize()
{
    m_timeSystem.Deinitalize();
    m_inputSystem.Deinitalize();
    m_graphicsSystem.Deinitalize();
    m_lightingSystem.Deinitalize();
}

void SystemManagement::InitializeWindows(int& screenWidth, int& screenHeight)
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

    screenWidth = 800;
    screenHeight = 600;

    posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
    posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;

    s_hwnd = CreateWindowEx(
        NULL,
        s_applicationName,
        s_applicationName,
        WS_OVERLAPPEDWINDOW,
        posX,
        posY,
        screenWidth,
        screenHeight,
        NULL,
        NULL,
        s_hInstance,
        NULL);
    SystemManagement::GetInputSystem()->SetHWND(s_hwnd);

    ShowWindow(s_hwnd, SW_SHOW);
    SetForegroundWindow(s_hwnd);
    SetFocus(s_hwnd);
}

void SystemManagement::ShutdownWindows()
{
    DestroyWindow(s_hwnd);
    s_hwnd = nullptr;

    UnregisterClass(s_applicationName, s_hInstance);
    s_hInstance = nullptr;
}