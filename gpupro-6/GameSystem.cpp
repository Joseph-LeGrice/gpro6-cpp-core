#include "stdafx.h"
#include "GameSystem.h"
#include "GraphicsSystem.h"
#include "SceneManagementSystem.h"
#include "MaterialManagementSystem.h"
#include "SceneGraph.h"
#include <chrono>

using namespace std::chrono_literals;

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

GameSystem* GameSystem::s_instance = new GameSystem();

GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
	SAFE_DELETE(m_sceneManagerSystem);
	SAFE_DELETE(m_materialManagementSystem);
	SAFE_DELETE(m_graphicsSystem);
}

GraphicsSystem* GameSystem::Graphics()
{
	return s_instance->m_graphicsSystem;
}

MaterialManagementSystem* GameSystem::MaterialManager()
{
	return s_instance->m_materialManagementSystem;
}

SceneManagementSystem* GameSystem::SceneManager()
{
	return s_instance->m_sceneManagerSystem;
}

bool GameSystem::InitializeAllSystems()
{
	int screenWidth = 0;
	int screenHeight = 0;
	s_instance->InitializeWindows(screenWidth, screenHeight);

	s_instance->m_graphicsSystem = GraphicsSystem::InitializeGraphics(s_instance->m_hwnd, screenWidth, screenHeight);
	s_instance->m_materialManagementSystem = new MaterialManagementSystem();
	s_instance->m_sceneManagerSystem = new SceneManagementSystem();

	return s_instance->m_graphicsSystem != nullptr;
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
	using clock = std::chrono::high_resolution_clock;

	constexpr std::chrono::nanoseconds timeStep(16ms);
	std::chrono::nanoseconds lag(0ns);
	auto lastTime = clock::now();

	m_sceneManagerSystem->GetSceneGraph()->InitializeScene();

	m_running = true;
	while (m_running)
	{
		ProcessInput();

		auto deltaTime = clock::now() - lastTime;
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
		lastTime = clock::now();

		while (lag >= timeStep)
		{
			lag -= timeStep;
			m_sceneManagerSystem->GetSceneGraph()->UpdateScene();
		}

		const std::vector<Material*>* allMats = m_materialManagementSystem->GetAllMaterials();
		m_graphicsSystem->Render(allMats);
	}

	m_sceneManagerSystem->GetSceneGraph()->DestroyScene();

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