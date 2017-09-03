#pragma once

class GraphicsSystem;
class MaterialManagementSystem;
class SceneManagementSystem;

class GameSystem
{
public:
	~GameSystem();

	static bool InitializeAllSystems();
	static int Run();
	static void Shutdown();

	static GraphicsSystem* Graphics();
	static MaterialManagementSystem* MaterialManager();
	static SceneManagementSystem* SceneManager();

private:
	static GameSystem* s_instance;

	bool m_running;
	HINSTANCE m_hInstance;
	HWND m_hwnd;
	LPCWSTR m_applicationName;

	GameSystem();
	GameSystem(const GameSystem&);

	int GameLoop();
	void ProcessInput();
	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();

	GraphicsSystem* m_graphicsSystem;
	MaterialManagementSystem* m_materialManagementSystem;
	SceneManagementSystem* m_sceneManagerSystem;
};

