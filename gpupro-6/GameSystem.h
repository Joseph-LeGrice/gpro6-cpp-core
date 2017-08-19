#pragma once

class GraphicsSystem;
class MaterialManagementSystem;

class GameSystem
{
public:
	static GraphicsSystem* Graphics();
	static MaterialManagementSystem* Materials();

	static int Run();

private:
	static GameSystem s_instance;

	HINSTANCE m_hInstance;
	HWND m_hwnd;
	LPCWSTR m_applicationName;

	GameSystem();
	~GameSystem();

	int GameLoop();
	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();

	GraphicsSystem* m_graphicsSystem;
	MaterialManagementSystem* m_materialManagementSystem;
};

