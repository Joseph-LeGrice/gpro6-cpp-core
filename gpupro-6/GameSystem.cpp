#include "stdafx.h"
#include "GameSystem.h"
#include "GraphicsSystem.h"
#include "SceneManagementSystem.h"
#include "MaterialManagementSystem.h"
#include "TimeSystem.h"
#include "SceneGraph.h"
#include "InputSystem.h"

GameSystem* GameSystem::s_instance = new GameSystem();

HWND GameSystem::s_hwnd = nullptr;
HINSTANCE GameSystem::s_hInstance = nullptr;
LPCWSTR GameSystem::s_applicationName = nullptr;

GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
	for (auto it = m_subsystems.begin(); it != m_subsystems.end(); ++it)
	{
		SAFE_DELETE(it->second);
	}
}

bool GameSystem::InitializeAllSystems()
{
	int screenWidth = 0;
	int screenHeight = 0;
	s_instance->InitializeWindows(screenWidth, screenHeight);
	return GraphicsSystem::Instance()->InitializeGraphics(s_instance->s_hwnd, screenWidth, screenHeight);
}

int GameSystem::Run()
{
	int returnCode = s_instance->GameLoop();
	SAFE_DELETE(s_instance);
	return returnCode;
}

void GameSystem::Quit()
{
	s_instance->m_running = false;
}

int GameSystem::GameLoop()
{
	TimeSystem* time = TimeSystem::Instance();
	SceneManagementSystem::Instance()->GetSceneGraph()->InitScene();
	
	m_running = true;
	while (m_running)
	{
		while (time->ShouldAdvanceFixedStep())
		{
			for (auto it = m_subsystems.begin(); it != m_subsystems.end(); ++it)
			{
				it->second->FixedTick();
			}
		}

		for (auto it = m_subsystems.begin(); it != m_subsystems.end(); ++it)
		{
			auto sys = it->second;
			sys->VariableTick();
		}

		time->AdvanceFrame();
	}

	SceneManagementSystem::Instance()->GetSceneGraph()->DeInitScene();

	return 0;
}

void GameSystem::InitializeWindows(int& screenWidth, int& screenHeight)
{
	DEVMODE dmScreenSettings;
	int posX, posY;

	s_hInstance = GetModuleHandle(NULL);
	s_applicationName = L"Engine";

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
	InputSystem::Instance()->SetHWND(s_hwnd);

	ShowWindow(s_hwnd, SW_SHOW);
	SetForegroundWindow(s_hwnd);
	SetFocus(s_hwnd);
}

void GameSystem::ShutdownWindows()
{
	DestroyWindow(s_hwnd);
	s_hwnd = nullptr;

	UnregisterClass(s_applicationName, s_hInstance);
	s_hInstance = nullptr;
}