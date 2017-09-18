#pragma once

#include <type_traits>
#include <typeindex>
#include <unordered_map>

class ISystem;
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

	template <class T>
	static T* GetSystem();

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

	std::unordered_map<std::type_index, ISystem*> m_subsystems;
};

template <class T>
static T* GameSystem::GetSystem()
{
	std::type_index typeId = typeid(T);
	if (!s_instance->m_subsystems.count(typeId))
	{
		s_instance->m_subsystems[typeId] = new T();
	}
	return (T*)s_instance->m_subsystems[typeId];
}

