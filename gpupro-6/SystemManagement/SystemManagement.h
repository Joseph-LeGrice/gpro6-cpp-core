#pragma once

#include "SystemManagement/SystemConfiguration.hpp"

#include "SystemManagement/Systems/GraphicsSystem.h"
#include "SystemManagement/Systems/InputSystem.h"
#include "SystemManagement/Systems/LightingSystem.h"
#include "SystemManagement/Systems/TimeSystem.h"

//typedef SystemConfiguration<
//    GraphicsSystem,
//    MaterialManagementSystem,
//    SceneManagementSystem,
//    LightingSystem,
//    ShaderManagementSystem,
//    TimeSystem,
//    ConstantBufferManagementSystem,
//    InputSystem
//> MainConfig;


//TODO: Make SystemManagement more easily extensible with code generation,
//      or some other way of registering systems as modules that can be retrieved
//      Bear in mind need for concurrency in the future.
class SystemManagement
{
public:
    static void Initialize()
    {
        s_instance->DoInitialize();
    }

    static int RunGameLoop()
    {
        return s_instance->DoRunGameLoop();
    }

    static void Deinitialize()
    {
        s_instance->DoDeinitialize();
        delete s_instance;
    }

    static TimeSystem* GetTimeSystem()
    {
        return &s_instance->m_timeSystem;
    }

    static InputSystem* GetInputSystem()
    {
        return &s_instance->m_inputSystem;
    }

    static GraphicsSystem* GetGraphicsSystem()
    {
        return &s_instance->m_graphicsSystem;
    }

    static LightingSystem* GetLightingSystem()
    {
        return &s_instance->m_lightingSystem;
    }

    static void Quit()
    {
        s_instance->m_running = false;
    }

private:
    static SystemManagement* s_instance;
   
    // TODO: THESE ARE NOT SYSTEMS!
    //MaterialManagementSystem,
    //SceneManagementSystem 
    //ShaderManagementSystem,
    //ConstantBufferManagementSystem,

    TimeSystem m_timeSystem;
    InputSystem m_inputSystem;
    GraphicsSystem m_graphicsSystem;
    LightingSystem m_lightingSystem;

    bool m_running;

    SystemManagement();
    ~SystemManagement();
    SystemManagement(const SystemManagement&) = delete;

    void DoInitialize();
    int DoRunGameLoop();
    void DoDeinitialize();

    //TODO: Move this functionality 
    static HWND s_hwnd;
    static LPCWSTR s_applicationName;
    static HINSTANCE s_hInstance;
    void InitializeWindows(int& screenWidth, int& screenHeight);
    void ShutdownWindows();
};

