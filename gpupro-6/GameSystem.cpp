#include "stdafx.h"
#include "GameSystem.h"
#include "GraphicsSystem.h"
#include "MaterialManagementSystem.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

GameSystem GameSystem::s_instance = GameSystem();

GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
}

GraphicsSystem* GameSystem::Graphics()
{
	return s_instance.Graphics();
}

MaterialManagementSystem* GameSystem::Materials()
{
	return s_instance.m_materialManagementSystem;
}

int GameSystem::Run()
{
	return s_instance.GameLoop();
}

int GameSystem::GameLoop()
{
	int screenWidth = 0;
	int screenHeight = 0;
	InitializeWindows(screenWidth, screenHeight);

	m_graphicsSystem = GraphicsSystem::InitializeGraphics(m_hwnd, screenWidth, screenHeight);
	m_materialManagementSystem = new MaterialManagementSystem();

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true)
	{
		if (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE)) // TODO: Create and move this to an InputManager
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}

		const std::vector<Material*>* allMats = m_materialManagementSystem->GetAllMaterials();
		m_graphicsSystem->Render(allMats);
	}

	return msg.wParam;
}

void GameSystem::InitializeWindows(int& screenWidth, int& screenHeight)
{
	DEVMODE dmScreenSettings;
	int posX, posY;

	m_hInstance = GetModuleHandle(NULL);
	m_applicationName = L"Engine";

	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
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

	screenWidth = 800;
	screenHeight = 600;

	posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;

	m_hwnd = CreateWindowEx(
		NULL,
		m_applicationName,
		m_applicationName,
		WS_OVERLAPPEDWINDOW,
		posX,
		posY,
		screenWidth,
		screenHeight,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
}

void GameSystem::ShutdownWindows()
{
	DestroyWindow(m_hwnd);
	m_hwnd = nullptr;

	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = nullptr;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}
}