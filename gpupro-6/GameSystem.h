#pragma once

class GraphicsSystem;
class MaterialManagementSystem;
class SceneManagementSystem;

class GameSystem
{
public:
	~GameSystem();

	static void InitializeAllSystems();
	static int Run();

	static GraphicsSystem* Graphics();
	static MaterialManagementSystem* MaterialManager();
	static SceneManagementSystem* SceneManager();

private:
	static GameSystem s_instance;

	HINSTANCE m_hInstance;
	HWND m_hwnd;
	LPCWSTR m_applicationName;

	GameSystem();

	int GameLoop();
	void ProcessInput();
	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();

	GraphicsSystem* m_graphicsSystem;
	MaterialManagementSystem* m_materialManagementSystem;
	SceneManagementSystem* m_sceneManagerSystem;
};

