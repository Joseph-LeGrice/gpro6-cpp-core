#pragma once

#include "ISystem.h"
#include <type_traits>
#include <typeindex>
#include <unordered_map>

class GraphicsSystem;
class MaterialManagementSystem;
class SceneManagementSystem;

class GameSystem
{
public:
	~GameSystem();

	static bool InitializeAllSystems();
	static int Run();
	static void Quit();
	static void ShutdownWindows();

	template <class T>
	static T* GetSystem();

private:
	static GameSystem* s_instance;
	
	bool m_running;
	static HWND s_hwnd;
	static LPCWSTR s_applicationName;
	static HINSTANCE s_hInstance;

	GameSystem();
	GameSystem(const GameSystem&);

	int GameLoop();
	void InitializeWindows(int& screenWidth, int& screenHeight);

	std::unordered_map<std::type_index, ISystem*> m_subsystems;
};

template <class T>
static T* GameSystem::GetSystem()
{
	static_assert(std::is_base_of<ISystem, T>::value, "Must be Sub-Class of ISystem");
	std::type_index typeId = typeid(T);
	if (!s_instance->m_subsystems.count(typeId))
	{
		s_instance->m_subsystems[typeId] = new T();
	}
	return (T*)s_instance->m_subsystems[typeId];
}

//TODO: Maybe replace REGISTER_SUBSYSTEM with a templated version of ISystem
#define REGISTER_SUBSYSTEM(x) \
public: \
static x* Instance() \
{ \
	static_assert(std::is_base_of<ISystem, x>::value, "Must be Sub-Class of ISystem"); \
	return GameSystem::GetSystem<x>(); \
} \
x(const x&) = delete; \
x(); \
virtual ~x();
