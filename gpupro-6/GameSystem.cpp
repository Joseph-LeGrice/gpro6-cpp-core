#include "stdafx.h"
#include "GameSystem.h"
#include "GraphicsSystem.h"
#include "SceneManagementSystem.h"
#include "MaterialManagementSystem.h"
#include "TimeSystem.h"
#include "SceneGraph.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

GameSystem* GameSystem::s_instance = new GameSystem();

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
	return GraphicsSystem::Instance()->InitializeGraphics(s_instance->m_hwnd, screenWidth, screenHeight);
}

int GameSystem::Run()
{
	return s_instance->GameLoop();
}

void GameSystem::Shutdown()
{
	SAFE_DELETE(s_instance);
}

int GameSystem::GameLoop()
{
	TimeSystem* time = TimeSystem::Instance();
	SceneManagementSystem* sceneManager = SceneManagementSystem::Instance();
	MaterialManagementSystem* materialManager = MaterialManagementSystem::Instance();
	GraphicsSystem* graphicsSystem = GraphicsSystem::Instance();

	sceneManager->GetSceneGraph()->InitScene();
	
	m_running = true;
	while (m_running)
	{
		ProcessInput();

		while (time->ShouldAdvanceFixedStep())
		{
			sceneManager->GetSceneGraph()->UpdateScene();
		}

		Camera& cam = sceneManager->GetSceneGraph()->GetCamera();
		const std::vector<Material*>* allMats = materialManager->GetAllMaterials();
		graphicsSystem->Render(cam, allMats);

		time->AdvanceFrame();
	}

	sceneManager->GetSceneGraph()->DeInitScene();

	return 0;
}

void GameSystem::ProcessInput()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE)) // TODO: Create and move this to an InputManager
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			m_running = false;
		}
	}
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